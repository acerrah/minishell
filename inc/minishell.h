/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 03:50:23 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 01:41:17 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
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
# include <termios.h>

# define TRUE 1
# define FALSE 0
# define INITIAL_CAPACITY 8
# define PIPE 0
# define REDIR_OUT 1
# define REDIR_OUT_APPEND 2
# define REDIR_IN 3
# define REDIR_HEREDOC 4
# define IN 0
# define OUT 1
# define STDIN 0
# define STDOUT 1
# define SUCCESS 1
# define ERROR 0
# define BUFF_SIZE 1024
# define CHILD 0
# define HEREDOC 1
# define DEFAULT 2

typedef struct s_dynintarray{
	int	*arr;
	int	size;
	int	capacity;
}	t_dynintarray;

typedef struct s_dynarray {
	char	**data;
	size_t	size;
	size_t	capacity;
}	t_dynarray;

typedef struct s_redirections {
	t_dynintarray	*type;
	t_dynarray		*file;
}	t_redirections;

typedef struct s_data
{
	t_dynarray		*env;
	t_dynarray		*exp;
	t_dynarray		*lex;
	t_dynarray		*lex_parsed;
	t_dynintarray	**fd;
	int				**pipe_fd;
	t_dynarray		**cmd;
	int				cmd_size;
	int				signal_flag;
	int				signal_select;
	int				signal_exit;
	pid_t			pid;
	int				exit_status;
	char			**path;
	t_redirections	*redirections;
	int				pipe_count;
	int				line;
}	t_data;

t_dynarray		*dynarray_create(void);
void			dynarray_destroy(t_dynarray *arr);
int				dynarray_resize(t_dynarray *arr, size_t new_capacity);
int				dynarray_push(t_dynarray *arr, char *str);
int				dynarray_push_to(t_dynarray *arr, char *str, size_t index);
t_dynintarray	*dynintarray_create(void);
void			dynintarray_destroy(t_dynintarray *d_arr);
void			dynintarray_resize(t_dynintarray *d_arr, int newCapacity);
void			dynintarray_push(t_dynintarray *d_arr, int value);
int				dynintarray_pull(t_dynintarray *d_arr, int index);
void			dynintarray_set(t_dynintarray *d_arr, int index, int value);
int				dynarray_remove(t_dynarray *arr, size_t index);
int				lexer(char *input_str, int in_single_quotes,
					int in_double_quotes, int last_pipe);
char			**ft_strdup_2d(char **str);
void			handle_g_data(char **env);
void			ft_export(char **comman, int size);
void			ft_env(char **command);
void			ft_cd(char **command);
int				ft_echo(char **av, int size);
int				ft_pwd(void);
int				ft_unset(char **command, int size);
void			ft_exit(char **command, int size);
int				ft_signal_handler(void);
int				is_it_builtin(char **command, int size);
char			*find_actual_path(char **command);
void			loop(char *input_str, char *trim_input_str);
void			loop_clear(char *input_str, char *trim_input_str);
void			init_one_command_execution(void);
void			take_pipe_count(void);
void			redirect_std_files(int in_fd, int out_fd);
void			ctrl_d(char	*input);
void			create_pipe_fd(void);
int				is_it_builtin2(char **command, int size);
void			init_multi_command_execution(void);
void			pipe_redirection(int i);
void			execute_builtin(char **command, int size);
int				is_builtin_check(char *command);
void			single_to_double_quote(char *command);
int				eq_check(char *command);
char			*format_exp(char *command);
int				int_strchr(const char *s, int c);
void			quotes(char c, int *in_single_quotes, int *in_double_quotes);
int				return_error(void);
int				ioput(char *str, int j,
					int in_single_quotes, int in_double_quotes);
int				input(char *str, int j);
int				output(char *str, int j);
char			*take_next_arg(char *str);
char			*last_arg_in_quote(char *str, int i, int j);
char			*next_arg_in_quote(char *str, int i);
void			delete_next_arg(char *str, int i);
void			delete_last_arg(char *str, int i);
int				redirections(int i, int j,
					int in_single_quotes, int in_double_quotes);
int				heredoc(char *str, int fd, char *line);
int				parser(size_t i, int k, int m, int j);
int				dynarray_push_to(t_dynarray *arr,
					char *str, size_t index);
char			*env_res(char *str, int i);
int				check_is_alnum(char c);
char			*take_next(char *str);
int				open_fd(void);
int				ascii_bigger(char *str1, char *str2);
void			take_pipe_count(void);
void			malloc_cmd(void);
void			spliting_lex(size_t i, int j, int *k);
char			*return_env_var(size_t *i);
void			push_to_cmd(size_t *i, int j, int *k, int m);
void			copy_exp(void);
void			trimming(size_t *i, int *k, int *m);
int				duplicate_check(char *variable);
void			clear_rd_fd(void);
void			clear_rd(void);
int				clear_ctrlc(int check, char	*input_str, char *trim_input_str);
int				check_and_clear(int check,
					char	*input_str, char *trim_input_str);

#endif
