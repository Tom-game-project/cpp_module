#include "Bureaucrat.hpp"
#include <iostream>

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
