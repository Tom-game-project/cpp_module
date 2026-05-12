#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

namespace Ope {
  enum Ope {
    Add,
    Sub,
    Mul,
    Div
  };
}

struct Inst {
  enum Type {
    Number,
    Ope
  } ty;
  union {
    int number_value;
    Ope::Ope ope_value;
  } value;
};

template <typename T, typename E>
struct Result {
  enum {
    Ok,
    Err
  } ty;
  T ok_value;
  E err_value;
};

struct Error {
};

Result<std::stack<Inst>, Error> interpret_string_as_rpn(std::string code);
Result<int, Error> rpn_runtime(std::stack<Inst>& r_stack);

#endif
