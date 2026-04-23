#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <exception>
#include <iostream>

const char *Bureaucrat::GradeTooHighException::what() const throw() {
  return GradeTooHighExceptionMsg;
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
  return GradeTooLowExceptionMsg;
}

Bureaucrat::Bureaucrat(): grade(1), name("") {}

Bureaucrat::Bureaucrat(const std::string& name, const int grade): grade(grade), name(name) {
  if (this->grade < 1) {
    throw Bureaucrat::GradeTooHighException();
  }
  if (this->grade > 150) {
    throw Bureaucrat::GradeTooLowException();
  }
}

Bureaucrat::Bureaucrat(const Bureaucrat& other): grade(other.grade), name(other.name) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat& other) {
  if (this != &other) {
    this->grade = other.grade;
  }
  return *this;
}

Bureaucrat::~Bureaucrat () {}

std::string Bureaucrat::getName() const {
  return this->name;
}

int Bureaucrat::getGrade() const {
  return this->grade;
}

void Bureaucrat::increment() {
  if (this->grade - 1 < 1) {
    throw Bureaucrat::GradeTooHighException();
  } else {
    this->grade -= 1;
  }
}

void Bureaucrat::decrement() {
  if (150 < this->grade + 1) {
    throw Bureaucrat::GradeTooLowException();
  } else {
    this->grade += 1;
  }
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
    return os;
}

void Bureaucrat::signForm(AForm& form) {
  try {
    form.beSigned(*this);
    std::cout << this->getName() << " signed " << form.getName() << std::endl;
  } catch (std::exception &e) {
    std::cout << this->getName() << " couldn't sign " << form.getName() 
              << " because " << e.what() << std::endl;
  }
}

void Bureaucrat::executeForm(AForm const & form) const {
  try {
    form.execute(*this);
    
    std::cout << this->getName() << " executed " << form.getName() << std::endl;
  } 
  catch (std::exception& e) {
    std::cout << this->getName() << " couldn't execute " << form.getName() 
              << " because " << e.what() << std::endl;
  }
}

