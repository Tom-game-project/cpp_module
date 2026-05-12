#include "RPN.hpp"

Result<std::stack<Inst>, Error> interpret_string_as_rpn(std::string code) {
  std::stack<Inst> r_stack;
  Result<std::stack<Inst>, Error> r;

  for (std::string::const_reverse_iterator rit = code.rbegin(); rit != code.rend(); ++rit) {
    char c = *rit; 

    if (' ' == c || '\t' == c) { // ignore pattern
    } else if ('0' <= c && c <= '9') {
      Inst inst;
      inst.ty = Inst::Number;
      inst.value.number_value = c - '0';
      r_stack.push(inst);
    } else if ('+' == c) {
      Inst inst;
      inst.ty = Inst::Ope;
      inst.value.ope_value = Ope::Add;
      r_stack.push(inst);
    } else if ('-' == c) {
      Inst inst;
      inst.ty = Inst::Ope;
      inst.value.ope_value = Ope::Sub;
      r_stack.push(inst);
    } else if ('*' == c) {
      Inst inst;
      inst.ty = Inst::Ope;
      inst.value.ope_value = Ope::Mul;
      r_stack.push(inst);
    } else if ('/' == c) {
      Inst inst;
      inst.ty = Inst::Ope;
      inst.value.ope_value = Ope::Div;
      r_stack.push(inst);
    } else {
      Error err;
      r.ty = Result<std::stack<Inst>, Error>::Err;
      r.err_value = err;
      return r;
    }
  }

  r.ty = Result<std::stack<Inst>, Error>::Ok;
  r.ok_value = r_stack;
  return r;
}

Result<int, Error> exec_operation(Inst inst, std::stack<int>& /*mut*/ workspace) {
  Result<int , Error> r;
  Error err;

  if (workspace.empty()) {
    r.ty = Result<int, Error>::Err;
    r.err_value = err;
    return r;
  }
  int b = workspace.top();
  workspace.pop();

  if (workspace.empty()) {
    r.ty = Result<int, Error>::Err;
    r.err_value = err;
    return r;
  }
  int a = workspace.top();
  workspace.pop();

  r.ty = Result<int, Error>::Ok;

  switch (inst.value.ope_value) {
    case Ope::Add:
      {
        r.ok_value = a + b;
      }
      break;
    case Ope::Sub:
      {
        r.ok_value = a - b;
      }
      break;
    case Ope::Mul:
      {
        r.ok_value = a * b;
      }
      break;
    case Ope::Div:
      {
        r.ok_value = a / b;
      }
      break;
  }
  return r;
}

Result<int, Error> rpn_runtime(std::stack<Inst>& r_stack) {
  std::stack<int> workspace;

  while (!r_stack.empty()) {
    Inst inst = r_stack.top();
    r_stack.pop();

    switch (inst.ty) {
      case Inst::Ope:
        {
          Result<int, Error> cal = exec_operation(inst, workspace);
          switch (cal.ty) {
            case Result<int, Error>::Err:
              return cal;
            case Result<int, Error>::Ok:
              {
                workspace.push(cal.ok_value);
              }
              break;
          }
        }
        break;
      case Inst::Number:
        {
          workspace.push(inst.value.number_value);
        }
        break;
    }
  }

  Error err;
  Result<int, Error> r;
  if (workspace.size() == 1) {
    r.ty = Result<int, Error>::Ok;
    r.ok_value = workspace.top();
  } else {
    r.ty = Result<int, Error>::Err;
    r.err_value = err;
  }
  return r;
}

