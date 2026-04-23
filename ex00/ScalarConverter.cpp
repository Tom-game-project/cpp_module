#include "ScalarConverter.hpp"
// パーサーコンビネーター
#include "cpp98_parser_combinator/parser_combinator.hpp"
#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib> // std::strtod
#include <limits>  // std::numeric_limits
#include <cmath>

struct Data {
  enum InputType {
    Char,
    Int,
    Double,
    Float
  };
  enum Category {
    Normal,
    Pseudo
  };

  InputType type;
  Category category;
  std::string value;

  Data() {}
  Data(InputType type, Category category, std::string value):type(type), category(category), value(value) {}
};

// helper functor

struct VecCharToString {
  std::string operator()(const std::vector<char> v) const {
    std::string s(v.begin(), v.end());
    return s;
  }
};

// ```
// N: 0-9
// N.N
// ```
// のような表記の際に文字列を接続する
struct NumsPointNumsConcat2 {
  std::string operator()(const std::pair<std::string, std::string> v) const {
    return v.first + "." + v.second;
  }
};

// 指数表記の際の処理
struct ExponentialToString {
  std::string operator()(const std::pair<std::string, std::pair<std::string, std::string> > v) const {
    return v.first + "e" + (v.second.first == "-"? "-" : "") /* sign */ + v.second.second /* exponential */;
  }
};


// === Int Map ===

struct IntToData {
  Data operator()(std::pair<std::string, std::string> input) const {
    return Data(Data::Int, Data::Normal, (input.first == "-"? "-" : "") + input.second);
  }
};


// === Double Map ===

struct DoubleToData {
  Data operator()(const std::pair<std::string, std::string >& input) const {
    return Data(Data::Double, Data::Normal, (input.first == "-"? "-" : "") + input.second);
  }
};

struct SpecialDoubleToData {
  Data operator()(const std::pair<std::string, std::string >& input) const {
    return Data(Data::Double, Data::Pseudo, (input.first == "-"? "-" : "") + input.second);
  }
};

// === Float Map ===

struct FloatToData {
  Data operator()(const std::pair<std::string, std::string >& input) const {
    return Data(Data::Float, Data::Normal, (input.first == "-"? "-" : "") + input.second);
  }
};

struct SpecialFloatToData {
  Data operator()(const std::pair<std::string, std::string >& input) const {
    return Data(Data::Float, Data::Pseudo, (input.first == "-"? "-" : "") + input.second);
  }
};

// === Char Map ===

struct AsciiToData {
  Data operator()(const std::string& input) const {
    return Data(Data::Char, Data::Normal, input);
  }
};


// helper function to generate parser

std::vector<StringParser<std::string::const_iterator> > generate_ascii_parser() {
  std::vector<StringParser<std::string::const_iterator> > v;
  for (char c = ' '; c <= '~'; c++) {
    std::string s(1, c);
    v.push_back(StringParser<std::string::const_iterator>(s));
  }
  return v;
}

ParseResult<std::string::const_iterator, Data> parsing(std::string& s) {
  typedef std::string::const_iterator Iter;

  typedef ChoiceParser<CharParser<Iter> > CharP;
  typedef StringParser<Iter> StringP;
  typedef OrParser<OrParser<StringP, StringP>, StringP> PlusMinus;
  typedef Many1Parser<CharP> Nums;

  typedef MapParser<Nums, VecCharToString, std::string> NumsM; // Nums to String

  typedef ThenParser<PlusMinus, NumsM> IntP;
  typedef MapParser<IntP, IntToData, Data> IntM;

  typedef ThenParser<ThenIgnoreParser<NumsM, CharParser<Iter> >, NumsM> NumsPointNumsP;

  typedef MapParser<NumsPointNumsP, NumsPointNumsConcat2, std::string> NumsPointNumsM;

  typedef 
    ThenParser<
      NumsPointNumsM, 
      IgnoreThenParser<ThenParser<PlusMinus, NumsM>, CharParser<Iter> > >  ExponentialP; // 指数表記

  typedef MapParser<ExponentialP, ExponentialToString, std::string> ExponentialM;

  typedef ThenParser<PlusMinus, OrParser<ExponentialM, NumsPointNumsM> > DoubleP;

  typedef ThenParser<PlusMinus, OrParser<StringP, StringP> > SpecialDoubleP;
  typedef MapParser<DoubleP, DoubleToData, Data> DoubleM;
  typedef MapParser<SpecialDoubleP, SpecialDoubleToData, Data> SpecialDoubleM;

  typedef ThenIgnoreParser<DoubleP, CharParser<Iter> > FloatP;
  typedef ThenIgnoreParser<SpecialDoubleP, CharParser<Iter> > SpecialFloatP;
  typedef MapParser<FloatP, FloatToData, Data> FloatM;
  typedef MapParser<SpecialFloatP, SpecialFloatToData, Data> SpecialFloatM;

  typedef ChoiceParser<StringP> AsciiP;
  typedef MapParser<AsciiP, AsciiToData, Data> AsciiM;

  typedef ThenIgnoreParser< OrParser< FloatM, OrParser< DoubleM, OrParser< SpecialFloatM, OrParser< SpecialDoubleM, OrParser< IntM, AsciiM > > > > >, EofParser<Iter> > NumberP;

  // stringやchar
  CharParser<Iter> num_set[] = {
    chr<Iter>('0'),
    chr<Iter>('1'),
    chr<Iter>('2'),
    chr<Iter>('3'),
    chr<Iter>('4'),
    chr<Iter>('5'),
    chr<Iter>('6'),
    chr<Iter>('7'),
    chr<Iter>('8'),
    chr<Iter>('9'),
  };

  std::vector<StringParser<Iter> > ascii_set = generate_ascii_parser();

  CharP char_p = choice(num_set);
  Nums nums_p = many1(char_p);
  PlusMinus plus_minus_p = StringP("+") | StringP("-") | StringP("");
  StringP inf_p = StringP("inf");
  StringP nan_p = StringP("nan");

  // 連続する数字の表記
  NumsM nums_m = map_p<std::string>(nums_p, VecCharToString());

  IntP int_p = plus_minus_p & nums_m;
  IntM int_m = map_p<Data>(int_p, IntToData());

  NumsPointNumsP nums_point_nums = thenignore_p(nums_m, chr<Iter>('.')) & nums_m;
  NumsPointNumsM nums_point_nums_m = map_p<std::string>(nums_point_nums, NumsPointNumsConcat2());

  ExponentialP exponential_p = nums_point_nums_m & ignorethen_p(plus_minus_p & nums_m, chr<Iter>('e'));
  ExponentialM exponential_m = map_p<std::string>(exponential_p, ExponentialToString());

  DoubleP double_p = plus_minus_p & (exponential_m | nums_point_nums_m);
  DoubleM double_m = map_p<Data>(double_p, DoubleToData());

  SpecialDoubleP special_double_p = plus_minus_p & (inf_p | nan_p);
  SpecialDoubleM special_double_m = map_p<Data>(special_double_p, SpecialDoubleToData());

  FloatP float_p = thenignore_p(double_p, chr<Iter>('f'));
  FloatM float_m = map_p<Data>(float_p, FloatToData());

  SpecialFloatP special_float_p = thenignore_p(special_double_p, chr<Iter>('f'));
  SpecialFloatM special_float_m = map_p<Data>(special_float_p, SpecialFloatToData());

  AsciiP ascii_p = choice(ascii_set);
  AsciiM ascii_m = map_p<Data>(ascii_p, AsciiToData());

  NumberP number_p = thenignore_p((float_m | (double_m | (special_float_m | (special_double_m | (int_m | ascii_m))))), eof_p<Iter>());

  // ここから
  std::string::const_iterator it = s.begin();
  std::string::const_iterator end = s.end();

  return number_p.parse(it, end);
}

void ScalarConverter::convert(std::string& data) {
  ParseResult<std::string::const_iterator, Data> parsed_data = parsing(data);

  if (parsed_data.success) {
    switch (parsed_data.value.type) {
      
      // =========================================================
      // Double
      // =========================================================
      case Data::Double:
        switch (parsed_data.value.category) {
          case Data::Normal:
            {
              double d_val = std::strtod(parsed_data.value.value.c_str(), NULL);

              // [char へのキャスト]
              if (d_val < std::numeric_limits<char>::min() || d_val > std::numeric_limits<char>::max()) {
                std::cout << "char: impossible\n";
              } else {
                char c = static_cast<char>(d_val);
                if (std::isprint(c)) {
                  std::cout << "char: '" << c << "'\n";
                } else {
                  std::cout << "char: Non displayable\n";
                }
              }

              // [int へのキャスト]
              if (d_val < std::numeric_limits<int>::min() || d_val > std::numeric_limits<int>::max()) {
                std::cout << "int: impossible\n";
              } else {
                std::cout << "int: " << static_cast<int>(d_val) << "\n";
              }

              double threshold = std::pow(10, std::cout.precision());
              // [float へのキャスト]
              if (d_val < -std::numeric_limits<float>::max() || d_val > std::numeric_limits<float>::max()) {
                std::cout << "float: impossible\n";
              } else {
                float f_val = static_cast<float>(d_val);
                std::cout << "float: " << f_val;
                // 安全な .0 付与（巨大な数値での未定義動作を防ぐ）
                if (f_val > -threshold && f_val < threshold && f_val == static_cast<int>(f_val)) {
                  std::cout << ".0";
                }
                std::cout << "f\n";
              }

              // [double の出力]
              std::cout << "double: " << d_val;
              if (d_val > -threshold && d_val < threshold && d_val == static_cast<int>(d_val)) {
                std::cout << ".0";
              }
              std::cout << "\n";
            }
            break;
          case Data::Pseudo:
            {
              std::cout << "char: impossible\n";
              std::cout << "int: impossible\n";
              std::cout << "float: " << parsed_data.value.value << "f\n";
              std::cout << "double: " << parsed_data.value.value << "\n";
            }
            break;
        }
        break;

      // =========================================================
      // Float
      // =========================================================
      case Data::Float:
        switch (parsed_data.value.category) {
          case Data::Normal:
            {
              float f_val = static_cast<float>(std::strtod(parsed_data.value.value.c_str(), NULL));

              // [char へのキャスト]
              if (f_val < std::numeric_limits<char>::min() || f_val > std::numeric_limits<char>::max()) {
                std::cout << "char: impossible\n";
              } else {
                char c = static_cast<char>(f_val);
                if (std::isprint(c)) {
                  std::cout << "char: '" << c << "'\n";
                } else {
                  std::cout << "char: Non displayable\n";
                }
              }

              // [int へのキャスト]
              if (f_val < static_cast<float>(std::numeric_limits<int>::min()) || 
                  f_val > static_cast<float>(std::numeric_limits<int>::max())) {
                std::cout << "int: impossible\n";
              } else {
                std::cout << "int: " << static_cast<int>(f_val) << "\n";
              }

              double threshold = std::pow(10, std::cout.precision());

              // [float の出力]
              std::cout << "float: " << f_val;
              if (f_val > -threshold && f_val < threshold && f_val == static_cast<int>(f_val)) {
                std::cout << ".0";
              }
              std::cout << "f\n";

              // [double へのキャスト]
              double d_val = static_cast<double>(f_val);
              std::cout << "double: " << d_val;
              if (d_val > -threshold && d_val < threshold && d_val == static_cast<int>(d_val)) {
                std::cout << ".0";
              }
              std::cout << "\n";
            }
            break;
          case Data::Pseudo:
            {
              std::cout << "char: impossible\n";
              std::cout << "int: impossible\n";
              std::cout << "float: " << parsed_data.value.value << "f\n";
              std::cout << "double: " << parsed_data.value.value << "\n";
            }
            break;
        }
        break;

      // =========================================================
      // Int
      // =========================================================
      case Data::Int:
        {
          // 構文はInt（数字列）だが、限界突破に備えて double の器で実体化する
          double d_val = std::strtod(parsed_data.value.value.c_str(), NULL);

          // [char へのダウンキャスト]
          if (d_val < std::numeric_limits<char>::min() || d_val > std::numeric_limits<char>::max()) {
            std::cout << "char: impossible\n";
          } else {
            char c = static_cast<char>(d_val);
            if (std::isprint(c)) {
              std::cout << "char: '" << c << "'\n";
            } else {
              std::cout << "char: Non displayable\n";
            }
          }

          // [int へのチェックと出力]
          // ここで「構文はIntだが、intの器から溢れている」ものを弾く
          if (d_val < std::numeric_limits<int>::min() || d_val > std::numeric_limits<int>::max()) {
            std::cout << "int: impossible\n";
          } else {
            std::cout << "int: " << static_cast<int>(d_val) << "\n";
          }

          double threshold = std::pow(10, std::cout.precision());

          // [float へのアップキャスト]
          float f_val = static_cast<float>(d_val);
          std::cout << "float: " << f_val;
          // 元が純粋な数字列であっても、floatの精度丸めで小数になる可能性はゼロではないため安全策をとる
          if (f_val > -threshold && f_val < threshold && f_val == static_cast<int>(f_val)) {
            std::cout << ".0";
          }
          std::cout << "f\n";

          // [double へのアップキャスト]
          std::cout << "double: " << d_val;
          if (d_val > -threshold && d_val < threshold && d_val == static_cast<int>(d_val)) {
            std::cout << ".0";
          }
          std::cout << "\n";
        }
        break;

      // =========================================================
      // Char
      // =========================================================
      case Data::Char:
        {
          char c_val = parsed_data.value.value[0];

          std::cout << "char: '" << c_val << "'\n";
          std::cout << "int: " << static_cast<int>(c_val) << "\n";
          
          // Charは絶対に100万を超えず、小数部も持たないため無条件で .0f をつけてOK
          std::cout << "float: " << static_cast<float>(c_val) << ".0f\n";
          std::cout << "double: " << static_cast<double>(c_val) << ".0\n";
        }
        break;
    }
  } else {
    // パース失敗時
    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";
    std::cout << "float: impossible\n";
    std::cout << "double: impossible\n";
  }
}
