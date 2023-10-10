#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <pthread.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

#define true 1
#define false 0
#define bool int
#define INITIAL_CAPACITY 8

typedef struct s_dynarray {
    char **data;
    size_t size;
    size_t capacity;
} t_dynarray;

typedef struct s_data
{
    t_dynarray *env;
    t_dynarray *exp;
    t_dynarray *lex;
    t_dynarray *cmd;
    t_dynarray *redirections;
    t_dynarray *heredocs;
} t_data;

t_dynarray *dynarray_create();
void        dynarray_destroy(t_dynarray *arr);
int         dynarray_resize(t_dynarray *arr, size_t new_capacity);
int         dynarray_push(t_dynarray *arr, char *str);
void        lexer(char *input_str, bool in_single_quotes,
    bool in_double_quotes, int last_pipe, int i);
char        **ft_strdup_2d(char **str);
void        handle_g_data(char **env);
#endif