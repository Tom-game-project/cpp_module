#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "parser_combinator.hpp"

// 文字列を格納するノード
struct StringNode {
  std::string value;
  
  StringNode(): value("") {}
  StringNode(std::string value): value(value) {}
};

struct KeyValueNode;
typedef  std::vector<KeyValueNode*> BraceNode;

struct KeyValueNode {
  std::string key;
  std::vector<std::string> values;
  BraceNode brace_node;
};

// std::vector<char>をstd::stringにする関数
struct VecCharToString {
  std::string operator()(const std::vector<char> v) const {
    std::string s(v.begin(), v.end());
    return s;
  }
};

// struct LineToKeyValueNode {
//   KeyValueNode operator()(const )
// }

struct SampleStruct {
  SampleStruct(): a(""), b("") {}
  SampleStruct(std::string a, std::string b):a(a), b(b){}
  std::string a;
  std::string b;
};

struct PairToSampleStruct {
  SampleStruct operator()(const std::pair<std::string, std::string> v) const {
    return SampleStruct(v.first, v.second);
  }
};

std::vector<CharParser<std::string::const_iterator> > generate_word_char() {
  std::vector<CharParser<std::string::const_iterator> > c_list;

  for (char i = 'a'; i <= 'z'; i++)
    c_list.push_back(CharParser<std::string::const_iterator>(i));
  for (char i = 'A'; i <= 'Z'; i++)
    c_list.push_back(CharParser<std::string::const_iterator>(i));
  for (char i = '0'; i <= '9'; i++)
    c_list.push_back(CharParser<std::string::const_iterator>(i));
  c_list.push_back(CharParser<std::string::const_iterator>('-'));
  c_list.push_back(CharParser<std::string::const_iterator>('_'));
  return c_list;
}


int main() {
  // ========================================================== test00 
  {
    typedef StringParser<std::string::const_iterator> Word; // hello

    typedef OrParser<Word, Word> HELLOorWORLD;
    // typedef ThenParser<Word, Word> HELLOthenWORLD;
    // typedef OrParser<OrParser<C, C>, C> AorBorC;

    std::string input = "hello";
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();

    // 'a' または 'b' をパースするパーサー

    Word word_hello = str<std::string::const_iterator>("hello");
    Word word_world = str<std::string::const_iterator>("world");

    HELLOorWORLD hello_or_world = word_hello | word_world;

    // (chr('a') | chr('b')).parse(...) と書く
    ParseResult<std::string::const_iterator, std::string> res = 
        hello_or_world.parse(it, end);

    if (res.success) {
      std::cout << "Success: " << res.value << std::endl;
    } else {
      std::cout << "Failed" << std::endl;
    }
  }

  // ========================================================== test01
  {
    typedef StringParser<std::string::const_iterator> Word; // hello
    // typedef OrParser<Word, Word> HELLOorWORLD;
    typedef ThenParser<Word, Word> HELLOthenWORLD;

    Word word_hello = str<std::string::const_iterator>("hello");
    Word word_world = str<std::string::const_iterator>("world");

    std::string input = "helloworld";

    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();

    HELLOthenWORLD hello_then_workd = word_hello & word_world;
    ParseResult<std::string::const_iterator, std::pair<std::string, std::string> > res = 
        hello_then_workd.parse(it, end);

    if (res.success) {
      std::cout << "Success: " << res.value.first << std::endl;
      std::cout << "Success: " << res.value.second << std::endl;
    } else {
      std::cout << "Failed" << std::endl;
    }
  }

  // ========================================================== test02
  {
    typedef ChoiceParser<CharParser<std::string::const_iterator > > SomeChar;
    typedef Many1Parser<SomeChar> Word;
    typedef ManyParser<SomeChar> Padded;
    typedef PaddedParser<Word, Padded> PaddedWord;

    typedef MapParser<PaddedWord, VecCharToString, std::string> MapWord;

    typedef MapParser<ThenParser<MapWord, MapWord> , PairToSampleStruct, SampleStruct> MappedPair;

    std::string input = "  \n abcd  aaa\r";

    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();

    CharParser<std::string::const_iterator> padded_char[3] = {
        chr<std::string::const_iterator>(' '),
        chr<std::string::const_iterator>('\n'),
        chr<std::string::const_iterator>('\r'),
    };

    Word some_word = many1(choice(generate_word_char() /*a-z A-Z 0-9 -_*/));
    Padded padded_set = many(choice(padded_char));

    PaddedWord padded_word = padded_p(some_word, padded_set);

    MapWord map_word = map_p<std::string>(padded_word, VecCharToString());

    MappedPair pair = map_p<SampleStruct>(map_word & map_word, PairToSampleStruct());

    ParseResult<std::string::const_iterator, SampleStruct > res =
      pair.parse(it, end);

    if (res.success) {
      std::cout << "a \"" << res.value.a << "\"" << std::endl;
      std::cout << "b \"" << res.value.b << "\"" << std::endl;
    } else {
      std::cout << "Failed to parse: pair test" << std::endl;
    }
  }

  // ========================================================== test03
  //{
  //  // nginx like config file parser 
  //
  //  typedef ChoiceParser<CharParser<std::string::const_iterator > > SomeChar;
  //  typedef Many1Parser<SomeChar> Word; // 単語
  //  typedef ManyParser<SomeChar> Padded; // 空白
  //  typedef PaddedParser<Word, Padded> PaddedWord; // 空白処理語の単語
  //
  //  typedef PaddedParser< ThenIgnoreParser<ThenParser<PaddedWord, Many1Parser<PaddedWord> >, CharParser<std::string::const_iterator > > , Padded > Line;
  //
  //  // typedef MapParser<Line, , KeyValueNode> MappedLine;
  //
  //  std::string input = "  \n abcd  world; \r";
  //
  //  std::string::const_iterator it = input.begin();
  //  std::string::const_iterator end = input.end();
  //
  //  CharParser<std::string::const_iterator> padded_char[3] = {
  //      chr<std::string::const_iterator>(' '),
  //      chr<std::string::const_iterator>('\n'),
  //      chr<std::string::const_iterator>('\r'),
  //  };
  //
  //  Word some_word = many1(choice(generate_word_char() /*a-z A-Z 0-9 -_*/));
  //
  //  Padded padded_set = many(choice(padded_char));
  //  PaddedWord padded_word = padded_p(some_word, padded_set); // 空白を除いたword
  //
  //  Line line_parser = padded_p(
  //      thenignore_p( 
  //        padded_word & many1(padded_word),
  //        chr<std::string::const_iterator>(';')),
  //      padded_set);
  //
  //
  //  // Recursive<std::string::const_iterator, >
  //
  //}

  return 0;
}
