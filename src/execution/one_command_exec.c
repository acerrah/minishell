/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:38:18 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/17 22:15:49 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

void execute_one_line_command(char *actual_path, int is_builtin, char **command)
{
	if (actual_path || is_builtin)
	{
		g_data->pid = fork();
		if (g_data->pid == CHILD)
		{
			// Set standard input and output files.
			if (is_builtin == TRUE)
				execute_builtin(command);
			execve(actual_path, command, g_data->env->data);
			exit(1);
		}
		//wait for child process to finish
		while (waitpid(-1, &g_data->status, 0) != -1)
			continue ;
		free(actual_path);
	}
}

void init_one_line_execution(void)
{
	char **command;
	char *actual_path;
	int	is_builtin;

	g_data->in_fd = -2;
	g_data->out_fd = -2;
	actual_path = NULL;

	command = g_data->cmd[0]->data;
	is_builtin = is_it_builtin(command);
	if (is_builtin == FALSE)
		actual_path = find_actual_path(command); //finding and returning the actual path of an executable command
	g_data->signal_select = CHILD;
	execute_one_line_command(actual_path, is_builtin, command);
	g_data->signal_select = DEFAULT;
}
