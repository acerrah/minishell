/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:14:42 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/23 01:52:04 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	close_pipe_fd(void)
{
	int	i;

	i = 0;
	while (i < g_data->pipe_count)
	{
		close(g_data->pipe_fd[i][0]);
		close(g_data->pipe_fd[i][1]);
		free(g_data->pipe_fd[i]);
		i++;
	}
	free(g_data->pipe_fd);
}

void	execute_multi_command(char **command, int is_builtin, int i,
char *actual_path)
{
	if (actual_path || is_builtin == TRUE)
	{
		g_data->pid = fork();
		if (g_data->pid == CHILD)
		{
			pipe_redirection(i);
			close_pipe_fd();
			if (is_builtin == TRUE)
				execute_builtin(command, g_data->cmd[i]->size);
			else
				execve(actual_path, command, g_data->env->data);
			exit(1);
		}
		else
			free(actual_path);
	}
	else
	{
		printf("minishell: %s: command not found\n", command[0]);
		g_data->exit_status = 127;
	}
}

void	init_multi_command_execution(void)
{
	int		i;
	int		is_builtin;
	char	*actual_path;

	i = -1;
	actual_path = NULL;
	create_pipe_fd();
	while (i++ < g_data->pipe_count)
	{
		if (!(g_data->cmd[i]->data[0]))
		{
			g_data->exit_status = 1;
			close_pipe_fd();
			printf("minishell: syntax error near unexpected token `|'\n");
			return ;
		}
		is_builtin = is_builtin_check(g_data->cmd[i]->data[0]);
		if (is_builtin == FALSE)
			actual_path = find_actual_path(g_data->cmd[i]->data);
		execute_multi_command(g_data->cmd[i]->data, is_builtin, i, actual_path);
	}
	close_pipe_fd();
	while (waitpid(-1, &g_data->exit_status, 0) != -1)
		continue ;
}
