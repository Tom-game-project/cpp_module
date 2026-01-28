#pragma once
#include <string>
#ifndef __HARL_H__
#define __HARL_H__


class Harl {
typedef void (*HarlMemFn)(void);
public:
	Harl();
	~Harl();
	void complain(std::string level);
private:
	static void debug(void);
	static void info(void);
	static void warning(void);
	static void error(void);
};

#endif

