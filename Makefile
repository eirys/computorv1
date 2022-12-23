# ================ TARGETS =======================

NAME	= computor

CC		= c++
CFLAGS	= -Wall -Werror -Wextra -g -std=c++11
INC		= -I./incs

SRC		= main.cpp
OBJ		= $(SRC:.cpp=.o)

ifdef debug
	CFLAGS += -DDEBUG=1
endif

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
