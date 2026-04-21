#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"

int main() {
    // 乱数のシード設定（RobotomyRequestForm用）
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::cout << "=========================================" << std::endl;
    std::cout << "           INTERN & BUREAUCRAT           " << std::endl;
    std::cout << "=========================================" << std::endl;

    Intern someRandomIntern;
    Bureaucrat boss("Boss", 1); // 署名・実行のための最高権力者
    AForm* form;

    std::cout << "\n--- Test 1: Robotomy Request Form ---" << std::endl;
    form = someRandomIntern.makeForm("robotomy request", "Bender");
    if (form) {
        boss.signForm(*form);
        boss.executeForm(*form);
        delete form;
    }

    std::cout << "\n--- Test 2: Shrubbery Creation Form ---" << std::endl;
    form = someRandomIntern.makeForm("shrubbery creation", "Garden");
    if (form) {
        boss.signForm(*form);
        boss.executeForm(*form);
        delete form;
    }

    std::cout << "\n--- Test 3: Presidential Pardon Form ---" << std::endl;
    form = someRandomIntern.makeForm("presidential pardon", "Alice");
    if (form) {
        boss.signForm(*form);
        boss.executeForm(*form);
        delete form;
    }

    std::cout << "\n--- Test 4: 存在しない書類名（エラーハンドリング） ---" << std::endl;
    form = someRandomIntern.makeForm("unknown form", "Target");
    if (form) {
        // ここは実行されない
        boss.signForm(*form);
        boss.executeForm(*form);
        delete form;
    }

    std::cout << "\n=========================================" << std::endl;
    std::cout << "                 END                     " << std::endl;
    std::cout << "=========================================" << std::endl;

    return 0;
}
