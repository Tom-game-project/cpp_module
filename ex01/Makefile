# ex01
CPP=c++
CPP_FLAG= -Wall -Wextra -Werror -std=c++98

SRC=\
	Contact.cpp\
	PhoneBook.cpp

OBJ=$(SRC:.cpp=.o)

NAME=myawesome

all: $(NAME)


%.o: %.cpp
	$(CPP) $(CPP_FLAG)  -c $< -o $@

$(NAME): $(OBJ)
	$(CPP) $(CPP_FLAG) $(OBJ) -o $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
