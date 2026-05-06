#include <cerrno>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>

// debug
#include <iostream>
#include <utility>

#include "BitcoinExchange.hpp"

typedef unsigned int YearT;  // 0000 - 9999
typedef unsigned int MonthT;
typedef unsigned int DayT;

template <typename T, typename E>
struct Result {
  enum {
    Ok,
    Err
  } ty;
  union {
    T ok_value;
    E err_value;
  } value;
};

struct Date {
  YearT year;
  MonthT month;
  DayT day;

  bool operator<(const Date& rhs) const {
    if (this->year != rhs.year) {
      return this->year < rhs.year;
    }
    if (this->month != rhs.month) {
      return this->month < rhs.month;
    }
    return this->day < rhs.day;
  }

  bool operator==(const Date& rhs) const {
    return this->year == rhs.year && this->month == rhs.month && this->day == rhs.day;
  }
};

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.year << "-"
       << std::setfill('0') << std::setw(2) << date.month << "-"
       << std::setfill('0') << std::setw(2) << date.day;
    return os;
}

namespace FailedReason {
enum FailedReason {
  BadInput
};
}

namespace ValueParseError {
  enum ValueParseError {
    StrtodErr // strtod error
  };
}

unsigned int interpret_char_as_int(char c) {
  return static_cast<unsigned int>(c - '0');
}

struct ToDate {
  Result<Date, FailedReason::FailedReason> operator()(const std::pair<std::pair<YearT, MonthT>, DayT> v) const {
    // // 1. 月と日の下限チェック
    Result<Date, FailedReason::FailedReason> r;

    YearT yyyy = v.first.first;
    MonthT mm = v.first.second;
    DayT dd = v.second;

    if (mm < 1 || mm > 12 || dd < 1) {
      r.ty = Result<Date, FailedReason::FailedReason>::Err;
      r.value.err_value = FailedReason::BadInput;
      return r;
    }

    // 2. 各月の日数テーブル（インデックス1〜12を使用するためにサイズ13で初期化）
    MonthT days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // 3. うるう年の補正
    if (mm == 2) {
      bool is_leap = (yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0);
      if (is_leap) {
        days_in_month[2] = 29;
      }
    }

    // 4. 日の上限チェック
    if (dd <= days_in_month[mm]) {
      Date rd;
      rd.year = yyyy;
      rd.month = mm;
      rd.day = dd;
      r.ty = Result<Date, FailedReason::FailedReason>::Ok;
      r.value.ok_value = rd;
      return r;
    } else {
      r.ty = Result<Date, FailedReason::FailedReason>::Err;
      r.value.err_value = FailedReason::BadInput;
      return r;
    }
  }
};

// 入力をyearに変換
// 0000 - 9999の入力のみを受け取る
// 必ず成功する。もし４桁でなければparse error
struct YearMap {
  YearT operator()(const std::pair<std::pair<std::pair<char, char>, char>, char> v) const {
    YearT year =
      interpret_char_as_int(v.first.first.first)  * 1000 +
      interpret_char_as_int(v.first.first.second) * 100  +
      interpret_char_as_int(v.first.second)       * 10   +
      interpret_char_as_int(v.second);
    return year;
  }
};

struct MonthMap {
  MonthT operator()(const std::pair<char, char> v) const {
    MonthT month =
      interpret_char_as_int(v.first) * 10 + 
      interpret_char_as_int(v.second);
    return month;
  }
};

struct DayMap {
  DayT operator()(const std::pair<char, char> v) const {
    MonthT day =
      interpret_char_as_int(v.first) * 10 + 
      interpret_char_as_int(v.second);
    return day;
  }
};

ParseResult<std::string::const_iterator, Result<Date, FailedReason::FailedReason> > date_parser(std::string input) {
  typedef std::string::const_iterator Iter;
  typedef CharParser<Iter> CharP;
  typedef FixedChoiceParser<CharP, 10> AnyCharP;
  typedef ThenParser<AnyCharP, AnyCharP> CharCharP;
  typedef CharCharP MonthP;  // MM

  typedef CharCharP DayP;    // DD
  typedef ThenParser<
    ThenParser<
      ThenParser<
        AnyCharP,
        AnyCharP>, 
      AnyCharP>,
    AnyCharP> YearP; // 0000-9999

  typedef MapParser<YearP, YearMap, YearT> YearM;
  typedef MapParser<MonthP, MonthMap, MonthT> MonthM;
  typedef MapParser<DayP, DayMap, DayT> DayM;

  typedef 
    ThenParser<
      ThenIgnoreParser<ThenParser<ThenIgnoreParser<YearM, CharP>, MonthM>, CharP>, 
      DayM
    > TimeStampFormatP;
  typedef MapParser<TimeStampFormatP, ToDate, Result<Date, FailedReason::FailedReason> > TimeStampFormatM;

  CharP num_set[] = {
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

  CharP sep_p = CharP('-');
  AnyCharP number_p = fixedchoice<CharP, 10>(num_set);

  YearP year_p = number_p & number_p & number_p & number_p;
  YearM year_m = map_p<YearT>(year_p, YearMap());

  CharCharP numnum_p = number_p & number_p;
  MonthM month_m = map_p<MonthT>(numnum_p, MonthMap());
  DayM day_m = map_p<DayT>(numnum_p, DayMap());

  TimeStampFormatP time_stamp_format_p = thenignore_p(thenignore_p(year_m, sep_p) & month_m/*month_p*/, sep_p) & day_m /*day_p*/;

  TimeStampFormatM time_stamp_format_m = map_p<Result<Date, FailedReason::FailedReason> >(time_stamp_format_p, ToDate());

  Iter it = input.begin();
  Iter end = input.end();
  ParseResult<Iter, Result<Date, FailedReason::FailedReason> > parsed_date = time_stamp_format_m.parse(it, end);

  return parsed_date;
}

struct NoEffect {
  std::string operator()(const std::string s) const {
    return s;
  }
};

struct DoubleConcat2 {
  std::string operator()(const std::pair<std::string, std::string> v) const {
    return v.first + "." + v.second;
  }
};

struct ToNumber {
  Result<double, ValueParseError::ValueParseError> operator()(const std::pair<std::string, std::string> v) const {
    char* endptr = NULL;
    errno = 0;

    double val = std::strtod((v.first + v.second).c_str(), &endptr);
    if (errno == ERANGE) {
        Result<double, ValueParseError::ValueParseError> r;
        r.ty = Result<double, ValueParseError::ValueParseError>::Err;
        r.value.err_value = ValueParseError::StrtodErr;
        return r;
    } else {
        Result<double, ValueParseError::ValueParseError> r;
        r.ty = Result<double, ValueParseError::ValueParseError>::Ok;
        r.value.ok_value = val;
        return r;
    }
  }
};

ParseResult<std::string::const_iterator, Result<double, ValueParseError::ValueParseError> > value_parser (std::string input) {
  typedef std::string::const_iterator Iter;
  typedef CharParser<Iter> CharP;
  typedef StringParser<Iter> StringP;
  typedef FixedChoiceParser<CharP, 10> AnyCharP;
  typedef FixedChoiceParser<CharP, 3> AnyPadCharP;

  typedef Many1CharParser<AnyCharP> DecimalP;
  typedef ManyCharParser<AnyPadCharP> PadP;
  // typedef MapParser<DecimalP, NoEffect, std::string> DecimalM;

  typedef ThenParser<ThenIgnoreParser<DecimalP, CharP>, DecimalP> DoubleP;
  typedef MapParser<DoubleP, DoubleConcat2, std::string> DoubleM;
  typedef OrParser<OrParser<StringP, StringP>, StringP> PlusMinusP;
  typedef ThenParser<PlusMinusP, OrParser<DoubleM, DecimalP> > NumberP;
  typedef MapParser<NumberP, ToNumber, Result<double, ValueParseError::ValueParseError> > NumberM;

  typedef PaddedParser<NumberM, PadP> PaddedNumberP;
  typedef ThenIgnoreParser<PaddedNumberP, EofParser<Iter> > JustNumberP;
  // typedef 

  CharP num_set[] = {
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

  CharP pad_set[] = {
    chr<Iter>(' '),
    chr<Iter>('\t'),
    chr<Iter>('\r'),
  };

  AnyCharP any_char_p = fixedchoice<CharP, 10>(num_set);
  AnyPadCharP any_pad_char_p = fixedchoice<CharP, 3>(pad_set);
  DecimalP decimal_p = many1char_p(any_char_p);

  PadP pad_p = manychar_p(any_pad_char_p);

  DoubleP double_p = thenignore_p(decimal_p, chr<Iter>('.')) & decimal_p;
  DoubleM double_m = map_p<std::string>(double_p, DoubleConcat2());

  PlusMinusP plus_minus_p = StringP("+") | StringP("-") | StringP("");
  NumberP number_p = plus_minus_p & (double_m | decimal_p);
  NumberM number_m = map_p<Result<double, ValueParseError::ValueParseError> >(number_p, ToNumber());

  PaddedNumberP padded_number_p = padded_p(number_m, pad_p);
  JustNumberP just_number_p = thenignore_p(padded_number_p, eof_p<Iter>());

  Iter it = input.begin();
  Iter end = input.end();
  ParseResult<Iter, Result<double, ValueParseError::ValueParseError> > parsed_result = just_number_p.parse(it, end);

  return parsed_result;
}

// errorが起こったときにはfalseを返す
bool load_csv_data(std::istringstream& csv_stream, std::map<Date, double>& r_map) {
  std::string line;
  // std::map<Date, double> r_map;

  if (std::getline(csv_stream, line)) {
    // 一行目は飛ばす
  }

  while (std::getline(csv_stream, line)) {

    if (!line.empty() && line[line.length() - 1] == '\r') {
      line.erase(line.length() - 1);
    }

    std::istringstream lineStream(line);
    std::string dateStr, priceStr;

    if (std::getline(lineStream, dateStr, ',')) {
      std::getline(lineStream, priceStr);

      ParseResult<std::string::const_iterator, Result<Date, FailedReason::FailedReason> > parsed_date = 
        date_parser(dateStr);
      ParseResult<std::string::const_iterator, Result<double, ValueParseError::ValueParseError> > parsed_result = 
        value_parser(priceStr);

      if (parsed_date.success) {
        switch (parsed_date.value.ty) {
          case Result<Date, FailedReason::FailedReason>::Ok:
            {
              Date date = parsed_date.value.value.ok_value;
              // std::cout << date.year << "-" << date.month << "-" << date.day << std::endl;

              if (parsed_result.success) {
                switch (parsed_result.value.ty) {
                  case Result<double, ValueParseError::ValueParseError>::Ok:
                    {
                      r_map.insert(std::make_pair(date, parsed_result.value.value.ok_value));
                      // std::cout << "Success to conv:" << parsed_result.value.value.ok_value << std::endl;
                    }
                    break;
                  case Result<double, ValueParseError::ValueParseError>::Err:
                    {
                      std::cerr << "load csv err: Failed to Convert" << std::endl;
                      return false;
                    }
                    break;
                }
              } else {
                // Failed to parse value
                std::cerr << "load csv err: Failed to parse" << std::endl;
                return false;
              }
            }
            break;
          case Result<Date, FailedReason::FailedReason>::Err:
            {
              // FailedReason::FailedReason fr = parsed_date.value.value.err_value;
              // switch (fr) {
              //   case FailedReason::BadInput:
              //     {
              //       std::cerr << "load csv err: BadInput" << std::endl;
              //       return false;
              //     }
              //     break;
              // }
              std::cerr << "load csv err: BadInput" << std::endl;
              return false;
            }
            break;
        }
      } else {
        // Failed to parse date
        std::cerr << "load csv err: failed to parse" << std::endl;
        return false;
      }
    }
  }
  return true;
}


void show_calc_result(Date& target_date, double rate, double price) {
  if (price < 0) {
    std::cerr << "Error: not a positive number" << std::endl;
  } else if (1000 < price) {
    // Error: too large a number
    std::cerr << "Error: too large a number" << std::endl;
  } else {
    double r = rate * price;
    std::cout << target_date << " => " << price << " = " << r << std::endl;
  }
}

bool load_user_input_and_show_result(std::istringstream& user_input_stream, std::map<Date, double>& csv_database_map) {
  std::string line;

  if (std::getline(user_input_stream, line)) {
    // 一行目は飛ばす
  }

  while (std::getline(user_input_stream, line)) {

    if (!line.empty() && line[line.length() - 1] == '\r') {
      line.erase(line.length() - 1);
    }

    std::istringstream lineStream(line);
    std::string dateStr, priceStr;

    if (std::getline(lineStream, dateStr, '|')) {
      std::getline(lineStream, priceStr);

      ParseResult<std::string::const_iterator, Result<Date, FailedReason::FailedReason> > parsed_date = 
        date_parser(dateStr);
      ParseResult<std::string::const_iterator, Result<double, ValueParseError::ValueParseError> > parsed_result = 
        value_parser(priceStr);

      if (parsed_date.success) {
        switch (parsed_date.value.ty) {
          case Result<Date, FailedReason::FailedReason>::Ok:
            {
              Date target_date = parsed_date.value.value.ok_value;

              if (parsed_result.success) {
                switch (parsed_result.value.ty) {
                  case Result<double, ValueParseError::ValueParseError>::Ok:
                    {
                      std::map<Date, double>::iterator it = csv_database_map.lower_bound(target_date);

                      // パターンA: ピッタリ同じ日付が見つかった場合
                      // (itがendではなく、かつ、指しているキーが探している日付と完全に一致する)
                      if (it != csv_database_map.end() && it->first == target_date) {
                        double price = it->second;
                        show_calc_result(target_date, price, parsed_result.value.value.ok_value);
                      }
                      // パターンB: 指定された日付が、データベースの一番古い日付よりもさらに過去だった場合
                      // (lower_boundがmapの先頭を返してきた場合)
                      else if (it == csv_database_map.begin()) {
                        std::cerr << "Error: No older date found in database for => " 
                                    << line << std::endl;
                      }
                      // パターンC: 日付がピッタリ存在しなかった場合（直近の過去を使う）
                      else {
                        // lower_boundは「未来」を指しているので、イテレータを1つ前に戻す(--)ことで
                        // 「直近の過去(lower date)」を取得できる
                        --it;
                        double price = it->second;
                        show_calc_result(target_date, price, parsed_result.value.value.ok_value);
                      }

                    }
                    break;
                  case Result<double, ValueParseError::ValueParseError>::Err:
                    {
                      std::cerr << "Error: failed to convert => " << priceStr << std::endl;
                    }
                    break;
                }
              } else {
                // Failed to parse value
                std::cerr << "Error: failed to parse data => " << line << std::endl;
              }
            }
            break;
          case Result<Date, FailedReason::FailedReason>::Err:
            {
              std::cerr << "Error: bad input => " << line << std::endl;
            }
            break;
        }
      } else {
        // Failed to parse date
        std::cerr << "Error: bad input => " << line << std::endl;
      }
    }
  }
  return true;
}


// errorの場合は1を返して終了
int func(char *file_name) {
  std::ifstream ifs("data.csv");

  if (!ifs.is_open()) {
    // ファイルが開けなかった場合のエラーハンドリング
    std::cerr << "Error: could not open database file. you have to set up data.csv" << std::endl;
    return 1;
  }
  // 2. ファイルの内容を一気に ostringstream に流し込み、string に変換する
  std::ostringstream csv_oss;
  csv_oss << ifs.rdbuf(); // 内部バッファを直接繋いで一気にコピー（C++98最速手法）
  std::string csv_content = csv_oss.str();

  ifs.close(); // 読み込み終わったのでファイルは閉じてOK

  // 3. 取得した文字列から目的の istringstream を作成する
  std::istringstream fileStream(csv_content);

  std::ifstream user_ifs(file_name);
  if (!user_ifs.is_open()) {
    // ファイルが開けなかった場合のエラーハンドリング
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }
  // 2. ファイルの内容を一気に ostringstream に流し込み、string に変換する
  std::ostringstream user_oss;
  user_oss << user_ifs.rdbuf(); // 内部バッファを直接繋いで一気にコピー（C++98最速手法）
  std::string user_content = user_oss.str();

  user_ifs.close(); // 読み込み終わったのでファイルは閉じてOK

  // 3. 取得した文字列から目的の istringstream を作成する
  std::istringstream userStream(user_content);

  std::map<Date, double> csv_database_map; // ここcsvから読んだ内容を格納する
  if (!load_csv_data(fileStream, csv_database_map)) {
    return 1;
  }

  load_user_input_and_show_result(userStream, csv_database_map);
  return 0;
}
