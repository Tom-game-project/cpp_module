#include "Form.hpp"
#include <ostream>

#define FormGradeTooHighExceptionMsg "Form: Grade is too high."
#define FormGradeTooLowExceptionMsg "Form: Grade is too low."

const char* Form::GradeTooHighException::what() const throw() {
  return FormGradeTooHighExceptionMsg;
}

const char* Form::GradeTooLowException::what() const throw() {
  return FormGradeTooLowExceptionMsg;
}

Form::Form(): 
  name(""), 
  is_signed(false), 
  required_level_for_sign(1),
  required_level_for_exec(1)
{}

Form::Form(
  const std::string name,
  const int required_level_for_sign,
  const int required_level_for_exec
): 
  name(name),
  is_signed(false),
  required_level_for_sign(required_level_for_sign),
  required_level_for_exec(required_level_for_exec) {
  if (required_level_for_sign < 1 || required_level_for_exec < 1)
    throw GradeTooHighException();
  if (150 < required_level_for_sign || 150 < required_level_for_exec)
    throw GradeTooLowException();
}

Form::Form (const Form& other):
  name(other.name),
  is_signed(other.is_signed),
  required_level_for_sign(other.required_level_for_sign),
  required_level_for_exec(other.required_level_for_exec) {}

Form &Form::operator=(const Form& other) {
  if (this != &other) {
    this->is_signed = other.is_signed;
  }
  return *this;
}

Form::~Form() {

}

// getters

std::string Form::getName() const {
  return this->name;
}

bool Form::getIsSigned() const {
  return this->is_signed;
}

int Form::getRequiredLevelForSign() const {
  return this->required_level_for_sign;
}

int Form::getRequiredLevelForExec() const {
  return this->required_level_for_exec;
}

// sign
void Form::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() <= this->required_level_for_sign) {
    this->is_signed = true;
  } else {
    // ここはエラーを投げるので本当に正しい？とても同じ種類のエラーには見えないけど
    // **要件**が間違っています
    throw GradeTooLowException();
  }
}

std::ostream& operator<<(std::ostream& os, const Form& f) {
  os << "Form: " << f.getName() 
     << ", signed: " << (f.getIsSigned() ? "yes" : "no")
     << ", sign grade: " << f.getRequiredLevelForSign()
     << ", exec grade: " << f.getRequiredLevelForExec();
  return os;
}

