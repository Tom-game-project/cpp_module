.PHONY: all clean fclean re

SRC= \
	 PmergeMe.cpp \
     main.cpp

OBJ=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)

NAME=PmergeMe

CXX=c++
DEP_FLAG= -MMD -MP
CXX_FLAGS= -Wall -Wextra -Werror -Wconversion -std=c++98 -pedantic-errors \
           -Wreorder -Wshadow -Wold-style-cast \
           -Woverloaded-virtual -Wnon-virtual-dtor $(DEP_FLAG)

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)
