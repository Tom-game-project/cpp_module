.PHONY: all clean fclean re

SRC= \
    BitcoinExchange.cpp \
    main.cpp

OBJ=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)

NAME=btc

CXX=c++
DEP_FLAG= -MMD -MP
CXX_FLAGS= -Wall -Wextra -Werror -Wconversion -std=c++98 -pedantic-errors \
           -Weffc++ -Wreorder -Wold-style-cast \
           -Woverloaded-virtual -Wnon-virtual-dtor $(DEP_FLAG)

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)
