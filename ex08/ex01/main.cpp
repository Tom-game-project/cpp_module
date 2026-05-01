#include "Span.hpp"

#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Span.hpp"

void test_large_scale_accuracy() {
  std::cout << "--- Large Scale Accuracy Test (10,000 elements) ---" << std::endl;
  
  unsigned int amount = 10000;
  Span sp(amount);
  std::vector<int> predictable_data;
  
  // 10, 20, 30 ... 100000 という等差数列を生成
  // 正解は必ず Shortest: 10, Longest: 99990
  for (std::size_t i = 1; i <= amount; ++i) {
    predictable_data.push_back(static_cast<int>(i * 10));
  }
  
  // データをシャッフルし、挿入順序を完全にランダムにする
  std::random_shuffle(predictable_data.begin(), predictable_data.end());
  
  sp.addNumber(predictable_data.begin(), predictable_data.end());
  
  unsigned int shortest = sp.shortestSpan();
  unsigned int longest = sp.longestSpan();
  
  std::cout << "Expected Shortest : 10    | Actual : " << shortest << std::endl;
  std::cout << "Expected Longest  : 99990 | Actual : " << longest << std::endl;
  
  if (shortest == 10 && longest == 99990) {
    std::cout << "=> [SUCCESS] Logic is perfectly accurate even with 10,000 shuffled elements." << std::endl;
  } else {
    std::cout << "=> [FAILED] Calculation mismatch." << std::endl;
  }
  std::cout << std::endl;
}

void test_bulk_insert_exception() {
  std::cout << "--- Bulk Insert Exception Test ---" << std::endl;

  Span sp(5);

  std::vector<int> massive_data(10000, 42);

  std::cout << "Attempting to insert 10,000 elements into a Span of size 5..." << std::endl;

  try {
    sp.addNumber(massive_data.begin(), massive_data.end());

    std::cerr << "=> [FAILED] Exception was NOT thrown! Span overflowed silently." << std::endl;
  } catch (const std::exception& e) {
    std::cout << "=> [SUCCESS] Exception correctly caught: " << e.what() << std::endl;
  }
  std::cout << std::endl;
}

void test_subject_example() {
  std::cout << "--- Subject PDF Example Test ---" << std::endl;
  Span sp = Span(5);
  
  sp.addNumber(6);
  sp.addNumber(3);
  sp.addNumber(17);
  sp.addNumber(9);
  sp.addNumber(11);
  
  std::cout << "Shortest Span: " << sp.shortestSpan() << " (Expected: 2)" << std::endl;
  std::cout << "Longest Span:  " << sp.longestSpan() << " (Expected: 14)" << std::endl;
  std::cout << std::endl;
}

int main() {
  test_subject_example();
  test_large_scale_accuracy();
  test_bulk_insert_exception();
  
  return 0;
}
