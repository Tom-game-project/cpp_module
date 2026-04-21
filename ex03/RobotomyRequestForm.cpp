#include "RobotomyRequestForm.hpp"
#include <iostream>
#include <cstdlib>

// -----------------------------------------------------------------------------
// コンストラクタと正統基本形式 (Orthodox Canonical Form)
// -----------------------------------------------------------------------------

// デフォルトコンストラクタ
RobotomyRequestForm::RobotomyRequestForm() : 
  AForm("Robotomy Request Form", 72, 45), target("default_target") {}

// 課題で要求されている「ターゲットを受け取る」コンストラクタ
RobotomyRequestForm::RobotomyRequestForm(const std::string& target) : 
  AForm("Robotomy Request Form", 72, 45),
  target(target) {}

// コピーコンストラクタ
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) : 
  AForm(other),
  target(other.target) {}

// コピー代入演算子
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
  if (this != &other) {
    AForm::operator=(other); 
    this->target = other.target;
  }
  return *this;
}

// デストラクタ
RobotomyRequestForm::~RobotomyRequestForm() {}

// -----------------------------------------------------------------------------
// アクションの実行
// -----------------------------------------------------------------------------

void RobotomyRequestForm::executeAction() const {
  std::cout << "* Vrrrrr... Bzzzzzt... (drilling noises) *" << std::endl;
  if (std::rand() % 2 == 0) {
    std::cout << this->target << " has been robotomized successfully." << std::endl;
  } else {
    std::cout << "The robotomy of " << this->target << " failed." << std::endl;
  }
}
