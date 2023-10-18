/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:47:06 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/18 14:31:38 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

void	redirect_std_files(int in_fd, int out_fd)
{
	if (out_fd >= 0)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			exit(1);
		close(out_fd);
	}
	if (in_fd >= 0)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)

		close(in_fd);
	}
}

int is_it_builtin(char **command)
{
	if (len_2d(command) == 0)
		return (FALSE);
	if (ft_strcmp(command[0], "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(command[0], "cd") == 0)
		return (TRUE);
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
		return (TRUE);
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		ft_exit(command);
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

void execute_builtin(char **command)
{
	if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command);
	else if (ft_strcmp(command[0], "env") == 0)
		ft_env(command);
	else if (ft_strcmp(command[0], "export") == 0)
		ft_export(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command[0], "unset") == 0)
		ft_unset(command);
}

