#include "ScalarConverter.hpp"
// パーサーコンビネーター
#include "cpp98_parser_combinator/parser_combinator.hpp"
#include <cassert>
#include <string>
#include <utility>
#include <vector>

namespace InputType {
  enum InputType {
    Char,
    Int,
    Double,
    Float
  };
}

struct Data {
  InputType::InputType type;
  std::string value;

  Data() {}
  Data(InputType::InputType t, std::string v):type(t), value(v) {}
};

struct VecCharToString {
  std::string operator()(const std::vector<char> v) const {
    std::string s(v.begin(), v.end());
    return s;
  }
};

struct IntToData {
  Data operator()(std::pair<std::string, std::string> input) const {
    if (input.first == "+") {
      return Data(InputType::Int, input.second);
    } else if (input.first == "-") {
      return Data(InputType::Int, input.first + input.second);
    } else if (input.first == "") {
      return Data(InputType::Int, input.second);
    } else {
      return Data();
    }
    // unreachable
  }
};

struct DoubleToData {
  Data operator()(const std::pair<std::string, std::pair<std::string, std::string> >& input) const {
    if (input.first == "+") {
      return Data(InputType::Double, input.second.first + "." + input.second.second);
    } else if (input.first == "-") {
      return Data(InputType::Double, input.first +  input.second.first + "." + input.second.second);
    } else if (input.first == "") {
      return Data(InputType::Double, input.second.first + "." + input.second.second);
    } else {
      return Data();
    }
    // unreachable
  }
};

struct FloatToData {
  Data operator()(const std::pair<std::string, std::pair<std::string, std::string> >& input) const {
    if (input.first == "+") {
      return Data(InputType::Float, input.second.first + "." + input.second.second);
    } else if (input.first == "-") {
      return Data(InputType::Float, input.first +  input.second.first + "." + input.second.second);
    } else if (input.first == "") {
      return Data(InputType::Float, input.second.first + "." + input.second.second);
    } else {
      return Data();
    }
    // unreachable
  }
};


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
 
  typedef ThenParser<PlusMinus, NumsPointNumsP> DoubleP;
  typedef MapParser<DoubleP, DoubleToData, Data> DoubleM;

  typedef ThenIgnoreParser<DoubleP, CharParser<Iter> > FloatP;
  typedef MapParser<FloatP, FloatToData, Data> FloatM;

  typedef OrParser<OrParser<FloatM, DoubleM>, IntM> NumberP;

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

  CharP char_p = choice(num_set);

  Nums nums_p = many1(char_p);

  PlusMinus plus_minus_p = StringP("+") | StringP("-") | StringP("");

  // 連続する数字の表記
  NumsM nums_m = map_p<std::string>(nums_p, VecCharToString());

  IntP int_p = plus_minus_p & nums_m;
  IntM int_m = map_p<Data>(int_p, IntToData());

  NumsPointNumsP nums_point_nums = thenignore_p(nums_m, chr<Iter>('.')) & nums_m;
  
  DoubleP double_p = plus_minus_p & nums_point_nums; 
  DoubleM double_m = map_p<Data>(double_p, DoubleToData());

  FloatP float_p = thenignore_p(double_p, chr<Iter>('f'));
  FloatM float_m = map_p<Data>(float_p, FloatToData());


  NumberP number_p = float_m | double_m | int_m;

  // ここから
  std::string::const_iterator it = s.begin();
  std::string::const_iterator end = s.end();

  ParseResult<Iter, Data> parsed_data = number_p.parse(it, end);

  if (parsed_data.success) {
    switch (parsed_data.value.type) {
      case InputType::Double:
        std::cout << "parsed double :" << parsed_data.value.value << std::endl;
        break;
      case InputType::Float:
        std::cout << "parsed float :" << parsed_data.value.value << std::endl;
        break;
      case InputType::Int:
        std::cout << "parsed int :" << parsed_data.value.value << std::endl;
        break;
      case InputType::Char:
        std::cout << "parsed char :" << parsed_data.value.value << std::endl;
        break;
    }
  }
}

void ScalarConverter::convert(std::string& data) {
  parsing(data);
}
