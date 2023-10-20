/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:14:42 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/20 23:37:40 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data	*g_data;

void close_pipe_fd(void)
{
	int i;

	i = 0;
	while (i < g_data->pipe_count)
	{
		close(g_data->pipe_fd[i][0]);
		close(g_data->pipe_fd[i][1]);
		i++;
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
			close_pipe_fd();
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
		execute_multi_command(command, is_builtin, i, actual_path);
	}
	close_pipe_fd();
	while (waitpid(-1, &g_data->exit_status, 0) != -1)
		continue ;
}
