#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "parser_combinator.hpp"


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
    ParseResult<std::string::const_iterator, std::string> res = 
        hello_then_workd.parse(it, end);

    if (res.success) {
      std::cout << "Success: " << res.value << std::endl;
    } else {
      std::cout << "Failed" << std::endl;
    }
  }

  // ========================================================== test02
  {
    typedef ChoiceParser<CharParser<std::string::const_iterator > > SomeChar;
    typedef ManyParser<SomeChar> Word;

    std::string input = "abcd";
    
    std::string::const_iterator it = input.begin();
    std::string::const_iterator end = input.end();

    CharParser<std::string::const_iterator > choice_char[6] = {
        chr<std::string::const_iterator>('a'),
        chr<std::string::const_iterator>('b'),
        chr<std::string::const_iterator>('c'),
        chr<std::string::const_iterator>('d'),
        chr<std::string::const_iterator>('e'),
        chr<std::string::const_iterator>('f')
    };

    Word some_word = many(choice(choice_char));
    ParseResult<std::string::const_iterator, std::vector<char> > res =
      some_word.parse(it, end);

    if (res.success) {
      for (std::size_t i = 0; i < res.value.size(); i++) {
        std::cout << "パースした文字 " << res.value[i] << std::endl;
      }
    } else {
      std::cout << "Failed" << std::endl;
    }
  }

  // ========================================================== test03
  {

  }

  return 0;
}
