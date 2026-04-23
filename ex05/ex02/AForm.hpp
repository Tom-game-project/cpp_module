#ifndef __AFORM_HPP__
#define __AFORM_HPP__

#include "Bureaucrat.hpp"
#include <string>

class Bureaucrat;
class AForm {
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

  class NotSignedException : public std::exception {
    public:
      virtual const char* what() const throw();
  };

  AForm();
  AForm(
    const std::string name,
    const int required_level_for_sign,
    const int required_level_for_exec
  );
  AForm(const AForm& other);
  AForm &operator=(const AForm& other);
  virtual ~AForm();

  std::string getName() const;
  bool getIsSigned() const;
  int getRequiredLevelForSign() const;
  int getRequiredLevelForExec() const;

  void beSigned(const Bureaucrat& bureaucrat);
  void execute(Bureaucrat const & executor) const;

  virtual void executeAction() const = 0;
};

// クラス定義の "外" に記述します
std::ostream& operator<<(std::ostream& os, const AForm& b);

#endif
