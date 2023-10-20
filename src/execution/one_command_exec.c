/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:38:18 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/19 23:58:40 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

void execute_one_command(char *actual_path, char **command, int is_builtin)
{
	if (actual_path || is_builtin == TRUE)
	{
		g_data->pid = fork();
		if (g_data->pid == CHILD)
		{
			// Set standard input and output files.
			redirect_std_files(g_data->fd[0]->arr[0], g_data->fd[1]->arr[0]);
			execve(actual_path, command, g_data->env->data);
			exit(1);
		}
		//wait for child process to finish
		while (waitpid(-1, &g_data->exit_status, 0) != -1)
			continue ;
		free(actual_path);
	}
	else
	{
		printf("bash: command not found: %s\n", command[0]);
		g_data->exit_status = 127;
	}
}

void init_one_command_execution(void)
{
	char **command;
	char *actual_path;
	int	is_builtin;

	actual_path = NULL;
	command = g_data->cmd[0]->data;

	is_builtin = is_it_builtin(command);
	if (is_builtin == FALSE)
		actual_path = find_actual_path(command); //finding and returning the actual path of an executable command
	execute_one_command(actual_path, command, is_builtin);

}
