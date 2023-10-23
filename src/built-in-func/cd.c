/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:33:38 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/23 04:11:24 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	update_old_path(void)
{
	char	*path;
	char	buff[BUFF_SIZE + 1];

	path = ft_strjoin("OLDPWD=", getcwd(buff, BUFF_SIZE));
	dynarray_push(g_data->exp, path);
	dynarray_push(g_data->env, path);
	free(path);
}

int	nemo_find_home(void)
{
	size_t	i;

	i = 0;
	while (i < g_data->env->size)
	{
		if (ft_strncmp(g_data->env->data[i], "HOME=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_cd(char **command)
{
	int	i;

	i = 1;
	if (command[i] == 0)
	{
		if (nemo_find_home() != -1)
		{
			update_old_path();
			chdir(g_data->env->data[nemo_find_home()] + 5);
		}
		else
			printf("cd: HOME not set\n");
	}
	else
	{
		update_old_path();
		if (chdir(command[i]) == -1)
			printf("cd: %s: No such file or directory\n", command[i]);
	}
}
