NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I./lib/readline/include -g
RM = rm -rf
LIB = ./lib/lib.a
READLINE = ./lib/readline/.minishell
LDFLAGS			= -L./lib/readline -lreadline

SRCS  = ./src/main.c \
		./src/lexer.c \
		./src/dynamic_array.c \
		./src/handle_g_data.c \
		./src/dynamic_intarray.c \
		./src/redirection.c \
		./src/loop.c \
		./src/parser.c  \
		./src/built-in-func/exit.c \
		./src/built-in-func/cd.c \
		./src/built-in-func/echo.c \
		./src/built-in-func/env.c \
		./src/built-in-func/export.c \
		./src/built-in-func/pwd.c \
		./src/built-in-func/unset.c \
		./src/execution/one_command_exec.c \
		./src/signals/signal_handler.c \
		./src/utils/exec_utils.c \
		./src/utils/path_utils.c \
		./src/execution/multi_command_exec.c

all: $(NAME)

$(NAME): $(LIB) $(SRCS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) $(LIB) -o $(NAME)

$(LIB): $(READLINE)
	@make -C ./lib

$(READLINE):
	@make -C ./lib/readline

clean:
	@$(RM) checker.dSYM
	@$(RM) push_swap.dSYM
	@make clean -C ./lib

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(NAME).dSYM
	@make fclean -C ./lib

ffclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(NAME).dSYM
	@make fclean -C ./lib
	@make fclean -C ./lib/readline

re: fclean all

.PHONY:  all clean fclean re lib
