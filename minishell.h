#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/libft/libft.h"
# include "./lib/gnl/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# define SUCCESS 1
# define ERROR 0
# define BUFF_SIZE 4096

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_data
{
	char **env;
}	t_data;

#endif
