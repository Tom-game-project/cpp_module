#include "ScalarConverter.hpp"
// パーサーコンビネーター
#include "cpp98_parser_combinator/parser_combinator.hpp"
#include <cassert>
#include <string>
#include <utility>
#include <vector>

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

struct NumsPointNumsConcat2 {
  std::string operator()(const std::pair<std::string, std::string> v) const {
    return v.first + "." + v.second;
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

void parsing(std::string& s) {
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

  typedef ThenParser<PlusMinus, NumsPointNumsM> DoubleP;
  typedef ThenParser<PlusMinus, OrParser<StringP, StringP> > SpecialDoubleP;
  typedef MapParser<DoubleP, DoubleToData, Data> DoubleM;
  typedef MapParser<SpecialDoubleP, SpecialDoubleToData, Data> SpecialDoubleM;

  typedef ThenIgnoreParser<DoubleP, CharParser<Iter> > FloatP;
  typedef ThenIgnoreParser<SpecialDoubleP, CharParser<Iter> > SpecialFloatP;
  typedef MapParser<FloatP, FloatToData, Data> FloatM;
  typedef MapParser<SpecialFloatP, SpecialFloatToData, Data> SpecialFloatM;

  typedef ChoiceParser<StringP> AsciiP;
  typedef MapParser<AsciiP, AsciiToData, Data> AsciiM;

  typedef ThenIgnoreParser<
    OrParser<
      FloatM,
      OrParser<
        DoubleM,
        OrParser<
          SpecialFloatM,
          OrParser<
            SpecialDoubleM,
            OrParser<
              IntM,
              AsciiM
            >
          >
        >
      >
    >,
    EofParser<Iter> > NumberP;

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

  DoubleP double_p = plus_minus_p & nums_point_nums_m;
  DoubleM double_m = map_p<Data>(double_p, DoubleToData());

  SpecialDoubleP special_double_p = plus_minus_p & (inf_p | nan_p);
  SpecialDoubleM special_double_m = map_p<Data>(special_double_p, SpecialDoubleToData());

  FloatP float_p = thenignore_p(double_p, chr<Iter>('f'));
  FloatM float_m = map_p<Data>(float_p, FloatToData());

  SpecialFloatP special_float_p = thenignore_p(special_double_p, chr<Iter>('f'));
  SpecialFloatM special_float_m = map_p<Data>(special_float_p, SpecialFloatToData());

  AsciiP ascii_p = choice(ascii_set);
  AsciiM ascii_m = map_p<Data>(ascii_p, AsciiToData());

  NumberP number_p = 
    thenignore_p(
        (float_m | (double_m | (special_float_m | (special_double_m | (int_m | ascii_m))))), eof_p<Iter>());

  // ここから
  std::string::const_iterator it = s.begin();
  std::string::const_iterator end = s.end();

  ParseResult<Iter, Data> parsed_data = number_p.parse(it, end);

  if (parsed_data.success) {
    switch (parsed_data.value.type) {
      case Data::Double:
        switch (parsed_data.value.category) {
          case Data::Normal:
            std::cout << "parsed double normal:" << parsed_data.value.value << std::endl;
            break;
          case Data::Pseudo:
            std::cout << "parsed double pseudo:" << parsed_data.value.value << std::endl;
            break;
        }
        break;
      case Data::Float:
        switch (parsed_data.value.category) {
          case Data::Normal:
            std::cout << "parsed float normal:" << parsed_data.value.value << std::endl;
            break;
          case Data::Pseudo:
            std::cout << "parsed float pseudo:" << parsed_data.value.value << std::endl;
            break;
        }
        break;
      case Data::Int:
        std::cout << "parsed int :" << parsed_data.value.value << std::endl;
        break;
      case Data::Char:
        std::cout << "parsed char :" << parsed_data.value.value << std::endl;
        break;
    }
  }
}

void ScalarConverter::convert(std::string& data) {
  parsing(data);
}
