#ifndef __ROBOTOMYREQUESTFORM_HPP__
#define __ROBOTOMYREQUESTFORM_HPP__

#include "AForm.hpp"
#include <string>

// AForm を public 継承する
class RobotomyRequestForm : public AForm {
private:
  std::string target;

public:
  // Orthodox Canonical Form
  RobotomyRequestForm();
  RobotomyRequestForm(const std::string& target);
  RobotomyRequestForm(const RobotomyRequestForm& other);
  RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
  ~RobotomyRequestForm();

  // 基底クラス(AForm)の純粋仮想関数をオーバーライドして、固有の処理を実装する
  void executeAction() const;
};

#endif

