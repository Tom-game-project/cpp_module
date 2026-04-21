#ifndef __SHRUBBERYCREATIONFORM_HPP__
#define __SHRUBBERYCREATIONFORM_HPP__

#include "AForm.hpp"
#include <string>

// AForm を public 継承する
class ShrubberyCreationForm : public AForm {
private:
  std::string target;

public:
  // Orthodox Canonical Form
  ShrubberyCreationForm();
  ShrubberyCreationForm(const std::string& target);
  ShrubberyCreationForm(const ShrubberyCreationForm& other);
  ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
  ~ShrubberyCreationForm();

  // 基底クラス(AForm)の純粋仮想関数をオーバーライドして、固有の処理を実装する
  void executeAction() const;
};

#endif
