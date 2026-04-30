#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <iterator>

class Span {
private:
  unsigned int _maxSize;
  std::vector<int> _numbers;

public:
  // Orthodox Canonical Form
  Span();
  Span(unsigned int n);
  Span(const Span& other);
  Span& operator=(const Span& other);
  ~Span();

  void addNumber(int number);

  unsigned int shortestSpan() const;
  unsigned int longestSpan() const;

  template <typename Iterator>
  void addNumber(Iterator begin, Iterator end) {
    long int distance = std::distance(begin, end);
    
    if (_numbers.size() + distance > _maxSize) {
      throw SpanFullException();
    }
    
    _numbers.insert(_numbers.end(), begin, end);
  }

  class SpanFullException : public std::exception {
  public:
    virtual const char* what() const throw();
  };

  class SpanTooSmallException : public std::exception {
  public:
    virtual const char* what() const throw();
  };
};

#endif
