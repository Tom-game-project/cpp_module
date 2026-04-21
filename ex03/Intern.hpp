#ifndef __INTERN_HPP__
#define __INTERN_HPP__

#include "AForm.hpp"

class Intern {
private:
  // 各Formを生成するためのプライベートなヘルパー関数
  AForm* makeShrubbery(const std::string& target) const;
  AForm* makeRobotomy(const std::string& target) const;
  AForm* makePresidential(const std::string& target) const;
public:
  // Orthodox Canonical Form
  Intern();
  Intern(const Intern& other);
  Intern& operator=(const Intern& other);
  ~Intern();

  AForm* makeForm(std::string formName, std::string target);
};

#endif
