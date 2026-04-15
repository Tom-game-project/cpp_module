
CXX=c++
CXX_FLAG= -Wall -Wextra -Werror -std=c++98 -pedantic-errors

all:
	$(CXX) $(CXX_FLAG) main.cpp
