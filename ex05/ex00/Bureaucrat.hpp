#pragma once

#ifndef __BUREAUCRAT_HPP__
# define __BUREAUCRAT_HPP__

#include <exception>
#include <string>

#define GradeTooHighExceptionMsg "Error: Bureaucrat grade is too high (must be >= 1)."

#define GradeTooLowExceptionMsg "Error: Bureaucrat grade is too low (must be <= 150)."

class Bureaucrat {
private:
  int grade;
  const std::string name;
public:
  class GradeTooHighException: public std::exception {
    public:
      virtual const char* what() const throw();
  };

  class GradeTooLowException: public std::exception {
    public:
      virtual const char* what() const throw();
  };

  Bureaucrat();
  Bureaucrat(const std::string& name, const int grade);
  Bureaucrat(const Bureaucrat& other);
  Bureaucrat &operator=(const Bureaucrat& other);
  ~Bureaucrat();

  std::string getName() const;
  int getGrade() const;

  // throw error
  void increment(); 
  // throw error
  void decrement();
};

// クラス定義の "外" に記述します
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif
