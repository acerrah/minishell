/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:38:18 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/22 11:38:06 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	execute_one_command(char *actual_path, char **command, int is_builtin)
{
	if (actual_path || is_builtin == TRUE)
	{
		g_data->pid = fork();
		if (g_data->pid == CHILD)
		{
			redirect_std_files(g_data->fd[0]->arr[0], g_data->fd[1]->arr[0]);
			execve(actual_path, command, g_data->env->data);
			exit(1);
		}
		free(actual_path);
	}
	else
	{
		printf("bash: command not found: %s\n", command[0]);
		g_data->exit_status = 127;
	}
}

void	init_one_command_execution(void)
{
	char	**command;
	char	*actual_path;
	int		is_builtin;

	actual_path = NULL;
	command = g_data->cmd[0]->data;
	is_builtin = is_it_builtin(command, g_data->cmd[0]->size);
	if (is_builtin == FALSE)
		actual_path = find_actual_path(command);
	execute_one_command(actual_path, command, is_builtin);
	while (waitpid(-1, &g_data->exit_status, 0) != -1)
		continue ;
}
