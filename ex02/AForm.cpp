#include "AForm.hpp"
#include <ostream>

#define FormGradeTooHighExceptionMsg "Form: Grade is too high."
#define FormGradeTooLowExceptionMsg "Form: Grade is too low."
#define NotSignedExceptionMsg "Form: not signed"

const char* AForm::GradeTooHighException::what() const throw() {
  return FormGradeTooHighExceptionMsg;
}

const char* AForm::GradeTooLowException::what() const throw() {
  return FormGradeTooLowExceptionMsg;
}

const char* AForm::NotSignedException::what() const throw() {
  return NotSignedExceptionMsg;
}

AForm::AForm(): 
  name(""), 
  is_signed(false), 
  required_level_for_sign(1),
  required_level_for_exec(1)
{}

AForm::AForm(
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

AForm::AForm (const AForm& other):
  name(other.name),
  is_signed(other.is_signed),
  required_level_for_sign(other.required_level_for_sign),
  required_level_for_exec(other.required_level_for_exec) {}

AForm &AForm::operator=(const AForm& other) {
  if (this != &other) {
    this->is_signed = other.is_signed;
  }
  return *this;
}

AForm::~AForm() {

}

// getters

std::string AForm::getName() const {
  return this->name;
}

bool AForm::getIsSigned() const {
  return this->is_signed;
}

int AForm::getRequiredLevelForSign() const {
  return this->required_level_for_sign;
}

int AForm::getRequiredLevelForExec() const {
  return this->required_level_for_exec;
}

// sign
void AForm::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() <= this->required_level_for_sign) {
    this->is_signed = true;
  } else {
    // ここはエラーを投げるので本当に正しい？とても同じ種類のエラーには見えないけど
    // **要件**が間違っています
    throw GradeTooLowException();
  }
}

std::ostream& operator<<(std::ostream& os, const AForm& f) {
  os << "Form: " << f.getName() 
     << ", signed: " << (f.getIsSigned() ? "yes" : "no")
     << ", sign grade: " << f.getRequiredLevelForSign()
     << ", exec grade: " << f.getRequiredLevelForExec();
  return os;
}

void AForm::execute(Bureaucrat const & executor) const {
  if (!this->is_signed) {
    throw AForm::NotSignedException(); // 未署名
  }
  if (executor.getGrade() > this->required_level_for_exec) {
    throw AForm::GradeTooLowException(); // 権限不足
  }
  
  this->executeAction(); 
}
