# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude

# Directories and files
SRC = $(addprefix src/, main.c checkers.c initializations.c philosopher_routine.c \
      philosophers_actions.c utils.c validations.c)
OBJ = $(SRC:.c=.o)
NAME = philo

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
