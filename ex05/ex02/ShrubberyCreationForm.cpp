#include "ShrubberyCreationForm.hpp"
#include <fstream>
#include <iostream>

// -----------------------------------------------------------------------------
// コンストラクタと正統基本形式 (Orthodox Canonical Form)
// -----------------------------------------------------------------------------

// デフォルトコンストラクタ
ShrubberyCreationForm::ShrubberyCreationForm() : 
  AForm("Shrubbery Creation Form", 145, 137), target("default_target") {}

// 課題で要求されている「ターゲットを受け取る」コンストラクタ
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) : 
  AForm("Shrubbery Creation Form", 145, 137),
  target(target) {}

// コピーコンストラクタ
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : 
  AForm(other),
  target(other.target) {}

// コピー代入演算子
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
  if (this != &other) {
    AForm::operator=(other); 
    this->target = other.target;
  }
  return *this;
}

// デストラクタ
ShrubberyCreationForm::~ShrubberyCreationForm() {}

// -----------------------------------------------------------------------------
// アクションの実行
// -----------------------------------------------------------------------------

void ShrubberyCreationForm::executeAction() const {
  std::ofstream ofs((this->target + "_shrubbery").c_str());

  if (!ofs.is_open()) {
    std::cerr << "Error: Could not open file for ShrubberyCreationForm." << std::endl;
    return;
  }

  // アスキーアートの木を書き込む
  ofs << "       _-_" << std::endl;
  ofs << "    /~~   ~~\\" << std::endl;
  ofs << " /~~         ~~\\" << std::endl;
  ofs << "{               }" << std::endl;
  ofs << " \\  _-     -_  /" << std::endl;
  ofs << "   ~  \\\\ //  ~" << std::endl;
  ofs << "_- -   | | _- _" << std::endl;
  ofs << "  _ -  | |   -_" << std::endl;
  ofs << "      // \\\\" << std::endl;

  ofs.close();
}
