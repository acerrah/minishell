/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:47:06 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/15 13:30:02 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

int is_it_builtin(char **command)
{
	if (len_2d(command) == 0)
		return (FALSE);
	if (ft_strcmp(command[0], "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(command[0], "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(command[0], "env") == 0)
		return (TRUE);
	else if (ft_strcmp(command[0], "export") == 0)
		return (TRUE);
	else if (ft_strcmp(command[0], "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(command[0], "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(command[0], "unset") == 0)
		return (TRUE);
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
		ft_pwd(command);
	else if (ft_strcmp(command[0], "exit") == 0)
		ft_exit(command);
	else if (ft_strcmp(command[0], "unset") == 0)
		ft_unset(command);
}

