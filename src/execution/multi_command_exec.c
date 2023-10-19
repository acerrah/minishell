/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:14:42 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/19 13:17:23 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data	*g_data;

void close_all_pipes(void)
{
	int i;

	i = 0;
	while (i < g_data->pipe_count)
	{
		close(g_data->fd[i][0]);
		close(g_data->fd[i][1]);
		i++;
	}
}

void	pipe_redirection(int i)
{
	if (i == 0)
	{
		dup2(g_data->fd[i][1], STDOUT_FILENO);
		close(g_data->fd[i][1]);
	}
	else if (i > 0 && i < g_data->pipe_count)
	{
		dup2(g_data->fd[i - 1][0], STDIN_FILENO);
		dup2(g_data->fd[i][1], STDOUT_FILENO);
		close(g_data->fd[i - 1][0]);
		close(g_data->fd[i][1]);
	}
	else if (i == g_data->pipe_count)
	{
		dup2(g_data->fd[i - 1][0], STDIN_FILENO);
		close_all_pipes();
	}
	close_all_pipes();
}

void	close_pipe(int i)
{
	if (i == g_data->pipe_count)
		close_all_pipes();
	else if (i < 0 && i < g_data->pipe_count)
	{
		close(g_data->fd[i - 1][0]);
		close(g_data->fd[i -1][1]);
	}

}

void	execute_multi_command(char **command, int is_builtin, int i, char *actual_path)
{
	if (actual_path || is_builtin == TRUE)
	{
		g_data->signal_select = CHILD;
		g_data->pid = fork();
		if (g_data->pid == CHILD)
		{
			pipe_redirection(i);
			redirect_std_files(g_data->in_fd, g_data->out_fd);
			if (is_builtin == TRUE)
				exec_builtin(command);
			execve(actual_path, command, g_data->env);
			exit(1);
		}
		else
		{
			close_pipe(i);
			free(actual_path);
		}
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
	//number of pipes needed to be created
	//number of commands - 1
	while (i++ < g_data->pipe_count)
	{
		g_data->in_fd = -2;
		g_data->out_fd = -2;
		command = g_data->cmd[i]->data;
		is_builtin = is_it_builtin(command);
		if (is_builtin == FALSE)
			actual_path = find_actual_path(command);

	}
}
