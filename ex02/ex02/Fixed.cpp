#include "Fixed.hpp"
#include <cmath>
#include <iostream>
#include <ostream>

// === Orthodox Canonical Form ===

Fixed::Fixed ():_fixedPointValue(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) : _fixedPointValue(value << _fractionalBits){
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value): _fixedPointValue(roundf(value * (1 << _fractionalBits))){
	std::cout << "Float constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) {
	std::cout << "Copy constructor called" << std::endl;
	*this = other; // call copy assignment operator
}

// destructor
Fixed::~Fixed () {
	std::cout << "Destructor called" << std::endl;
}

// ^^^ Orthodox Canonical Form ^^^


Fixed &Fixed::operator=(const Fixed &other) {
	std::cout << "Copy assignment operator called" << std::endl;

	// 1. 自己代入チェック (Self-assignment check)
	// アドレスが同じなら、コピー処理をスキップしてそのまま返す
	if (this == &other) {
		// do nothing
	} else {
		// 2. 値のコピー
		// Exercise 00の出力例に従い、getRawBits()経由で値を取得する
		this->_fixedPointValue = other.getRawBits();
	}

	// 3. 自分自身への参照を返す
	return *this;
}

// === operators ===

// compare

// gt
bool Fixed::operator>(const Fixed &other) const{
    return this->getRawBits() > other.getRawBits();
}

// ge
bool Fixed::operator>=(const Fixed &other) const{
    return this->getRawBits() >= other.getRawBits();
}

// lt
bool Fixed::operator<(const Fixed &other) const{
    return this->getRawBits() < other.getRawBits();
}

// le
bool Fixed::operator<=(const Fixed &other) const{
    return this->getRawBits() <= other.getRawBits();
}

// eq
bool Fixed::operator==(const Fixed &other) const{
    return this->getRawBits() == other.getRawBits();
}

// ne
bool Fixed::operator!=(const Fixed &other) const{
    return this->getRawBits() != other.getRawBits();
}

// operator

// add 
Fixed Fixed::operator+(const Fixed &other) const {
    Fixed result;
    result.setRawBits(this->getRawBits() + other.getRawBits());
    return result;
}

// sub
Fixed Fixed::operator-(const Fixed &other) const {
    Fixed result;
    result.setRawBits(this->getRawBits() - other.getRawBits());
    return result;
}

// mul
Fixed Fixed::operator*(const Fixed &other) const {
    Fixed result;
    // 1. casting to `long long` and preventing overflow
    i64 temp = (i64)this->getRawBits() * (i64)other.getRawBits();
    
    // 2. undo the result
    result.setRawBits((i32)(temp >> _fractionalBits));
    return result;
}

// div
Fixed Fixed::operator/(const Fixed &other) const {
    Fixed result;
    i64 temp = (i64)this->getRawBits() << _fractionalBits;

    if (other.getRawBits()!= 0) {
        result.setRawBits((i32)(temp / other.getRawBits()));
    } else {
        std::cerr << "Error: Division by zero" << std::endl;
    }
    return result;
}
// ^^^ operators ^^^

// === incr decr ===
// - prefix
Fixed &Fixed::operator++() {
    this->_fixedPointValue++;
    return *this;
}
Fixed &Fixed::operator--() {
    this->_fixedPointValue--;
    return *this;
}

// - postfix
Fixed Fixed::operator++(int) {
    Fixed temp = *this;
    this->_fixedPointValue++;
    return temp;
}
Fixed Fixed::operator--(int) {
    Fixed temp = *this;
    this->_fixedPointValue--;
    return temp;
}
// ^^^ incr decr ^^^

// === min max ===

Fixed &Fixed::min(Fixed &a, Fixed &b) {
    if (a < b)
        return a;
    else
        return b;
}
const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    if (a < b)
        return a;
    else
        return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    if (a > b)
        return a;
    else
        return b;
}
const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    if (a > b)
        return a;
    else
        return b;
}
// ^^^ min max ^^^


// === normal methods ===
i32 Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return this->_fixedPointValue;
}

void Fixed::setRawBits(i32 const raw) {
	this->_fixedPointValue = raw;
}

i32 Fixed::toInt(void) const {
    return this->_fixedPointValue>>8;
}

f32 Fixed::toFloat(void) const {
    return (f32)this->_fixedPointValue / 256.0f;
}

// ^^^ normal methods ^^^
// stream out put
std::ostream &operator<<(std::ostream &o, Fixed const &i) {
    o<<i.toFloat();
    return o;
}
