#ifndef __FORM_HPP__
#define __FORM_HPP__

#include <string>

#include "Bureaucrat.hpp"

class Form {
private:
  const std::string name;
  bool is_signed;
  const int required_level_for_sign;
  const int required_level_for_exec;
public:

  class GradeTooHighException : public std::exception {
    public:
      virtual const char* what() const throw() ;
    };
  class GradeTooLowException : public std::exception {
    public:
      virtual const char* what() const throw();
  }; 

  Form();
  Form(
    const std::string name,
    const int required_level_for_sign,
    const int required_level_for_exec
  );
  Form(const Form& other);
  Form &operator=(const Form& other);
  ~Form();

  std::string getName() const;
  bool getIsSigned() const;
  int getRequiredLevelForSign() const;
  int getRequiredLevelForExec() const;

  void beSigned(const Bureaucrat& bureaucrat);
};

// クラス定義の "外" に記述します
std::ostream& operator<<(std::ostream& os, const Form& b);

#endif
