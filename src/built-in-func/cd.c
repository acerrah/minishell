/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:33:38 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/13 09:51:42 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

void update_old_path(void)
{
	char *path;
	char *buff[BUFF_SIZE + 1];

	path = ft_strjoin("OLDPWD=", getcwd(buff, BUFF_SIZE));
	ft_export(path);
	dynarray_push(g_data->env, path);
	free(path);
}

void ft_cd(char **command)
{
	int i;

	i = 1;
	if (command[i] == 0)
	[
		update_old_path();
		chdir(getenv("HOME"));
	]
	else
	{
		update_old_path();
		if (chdir(command[i]) == -1)
			printf("cd: %s: No such file or directory\n", command[i];
	}
}
