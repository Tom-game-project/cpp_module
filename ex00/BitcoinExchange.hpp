#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <utility>
#include <string>

// ============================= parser combinator ============================= (ここから)

template <typename Iterator, typename ValueType>
struct ParseResult {
  bool success;
  ValueType value;
  Iterator next;

  ParseResult(bool s, ValueType v, Iterator n): success(s), value(v), next(n) {}
};

template <typename Parser1, typename Parser2>
struct ThenParser {
  typedef std::pair<typename Parser1::value_type, typename Parser2::value_type>  value_type;
  Parser1 p1;
  Parser2 p2;

  ThenParser(const Parser1& a, const Parser2& b) : p1(a), p2(b) {}

  template <typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    ParseResult<Iterator, typename Parser1::value_type> res1 = p1.parse(it, end);
    if (!res1.success)
      return ParseResult<Iterator, value_type>(false, value_type(), it);
    ParseResult<Iterator, typename Parser2::value_type> res2 = p2.parse(res1.next, end);
    if (!res2.success)
      return ParseResult<Iterator, value_type>(false, value_type(), it);
    return ParseResult<Iterator, value_type>(true, std::make_pair(res1.value, res2.value), res2.next);
  }
};

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

    ParseResult<Iterator, value_type> res2 = p2.parse(it, end);
    return res2;
  }
};

template <typename TargetParser/*本命*/, typename PadParser/*無視*/>
struct ThenIgnoreParser {
  typedef typename TargetParser::value_type value_type;
  TargetParser target_parser;
  PadParser pad_parser;

  ThenIgnoreParser(const TargetParser& target_parser, const PadParser& pad_parser): target_parser(target_parser), pad_parser(pad_parser) {} 

  template <typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    ParseResult<Iterator, value_type> res_target = this->target_parser.parse(it, end);
    if (!res_target.success) 
      return ParseResult<Iterator, value_type>(false, value_type(), it);
    ParseResult<Iterator, typename PadParser::value_type> res2_pad = this->pad_parser.parse(res_target.next, end);
    if (!res2_pad.success) 
      return ParseResult<Iterator, value_type>(false, value_type(), it);
    // 本命の値だけを取り出す
    return ParseResult<Iterator, value_type>(true, res_target.value, res2_pad.next);
  }
};

template <typename Parser>
struct ManyCharParser {
  typedef std::string value_type;
  Parser p;

  ManyCharParser(const Parser& a): p(a) {}
  // すべての要素がparserを

  template<typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    ManyCharParser::value_type results;
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

template<typename P>
ManyCharParser<P> manychar_p(const P& p) {
  return ManyCharParser<P>(p);
}

template <typename Iterator>
struct CharParser {
  typedef char value_type;
  char target;

  CharParser() : target('\0') {}
  CharParser(char c) : target(c) {}

  ParseResult<Iterator, char> parse(Iterator it, Iterator end) const {
    if (it != end /*終端に到達しておらず*/ && *it == this->target /*target文字列にマッチしている*/) {
      return ParseResult<Iterator, value_type>(true, *it, it + 1);
    }
    return ParseResult<Iterator, value_type>(false, '\0', it);
  }
};

template <typename Parser, std::size_t N>
struct FixedChoiceParser {
  typedef typename Parser::value_type value_type;
  Parser ps[N];

  // FixedChoiceParser(Parser ps[N]): ps(ps) {}
  FixedChoiceParser(const Parser (&arr)[N]) {
  // 初期化子リストは使わず、forループで1つずつ安全にコピーする
    for (std::size_t i = 0; i < N; ++i) {
      this->ps[i] = arr[i];
    }
  }

  template<typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    for (std::size_t i = 0; i < N; i++) {
      ParseResult<Iterator, value_type> res = this->ps[i].parse(it, end);
      if (res.success) return res;
    }
    return ParseResult<Iterator, value_type>(false, value_type(), it);
  }
};

template <typename ParserT, typename FuncT, typename OutValueT>
struct MapParser {
  // 変換後の型を、このパーサーの value_type として公開する
  typedef OutValueT value_type;

  ParserT p;
  FuncT f; // 変換処理を行う関数オブジェクト

  MapParser(const ParserT& parser, FuncT func) : p(parser), f(func) {}

  template <typename Iterator>
  ParseResult<Iterator, OutValueT> parse(Iterator it, Iterator end) const {
    // まず中のパーサーを実行
    ParseResult<Iterator, typename ParserT::value_type> res = p.parse(it, end);

    if (res.success) {
      OutValueT mapped_value = f(res.value);
      return ParseResult<Iterator, OutValueT>(true, mapped_value, res.next);
    }

    return ParseResult<Iterator, OutValueT>(false, OutValueT(), it);
  }
};

template <typename OutValueT, typename ParserT, typename FuncT>
MapParser<ParserT, FuncT, OutValueT> map_p(const ParserT& p, FuncT f) {
    return MapParser<ParserT, FuncT, OutValueT>(p, f);
}

template <typename P, std::size_t N> 
FixedChoiceParser<P, N> fixedchoice(const P (&ps)[N]) {
  return FixedChoiceParser<P, N>(ps);
}

template <typename Iterator>
CharParser<Iterator> chr(char c) {
  return CharParser<Iterator>(c);
}

template <typename P1, typename P2>
ThenParser<P1, P2> operator&(const P1& p1, const P2& p2) {
  return ThenParser<P1, P2>(p1, p2);
}

template <typename P1, typename P2>
OrParser<P1, P2> operator|(const P1& p1, const P2& p2) {
  return OrParser<P1, P2>(p1, p2);
}

template <typename TargetParser, typename PadParser>
ThenIgnoreParser<TargetParser, PadParser>thenignore_p(
  const TargetParser& target_parser,
  const PadParser& pad_parser
) {
  return ThenIgnoreParser<TargetParser, PadParser>(target_parser, pad_parser);
}

template <typename Parser>
struct Many1CharParser {
  typedef std::string value_type;
  Parser p;

  Many1CharParser(const Parser& a): p(a) {}

  template<typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    Many1CharParser::value_type results;
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
    if (results.empty())
      return ParseResult<Iterator, value_type>(false, value_type(), it);
    return ParseResult<Iterator, value_type>(true, results, current);
  }
};

template <typename P>
Many1CharParser<P> many1char_p(const P& p) {
  return Many1CharParser<P>(p);
}

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

template <typename TargetParser, typename PadParser>
struct PaddedParser {
  typedef typename TargetParser::value_type value_type;
  TargetParser target_parser;
  PadParser pad_parser;

  PaddedParser(const TargetParser& target_parser, const PadParser& pad_parser): target_parser(target_parser), pad_parser(pad_parser) {} 

  template <typename Iterator>
  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    ParseResult<Iterator, typename PadParser::value_type> res1_pad = this->pad_parser.parse(it, end);
    if (!res1_pad.success)
      return ParseResult<Iterator, value_type>(false, value_type(), it);
    ParseResult<Iterator, value_type> res_target = this->target_parser.parse(res1_pad.next, end);
    if (!res_target.success) 
      return ParseResult<Iterator, value_type>(false, value_type(), it);
    ParseResult<Iterator, typename PadParser::value_type> res2_pad = this->pad_parser.parse(res_target.next, end);
    if (!res2_pad.success) 
      return ParseResult<Iterator, value_type>(false, value_type(), it);
    // 本命の値だけを取り出す
    return ParseResult<Iterator, value_type>(true, res_target.value, res2_pad.next);
  }
};

template <typename TargetParser, typename PadParser>
PaddedParser<TargetParser, PadParser>padded_p(
  const TargetParser& target_parser,
  const PadParser& pad_parser
) {
  return PaddedParser<TargetParser, PadParser>(target_parser, pad_parser);
}

template <typename Iterator>
struct EofParser {
  typedef bool value_type; // 返す値に意味はない

  EofParser() {}

  ParseResult<Iterator, value_type> parse(Iterator it, Iterator end) const {
    if (it == end) {
      return ParseResult<Iterator, value_type>(true, true, it);
    }
    return ParseResult<Iterator, value_type>(false, false, it);
  }
};

template <typename Iterator>
EofParser<Iterator> eof_p() {
  return EofParser<Iterator>();
}

// ============================= parser combinator ============================= (ここまで)

int func();

#endif
