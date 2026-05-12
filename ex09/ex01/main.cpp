#include "RPN.hpp"
#include <iostream>

int main (int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Please pass one argument." << std::endl;
    return 0;
  } else {
    std::string code = argv[1];
    Result<std::stack<Inst>, Error> r_stack = interpret_string_as_rpn(code);

    switch (r_stack.ty) {
      case Result<std::stack<Inst>, Error>::Err:
        {
          std::cerr << "Error" << std::endl;
          return 1;
        }
      case Result<std::stack<Inst>, Error>::Ok:
        {
          Result<int, Error> r_int;
          r_int = rpn_runtime(r_stack.ok_value);

          switch (r_int.ty) {
            case Result<int, Error>::Err:
              {
                std::cerr << "Error" << std::endl;
                return 1;
              }
            case Result<int, Error>::Ok:
              {
                std::cout << r_int.ok_value << std::endl;
              }
              break;
          }
        }
        break;
    }
    return 0;
  }
}
