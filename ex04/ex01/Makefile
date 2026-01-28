# ex01
CXX=c++
CXX_FLAG= -Wall -Wextra -Werror -std=c++98 -pedantic-errors -g

SRC=\
	Animal.cpp \
	Cat.cpp \
	Dog.cpp \
	WrongAnimal.cpp \
	WrongCat.cpp \
	Brain.cpp \
    main.cpp \

OBJ=$(SRC:.cpp=.o)

NAME=exec

all: $(NAME)


%.o: %.cpp
	$(CXX) $(CXX_FLAG)  -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXX_FLAG) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


