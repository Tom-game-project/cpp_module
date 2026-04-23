//#include "Bureaucrat.hpp"
//#include "AForm.hpp"
//#include <cassert>
//#include <cstring>
//#include <exception>
//#include <iostream>
//#include <ctime>
// 
//int main () {
//  std::srand(static_cast<unsigned int>(std::time(NULL)));
//
//  Bureaucrat b0("Hello", 150);
//
//  try {
//    b0.decrement();
//  } catch (std::exception& e) {
//    // std::cout << e.what() << std::endl;
//    assert(std::strcmp(GradeTooLowExceptionMsg, e.what()) == 0);
//  }
//
//  Bureaucrat b1("World", 1);
//  
//  try {
//    b1.increment();
//  } catch (std::exception& e) {
//    // std::cout << e.what() << std::endl;
//    assert(std::strcmp(GradeTooHighExceptionMsg, e.what()) == 0);
//  }
//
//  Bureaucrat* b2 = new Bureaucrat("A", 150);
//
//  b2->increment();
//  assert(b2->getGrade() == 149);
//
//  Bureaucrat* b3 = new Bureaucrat("B", 1);
//
//  b3->decrement();
//  assert(b3->getGrade() == 2);
//
//  std::cout << b0 << std::endl;
//  std::cout << b1 << std::endl;
//  std::cout << *b2 << std::endl;
//  std::cout << *b3 << std::endl;
//
//  // AForm f0("form0", 100, 100);
//  // 
//  // Form f1("form1", 100, 100);
//  // Form f2("form2", 100, 100);
//  // 
//  // // failed to sign !
//  // b0.signForm(f0);
//  // 
//  // b1.signForm(f1);
//
//}


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    // RobotomyRequestForm のための乱数シード設定（プログラム全体で1回だけ呼ぶ）
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::cout << "=========================================" << std::endl;
    std::cout << "           BUREAUCRATS SETUP             " << std::endl;
    std::cout << "=========================================" << std::endl;
    
    Bureaucrat boss("Boss", 1);       // 最高権力者：すべて可能
    Bureaucrat mid("Mid", 40);        // 中間管理職：ロボトミー実行(45)までは可能
    Bureaucrat noob("Noob", 150);     // 新入社員：何もできない

    std::cout << boss << std::endl;
    std::cout << mid << std::endl;
    std::cout << noob << std::endl;

    std::cout << "\n=========================================" << std::endl;
    std::cout << "    TEST 1: Shrubbery Creation Form      " << std::endl;
    std::cout << "=========================================" << std::endl;
    try {
        ShrubberyCreationForm shrub("garden"); // Sign: 145, Exec: 137
        std::cout << shrub << std::endl;

        // Noob(150) は署名できない
        noob.signForm(shrub);
        
        // Mid(40) が署名する
        mid.signForm(shrub);
        
        // Noob(150) は実行できない
        noob.executeForm(shrub);
        
        // Mid(40) が実行する -> garden_shrubbery ファイルが作成されるはず
        mid.executeForm(shrub);
    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    std::cout << "\n=========================================" << std::endl;
    std::cout << "    TEST 2: Robotomy Request Form        " << std::endl;
    std::cout << "=========================================" << std::endl;
    try {
        RobotomyRequestForm robot("Bender"); // Sign: 72, Exec: 45
        std::cout << robot << std::endl;

        // 未署名のまま実行しようとする -> 失敗するはず
        boss.executeForm(robot);

        // 署名する
        mid.signForm(robot);

        // 50%の確率を確かめるため、Bossに複数回実行させる
        std::cout << "--- Executing multiple times to test randomness ---" << std::endl;
        boss.executeForm(robot);
        boss.executeForm(robot);
        boss.executeForm(robot);
        boss.executeForm(robot);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\n=========================================" << std::endl;
    std::cout << "    TEST 3: Presidential Pardon Form     " << std::endl;
    std::cout << "=========================================" << std::endl;
    try {
        PresidentialPardonForm pardon("Alice"); // Sign: 25, Exec: 5
        std::cout << pardon << std::endl;

        // Mid(40) は署名できない (25が必要)
        mid.signForm(pardon);

        // Boss(1) が署名する
        boss.signForm(pardon);

        // Mid(40) は実行できない (5が必要)
        mid.executeForm(pardon);

        // Boss(1) が実行する -> 恩赦成功
        boss.executeForm(pardon);
    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    std::cout << "\n=========================================" << std::endl;
    std::cout << "                 END                     " << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}
