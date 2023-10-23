/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 00:55:13 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/22 10:31:18 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_it_builtin(char **command, int size)
{
	if (size == 0)
		return (FALSE);
	else if (ft_strcmp(command[0], "env") == 0)
	{
		ft_env(command);
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "export") == 0)
	{
		ft_export(command, size);
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "pwd") == 0)
	{
		ft_pwd();
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		ft_exit(command, size);
		return (TRUE);
	}
	else
		return (is_it_builtin2(command, size));
}

int	is_it_builtin2(char **command, int size)
{
	if (ft_strcmp(command[0], "echo") == 0)
	{
		ft_echo(command, size);
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "cd") == 0)
	{
		ft_cd(command);
		return (TRUE);
	}
	else if (ft_strcmp(command[0], "unset") == 0)
	{
		ft_unset(command, size);
		return (TRUE);
	}
	else
		return (FALSE);
}

int	is_builtin_check(char *command)
{
	if (ft_strcmp(command, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "unset") == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	execute_builtin(char **command, int size)
{
	if (ft_strcmp(command[0], "env") == 0)
		ft_env(command);
	else if (ft_strcmp(command[0], "export") == 0)
		ft_export(command, size);
	else if (ft_strcmp(command[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command[0], "exit") == 0)
		ft_exit(command, size);
	else if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(command, size);
	else if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command);
	else if (ft_strcmp(command[0], "unset") == 0)
		ft_unset(command, size);
}
