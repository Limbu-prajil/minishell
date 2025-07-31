# minishell/Makefile

NAME = minishell

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
RL_FLAGS = -lreadline

SRC = ./src/main.c ./src/minishell_loop.c \
./src/utils/str_utils.c  ./src/utils/ft_strchr.c ./src/utils/ft_strjoin.c \
./src/utils/ft_strnstr.c ./src/utils/ft_isschar.c ./src/utils/ft_isspace.c \
./src/tokenizer/tokenizer.c \
./src/tokenizer/utils/utils.c \
./src/tokenizer/helper_functions/handle_esc_seq.c ./src/tokenizer/helper_functions/handle_special.c \
./src/tokenizer/helper_functions/handle_word.c ./src/tokenizer/helper_functions/handle_quotes.c \
./src/parser/parser.c \
./src/parser/parser_utils/is_syntax_error.c ./src/parser/parser_utils/is_redirection.c \
./src/parser/parser_utils/free_ast.c \
./src/executor/executor.c \
./src/executor/builtins/builtin_echo.c \
./src/executor/builtins/builtin_pwd.c \
./src/executor/builtins/builtin_cd.c \
./src/executor/builtins/builtin_env.c \
./src/executor/builtins/builtin_export.c \
./src/env/init_env_list.c ./src/env/get_env_value.c ./src/env/update_env.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(RL_FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
