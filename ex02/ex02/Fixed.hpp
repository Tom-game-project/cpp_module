#pragma once
#ifndef __FIXED_H__
#define __FIXED_H__
#include <iostream>

// If the platform does not support with the following specifications, you can't use the class `Fixed`.

                       // # spec you needed
typedef long long i64; // - `long long` must have a 64bit space.
typedef int       i32; // - `int` must have a 32bit space.
typedef float     f32; // - `float` must have a 32bit space.

class Fixed {
public:

	// Orthodox Canonical Form
    // constructors
	Fixed();
	Fixed(const int value);
	Fixed(const float value);
	Fixed(const Fixed &other);

    // destructor
	~Fixed();

    // operators
	Fixed &operator=(const Fixed &other); // assign 

    // compare
    bool operator>(const Fixed &other) const; // gt
    bool operator>=(const Fixed &other) const;// ge
    bool operator<(const Fixed &other) const; // lt
    bool operator<=(const Fixed &other) const;// le
    bool operator==(const Fixed &other) const;// eq
    bool operator!=(const Fixed &other) const;// ne

    // operator
    Fixed operator+(const Fixed &other) const; // add 
    Fixed operator-(const Fixed &other) const; // sub
    Fixed operator*(const Fixed &other) const; // mul
    Fixed operator/(const Fixed &other) const; // div
    
    // incr decr
    // prefix
    Fixed &operator++();
    Fixed &operator--();
    // postfix
    Fixed operator++(int);
    Fixed operator--(int);

    // min max
    static Fixed &min(Fixed &a, Fixed &b);
    static const Fixed &min(const Fixed &a, const Fixed &b);
    static Fixed &max(Fixed &a, Fixed &b);
    static const Fixed &max(const Fixed &a, const Fixed &b);

    // otherwise
	i32 getRawBits(void) const;
	void setRawBits(i32 const raw);
	i32 toInt(void) const;
    f32 toFloat(void) const;
private:
	int                 _fixedPointValue; // entity
	static const int    _fractionalBits = 8;
};

// for stream output 
// left expr is not a Fixed class. so this method is out of Fixed class
std::ostream &operator<<(std::ostream &o, Fixed const &i);
#endif

