#ifndef __PRESIDENTIALPARDONFORM_HPP__
#define __PRESIDENTIALPARDONFORM_HPP__

#include "AForm.hpp"
#include <string>

// AForm を public 継承する
class PresidentialPardonForm : public AForm {
private:
  std::string target;

public:
  // Orthodox Canonical Form
  PresidentialPardonForm();
  PresidentialPardonForm(const std::string& target);
  PresidentialPardonForm(const PresidentialPardonForm& other);
  PresidentialPardonForm& operator=(const PresidentialPardonForm& other);
  ~PresidentialPardonForm();

  // 基底クラス(AForm)の純粋仮想関数をオーバーライドして、固有の処理を実装する
  void executeAction() const;
};

#endif
