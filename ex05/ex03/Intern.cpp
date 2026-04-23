#include "Intern.hpp"
#include <string>
#include <iostream>

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// Orthodox Canonical Form
Intern::Intern() {}
Intern::Intern(const Intern& other) { (void)other; }
Intern& Intern::operator=(const Intern& other) { 
  (void)other; 
  return *this; 
}
Intern::~Intern() {}

AForm* Intern::makeShrubbery(const std::string& target) const {
  return new ShrubberyCreationForm(target);
}

AForm* Intern::makeRobotomy(const std::string& target) const {
  return new RobotomyRequestForm(target);
}

AForm* Intern::makePresidential(const std::string& target) const {
  return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(std::string formName, std::string target) {
  std::string formNames[] = {
    "shrubbery creation",
    "robotomy request",
    "presidential pardon"
  };

  AForm* (Intern::*funcs[])(const std::string&) const = {
    &Intern::makeShrubbery,
    &Intern::makeRobotomy,
    &Intern::makePresidential
  };

  // 3. ループで検索し、一致したらそのインデックスの関数を実行する
  for (int i = 0; i < 3; i++) {
    if (formName == formNames[i]) {
      std::cout << "Intern creates " << formName << std::endl;
      // this->* を使ってメンバ関数ポインタを呼び出す
      return (this->*funcs[i])(target);
    }
  }

  // 見つからなかった場合の処理
  std::cerr << "Error: Intern cannot create '" << formName << "' because it does not exist." << std::endl;
  return NULL;
}
