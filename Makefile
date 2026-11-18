# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude

# Directories and files
SRC = $(addprefix src/, main.c checkers.c initializations.c philosopher_routine.c \
      philosophers_actions.c utils.c validations.c)
OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
NAME = philo

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
