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
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

#define true 1
#define false 0
#define bool int
#define INITIAL_CAPACITY 8

typedef struct s_dynintarray{
    int *arr;
    int size;
    int capacity;
} t_dynintarray;

typedef struct s_dynarray {
    char **data;
    size_t size;
    size_t capacity;
} t_dynarray;

/* types are as follows: */
/* 0: no redirection     */
/* 1: >                  */
/* 2: >>                 */
/* 3: <                  */
/* 4: <<                 */
typedef struct s_redirections {
    t_dynintarray *type;
    t_dynarray *file;
} t_redirections;

typedef struct s_data
{
    t_dynarray *env;
    t_dynarray *exp;
    t_dynarray *lex;
    t_dynarray *cmd;
    t_redirections *redirections;
} t_data;

t_dynarray *dynarray_create();
void        dynarray_destroy(t_dynarray *arr);
int         dynarray_resize(t_dynarray *arr, size_t new_capacity);
int         dynarray_push(t_dynarray *arr, char *str);
t_dynintarray* dynintarray_create();
void        dynintarray_destroy(t_dynintarray *d_arr);
void        dynintarray_resize(t_dynintarray *d_arr, int newCapacity);
void        dynintarray_push(t_dynintarray *d_arr, int value);
int         dynintarray_pull(t_dynintarray *d_arr, int index);
void        dynintarray_set(t_dynintarray *d_arr, int index, int value);
void        lexer(char *input_str, bool in_single_quotes,
    bool in_double_quotes, int last_pipe, int i);
char        **ft_strdup_2d(char **str);
void        handle_g_data(char **env);
void        ft_export(char **command);

#endif