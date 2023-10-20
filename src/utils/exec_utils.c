/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:47:06 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/20 21:22:40 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

void	redirect_std_files(int in_fd, int out_fd)
{
	if (out_fd > 2)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			exit(1);
		close(out_fd);
	}
	if (in_fd > 2)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			exit(1);
		close(in_fd);
	}
}


void create_pipe_fd(void)
{
    int i;

    i = 0;
    g_data->pipe_fd = malloc(sizeof(int*) * g_data->pipe_count);
    while (i < g_data->pipe_count)
    {
        g_data->pipe_fd[i] = malloc(sizeof(int) * 2);
        if (pipe(g_data->pipe_fd[i]) == -1)
            exit(1);
        i++;
    }
}

void	pipe_redirection(int i)
{
	if (i == 0)
		dup2(g_data->pipe_fd[i][1], STDOUT_FILENO);
	else if (i == g_data->pipe_count)
		dup2(g_data->pipe_fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(g_data->pipe_fd[i - 1][0], STDIN_FILENO);
		dup2(g_data->pipe_fd[i][1], STDOUT_FILENO);
	}
	if (g_data->fd[0]->arr[i] > 2)
		dup2(g_data->fd[0]->arr[i], STDIN_FILENO);
	if (g_data->fd[1]->arr[i] > 2)
		dup2(g_data->fd[1]->arr[i], STDOUT_FILENO);
}

int is_it_builtin(char **command)
{
	if (len_2d(command) == 0)
		return (FALSE);
	else if (ft_strcmp(command[0], "env") == 0)
	{
		ft_env(command);
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "export") == 0)
	{
		ft_export(command);
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "pwd") == 0)
	{
		ft_pwd();
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		ft_exit(command);
		return (TRUE);
	}

	else
		return (is_it_builtin2(command));
}

int is_it_builtin2(char **command)
{
	if (ft_strcmp(command[0], "echo") == 0)
	{
		ft_echo(command);
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "cd") == 0)
	{
		ft_cd(command);
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "unset") == 0)
	{
		ft_unset(command);
		return (TRUE);
	}
	else
		return (FALSE);
}

