#include "Span.hpp"
#include <algorithm>

// --- Orthodox Canonical Form ---

Span::Span() : _maxSize(0) {}
Span::Span(unsigned int n) : _maxSize(n) {}
Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {}
Span& Span::operator=(const Span& other) {
  if (this != &other) { // 自己代入チェック
    _maxSize = other._maxSize;
    _numbers = other._numbers;
  }
  return *this;
}
Span::~Span() {}


void Span::addNumber(int number) {
  if (_numbers.size() >= _maxSize) {
    throw SpanFullException();
  }
  _numbers.push_back(number);
}

unsigned int Span::longestSpan() const {
  if (_numbers.size() < 2) {
    throw SpanTooSmallException();
  }

  std::vector<int>::const_iterator min_it = std::min_element(_numbers.begin(), _numbers.end());
  std::vector<int>::const_iterator max_it = std::max_element(_numbers.begin(), _numbers.end());

  return static_cast<unsigned int>(*max_it) - static_cast<unsigned int>(*min_it);
}

unsigned int Span::shortestSpan() const {
  if (_numbers.size() < 2) {
    throw SpanTooSmallException();
  }

  std::vector<int> sorted_numbers = _numbers;
  std::sort(sorted_numbers.begin(), sorted_numbers.end());

  unsigned int min_span = static_cast<unsigned int>(-1); 

  for (std::vector<int>::size_type i = 1; i < sorted_numbers.size(); ++i) {
    unsigned int diff = static_cast<unsigned int>(sorted_numbers[i]) - static_cast<unsigned int>(sorted_numbers[i - 1]);
    if (diff < min_span) {
      min_span = diff;
    }
  }
  return min_span;
}

const char* Span::SpanFullException::what() const throw() {
  return "Error: Span is already full.";
}

const char* Span::SpanTooSmallException::what() const throw() {
  return "Error: Span requires at least 2 elements to calculate the distance.";
}
