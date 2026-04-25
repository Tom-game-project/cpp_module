#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main () {
  std::srand(static_cast<unsigned int>(std::time(NULL)));

  for (int i = 0; i < 5; ++i) {
    std::cout << "[Test " << i + 1 << "]" << std::endl;
    
    // ランダムなインスタンスを生成
    Base* random_obj = generate();

    // ポインタのidentifyテスト
    std::cout << "  identify(Base* p) : ";
    identify(random_obj);

    // 参照のidentifyテスト（*をつけて実体を渡す）
    std::cout << "  identify(Base& p) : ";
    identify(*random_obj);

    // 必ずdeleteしてメモリリークを防ぐ
    delete random_obj;
    
    std::cout << "----------------------------------------\n";
  }
  Base* a = new A();
  Base* b = new B();
  Base* c = new C();

  std::cout << "Expected: A -> Actual (Ptr): ";
  identify(a);
  std::cout << "Expected: B -> Actual (Ref): ";
  identify(*b);
  std::cout << "Expected: C -> Actual (Ptr): ";
  identify(c);

  // NULLポインタを渡したときのエッジケーステスト（クラッシュしないことの証明）
  std::cout << "Expected: Unknown -> Actual (Ptr): ";
  identify(NULL);

  delete a;
  delete b;
  delete c;

  return 0;
}
