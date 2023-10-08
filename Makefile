NAME = minishell

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -rf
LIB = ./lib/lib.a

SRCS  = main.c

all: $(NAME)

$(NAME): $(LIB)
	@$(CC) $(CFLAGS) $(SRCS) $(LIB) -o $(NAME)

$(LIB):
	@make -C ./lib

clean:
	@$(RM) checker.dSYM
	@$(RM) push_swap.dSYM
	@make clean -C ./lib

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@make fclean -C ./lib

re: fclean all

.PHONY:  all clean fclean re lib
