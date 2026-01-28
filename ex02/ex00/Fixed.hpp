#pragma once
#ifndef __FIXED_H__
#define __FIXED_H__

class Fixed {
public:
	// Orthodox Canonical Form
	Fixed();
	Fixed(const Fixed &other);
	Fixed &operator=(const Fixed &other);
	~Fixed();
	int getRawBits(void) const;
	void setRawBits(int const raw);
private:
	int                 _fixedPointValue;
	static const int    _fractionalBits = 8;
};

#endif

