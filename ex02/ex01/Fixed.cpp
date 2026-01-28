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

// === normal methods ===
i32 Fixed::getRawBits(void) const {
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
