NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -L./readline/lib -I./lib/readline/include -g #-fsanitize=address
LIB = ./lib/lib.a
READLINE = ./lib/readline/.minishell
LDFLAGS	= -L./lib/readline -lreadline
RM = rm -rf

SRCS  = ./src/minishell/main.c \
		./src/minishell/handle_g_data.c \
		./src/minishell/create_exp.c \
		./src/lexer/lexer.c \
		./src/dynamic_arrays/dynamic_array.c \
		./src/dynamic_arrays/dynamic_intarray.c \
		./src/dynamic_arrays/push.c \
		./src/redirection/redirection.c \
		./src/redirection/ioputs.c \
		./src/redirection/delete_arg.c \
		./src/redirection/take_arg.c \
		./src/loop/loop.c \
		./src/loop/loop_clear.c \
		./src/loop/clear.c \
		./src/parser/parser.c  \
		./src/parser/parser_utils.c  \
		./src/parser/env_res.c  \
		./src/parser/opening_fd.c \
		./src/parser/heredoc.c \
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
		./src/execution/multi_command_exec.c \
		./src/utils/built-in-utils.c \
		./src/utils/export_utils.c \
		./src/utils/duplicate_utils.c 

all: $(NAME)

$(NAME): $(LIB) $(SRCS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) $(LIB) -o $(NAME)

$(LIB): $(READLINE)
	@make -C ./lib

$(READLINE):
	@make -C ./lib/readline

clean:
	@make clean -C ./lib

fclean:	clean
	@$(RM) $(NAME)
	@make fclean -C ./lib

ffclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(NAME).dSYM
	@make fclean -C ./lib
	@make fclean -C ./lib/readline

re: fclean all

.PHONY:  all clean fclean re lib
