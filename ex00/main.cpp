#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp" // 先ほど作成したヘッダファイル

// テスト用のヘルパー関数（ベクトル用）
void test_vector() {
    std::cout << "--- Testing std::vector ---" << std::endl;
    
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    // 正常系テスト（存在する値を探す）
    std::cout << "[Search 30] : ";
    Result<std::vector<int>::iterator, FailedReason::FailedReason> res1 = easyfind(vec, 30);
    if (res1.ty == Result<std::vector<int>::iterator, FailedReason::FailedReason>::Ok) {
        std::cout << "Found! Value is " << *(res1.ok_value) << std::endl;
    } else {
        std::cout << "Not Found." << std::endl;
    }

    // 異常系テスト（存在しない値を探す）
    std::cout << "[Search 99] : ";
    Result<std::vector<int>::iterator, FailedReason::FailedReason> res2 = easyfind(vec, 99);
    if (res2.ty == Result<std::vector<int>::iterator, FailedReason::FailedReason>::Err) {
        std::cout << "Error Caught! (FailedReason Code: " << res2.err_value << ")" << std::endl;
    } else {
        std::cout << "Found unexpectedly." << std::endl;
    }
}

// テスト用のヘルパー関数（リスト用）
void test_list() {
    std::cout << "\n--- Testing std::list ---" << std::endl;
    
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    // 正常系テスト
    std::cout << "[Search 2] : ";
    Result<std::list<int>::iterator, FailedReason::FailedReason> res1 = easyfind(lst, 2);
    if (res1.ty == Result<std::list<int>::iterator, FailedReason::FailedReason>::Ok) {
        std::cout << "Found! Value is " << *(res1.ok_value) << std::endl;
    } else {
        std::cout << "Not Found." << std::endl;
    }
}

int main() {
    test_vector();
    test_list();
    
    return 0;
}
