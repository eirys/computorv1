# ================ TARGETS =======================

NAME	= computor

CC		= c++
CFLAGS	= -Wall -Werror -Wextra -g
INC		= -I./incs

SRC		= main.cpp
OBJ		= $(SRC:.cpp=.o)

# ================= RULES ========================

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ)

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
