#include <iostream>
#include <string>

int main() {
    // 1. 変数の初期化
    // "HI THIS IS BRAIN" で初期化された文字列変数
    std::string str = "HI THIS IS BRAIN";
    // stringPTR: 文字列へのポインタ
    std::string* stringPTR = &str;
    // stringREF: 文字列への参照
    std::string& stringREF = str;
    // 2. メモリアドレスの表示
    std::cout << "--- Memory Addresses ---" << std::endl;
    // 文字列変数のアドレス
    std::cout << "Address of the string variable: " << &str << std::endl;
    // stringPTR が保持しているアドレス (ポインタ自体のアドレスではない点に注意)
    std::cout << "Address held by stringPTR:      " << stringPTR << std::endl;
    // stringREF が保持しているアドレス (実体のアドレスと同じになる)
    std::cout << "Address held by stringREF:      " << &stringREF << std::endl;
    std::cout << std::endl;
    // 3. 値の表示
    std::cout << "--- String Values ---" << std::endl;
    // 文字列変数の値
    std::cout << "Value of the string variable:  " << str << std::endl;
    // stringPTR が指している値 (デリファレンス * が必要)
    std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
    // stringREF が指している値 (そのまま変数として扱える)
    std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;
    return 0;
}
