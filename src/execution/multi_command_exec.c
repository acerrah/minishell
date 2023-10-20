/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:14:42 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/20 22:35:42 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data	*g_data;

void close_all_pipes(void)
{
	int i;

	i = 0;
	printf("pipe_count: %d\n", g_data->pipe_count);
	while (i < g_data->pipe_count)
	{
		close(g_data->pipe_fd[i][0]);
		close(g_data->pipe_fd[i][1]);
		i++;
	}
	i = 0;
	while (i < g_data->pipe_count + 1)
	{
		close(g_data->fd[0]->arr[i]);
		close(g_data->fd[1]->arr[i]);
		i++;
	}

}


void	close_pipe(int i)
{
	if (i == g_data->pipe_count)
		close_all_pipes();
	else if (i > 0 && i < g_data->pipe_count)
	{
		close(g_data->pipe_fd[i - 1][0]);
		close(g_data->pipe_fd[i - 1][1]);
	}
}

void	execute_multi_command(char **command,int is_builtin, int i, char *actual_path)
{
	if (actual_path || is_builtin == TRUE)
	{
		g_data->pid = fork();
		if (g_data->pid == CHILD)
		{
			pipe_redirection(i);
			execve(actual_path, command, g_data->env->data);
			exit(1);
		}
		else
		{
			free(actual_path);
			close_pipe(i);
		}
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
	char	**command;
	char	*actual_path;

	i = -1;
	actual_path = NULL;
	create_pipe_fd();
	while (i++ < g_data->pipe_count)
	{
		command = g_data->cmd[i]->data;
		is_builtin = is_it_builtin(command);
		if (is_builtin == FALSE)
			actual_path = find_actual_path(command);
		printf("actual_path: %s\n", actual_path);
		execute_multi_command(command, is_builtin, i, actual_path);
	}
	close_all_pipes();
	while (waitpid(-1, &g_data->exit_status, 0) != -1)
		continue ;
}
