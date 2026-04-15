#ifndef PARSER_COMBINATOR_HPP
#define PARSER_COMBINATOR_HPP

#include <cstddef>
#include <string>

#include <iostream>
#include <ostream>
#include <vector>

template <typename Iterator, typename ValueType>
struct ParseResult {
  bool success;
  ValueType value;
  Iterator next;

  ParseResult(bool s, ValueType v, Iterator n): success(s), value(v), next(n) {}
};

/*
 * Parserは以下を実装している必要がある
 * 
 * - インスタンス化
 * - ParseResult<Iterator, char> parse
 */

template <typename Iterator>
struct CharParser {
  typedef char value_type;
  char target;
  CharParser(char c) : target(c) {}

  ParseResult<Iterator, char> parse(Iterator it, Iterator end) const {
    if (it != end /*終端に到達しておらず*/ && *it == this->target /*target文字列にマッチしている*/) {
      return ParseResult<Iterator, value_type>(true, *it, it + 1);
    }
    return ParseResult<Iterator, value_type>(false, '\0', it);
  }
};

template <typename Iterator>
struct StringParser {
  typedef std::string value_type;
  std::string target;
  
  StringParser(std::string s) : target(s) {}

  ParseResult<Iterator, std::string> parse(Iterator it, Iterator end) const {
    Iterator current = it;

    for (std::size_t i = 0; i < this->target.length(); ++i) {
      // std::cout << "今の文字列　" << *current << std::endl;
      if (current == end || *current != target[i]) {
        // 失敗した場合は、一切進めていない元の 'it' を返す（バックトラックのため）
        return ParseResult<Iterator, value_type>(false, "", it);
      }
      ++current;
    }
    return ParseResult<Iterator, value_type>(true, this->target, current);
  }
};

// ヘルパー関数（autoがないC++98では、型推論させるためにヘルパー関数が必須）
template <typename Iterator>
CharParser<Iterator> chr(char c) {
  return CharParser<Iterator>(c);
}

template <typename Iterator>
StringParser<Iterator> str(std::string s) {
  return StringParser<Iterator>(s);
}

template <typename Parser1, typename Parser2>
// where Parser1, Parser2: 
struct OrParser {
  typedef typename Parser1::value_type value_type;
  Parser1 p1;
  Parser2 p2;

  OrParser(const Parser1& a, const Parser2& b) : p1(a), p2(b) {}

  template <typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    // まずp1を試す
    ParseResult<Iterator, value_type> res1 = p1.parse(it, end);
    if (res1.success) return res1;
    // ダメならp2を試す
    return p2.parse(it, end);
  }

};

template <typename Parser>
struct ChoiceParser {
  typedef typename Parser::value_type value_type;
  std::vector<Parser> ps;

  ChoiceParser(std::vector<Parser> ps): ps(ps) {}

  template<typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    for (std::size_t i = 0; i < this->ps.size(); i++) {
      ParseResult<Iterator, value_type> res = this->ps[i].parse(it, end);
      if (res.success) return res;
    }
    return ParseResult<Iterator, value_type>(false, value_type(), it);
  }
};

template <typename Parser1, typename Parser2>
struct ThenParser {
  typedef typename Parser1::value_type value_type;
  Parser1 p1;
  Parser2 p2;

  ThenParser(const Parser1& a, const Parser2& b) : p1(a), p2(b) {}

  template <typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    ParseResult<Iterator, value_type> res1 = p1.parse(it, end);
    if (res1.success) {
      ParseResult<Iterator, value_type> res2 = p2.parse(res1.next, end);
      return res2;
    }
    return ParseResult<Iterator, value_type>(false, value_type(), it);
  }
};

// ManyParserはThen<P, Then<P, Then<P, ...>>>
// と同じ意味を持つ
// ただし任意長
template <typename Parser>
struct ManyParser {
  typedef std::vector<typename Parser::value_type> value_type;
  Parser p;

  ManyParser(const Parser& a): p(a) {}
  // すべての要素がparserを

  template<typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    value_type results;  // = std::vector<typename Parser::value_type>();
    Iterator current = it;

    while (current != end) {
      ParseResult<Iterator, typename Parser::value_type> res = this->p.parse(current, end);
      if (!res.success)
        break;
      if (current == res.next)
        break;
      results.push_back(res.value);
      current = res.next;
    }
    return ParseResult<Iterator, value_type>(true, results, current);
  }
};

// 演算子オーバーロードで `chumsky` のような流れるAPI（DSL）を作る
template <typename P1, typename P2>
OrParser<P1, P2> operator|(const P1& p1, const P2& p2) {
  return OrParser<P1, P2>(p1, p2);
}

template <typename P1, typename P2>
ThenParser<P1, P2> operator&(const P1& p1, const P2& p2) {
  return ThenParser<P1, P2>(p1, p2);
}

template <typename P, std::size_t N>
ChoiceParser<P> choice(const P (&arr)[N]) {
  std::vector<P> ps(arr, arr + N);
  return ChoiceParser<P>(ps);
}

template <typename Parser>
ManyParser<Parser> many(const Parser& p) {
  return ManyParser<Parser>(p);
}

// パースが成功した場合にその情報を変換する
/*
template <typename Parser, typename FuncT, typename OutValueT>
struct MapParser {
  typedef typename Parser::value_type value_type; // 関数への入力となる
  Parser p;

  MapParser<Parser, FuncT, OutValueT>() {

  }
}
*/

#endif
