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


#define TRUE 1
#define true 1
#define false 0
#define FALSE 0
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

# define SUCCESS 1
# define ERROR 0

# define BUFF_SIZE 1024

//Flags for signal handling
# define CHILD 0
# define HEREDOC 1
# define DEFAULT 2

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
    t_dynarray		*env;
    t_dynarray		*exp;
    t_dynarray		*lex;
    t_dynarray		*lex_parsed;
    t_dynintarray	**fd;
    t_dynarray	**cmd;
	int			signal_flag;
	int			signal_select;
	pid_t			pid;
	int			in_fd;
	int			out_fd;
	int			exit_status;
	char		**path;
    t_redirections *redirections;
	int 		pipe_count;
    int line;
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
int			dynarray_remove(t_dynarray *arr, size_t index);
int lexer(char *input_str, bool in_single_quotes,
bool in_double_quotes, int last_pipe, int i);
char		**ft_strdup_2d(char **str);
void		handle_g_data(char **env);
void		ft_export(char **command);
void		ft_env(char **command);
void		ft_cd(char **command);
int			ft_echo(char **av);
int			ft_pwd(void);
int			ft_unset(char **command);
void		ft_exit(char **command);
int			len_2d(char **command);
int			ft_signal_handler(void);
int			is_it_builtin(char **command);
void		execute_builtin(char **command);
char		*find_actual_path(char **command);
void		loop(void);
void		loop_clear(char *input_str);
int			parser();
int			redirections();
void		init_one_command_execution(void);
void		take_pipe_count();
void		redirect_std_files(int in_fd, int out_fd);
void		ctrl_d(char	*input);
void		create_pipe_fd(void);

#endif
