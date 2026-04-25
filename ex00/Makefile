.PHONY: all clean fclean re

SRC= \

OBJ=$(SRC:.cpp=.o)

MAIN=main.cpp

NAME=exec

CXX=c++
CXX_FLAGS= -Wall -Wextra -Werror -Wconversion -std=c++98 -pedantic-errors



all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MAIN)
	$(CXX) $(CXX_FLAGS) $(OBJ) $(MAIN) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

