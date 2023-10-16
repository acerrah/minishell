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
#define PIPE 0
#define REDIR_OUT 1
#define REDIR_OUT_APPEND 2
#define REDIR_IN 3
#define REDIR_IN_HERE_DOC 4
#define IN 0
#define OUT 1
#define STDIN 0
#define STDOUT 1

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

typedef struct s_redirections {
    t_dynintarray *type;
    t_dynarray *file;
} t_redirections;

typedef struct s_data
{
    t_dynarray *env;
    t_dynarray *exp;
    t_dynarray *lex;
    t_dynarray *lex_parsed;
    t_dynarray **cmd;
    t_dynintarray **fd;
    t_redirections *redirections;
    int line;
} t_data;


t_dynarray      *dynarray_create();
void            dynarray_destroy(t_dynarray *arr);
int             dynarray_resize(t_dynarray *arr, size_t new_capacity);
int             dynarray_push(t_dynarray *arr, char *str);
int             dynarray_remove(t_dynarray *arr, size_t index);
t_dynintarray   *dynintarray_create();
void            dynintarray_destroy(t_dynintarray *d_arr);
void            dynintarray_resize(t_dynintarray *d_arr, int newCapacity);
void            dynintarray_push(t_dynintarray *d_arr, int value);
int             dynintarray_pull(t_dynintarray *d_arr, int index);
void            dynintarray_set(t_dynintarray *d_arr, int index, int value);
int            lexer(char *input_str, bool in_single_quotes,
    bool in_double_quotes, int last_pipe, int i);
char            **ft_strdup_2d(char **str);
void            handle_g_data(char **env);
void            loop(void);
void            loop_clear(char *input_str);
int             parser();
int            redirections();
void            ft_export(char **command);

#endif