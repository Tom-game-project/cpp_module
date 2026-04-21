#include "PresidentialPardonForm.hpp"
#include <iostream>

// -----------------------------------------------------------------------------
// コンストラクタと正統基本形式 (Orthodox Canonical Form)
// -----------------------------------------------------------------------------

// デフォルトコンストラクタ
PresidentialPardonForm::PresidentialPardonForm() : 
  AForm("Presidential Pardon Form", 25, 5), target("default_target") {}

// 課題で要求されている「ターゲットを受け取る」コンストラクタ
PresidentialPardonForm::PresidentialPardonForm(const std::string& target) : 
  AForm("Presidential Pardon Form", 25, 5),
  target(target) {}

// コピーコンストラクタ
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) : 
  AForm(other),
  target(other.target) {}

// コピー代入演算子
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other) {
  if (this != &other) {
    AForm::operator=(other); 
    this->target = other.target;
  }
  return *this;
}

// デストラクタ
PresidentialPardonForm::~PresidentialPardonForm() {}

// -----------------------------------------------------------------------------
// アクションの実行
// -----------------------------------------------------------------------------

void PresidentialPardonForm::executeAction() const {
  std::cout << this->target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
