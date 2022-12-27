# ================ TARGETS =======================

NAME	= computor

CC		= c++
CFLAGS	= -Wall -Werror -Wextra -g -std=c++11
INC		= -I./incs

SRCS	= main.cpp
OBJS	= $(SRCS:.cpp=.o)

SRC		= $(addprefix src/, $(SRCS))
OBJ		= $(addprefix obj/, $(OBJS))

ifdef debug
	CFLAGS += -DDEBUG=1
endif

# ================= RULES ========================

.PHONY: all
all: obj $(NAME)

obj:
	mkdir obj

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: clean
clean:
	rm -rf obj

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
