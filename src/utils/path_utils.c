/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:10:02 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/16 20:29:59 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

static void	find_path(void)
{
	int i;

	i = 0;
	while (g_data->envp[i])
	{
		if (ft_strncmp(g_data->envp[i], "PATH=", 5) == 0)
		{
			g_data->path = ft_split(g_data->envp[i] + 5, ':');
			break ;
		}
		i++;
	}

}

statis char	*access_valid_path(char *command)
{
	int i;
	char *actual_path;

	i = 0;
	while (g_data->path[i])
	{
		actual_path = ft_strdup(g_data->path[i]);
		actual_path = ft_strjoin(actual_path, "/");
		actual_path = ft_strjoin(g_data->path[i], command);
		if (access(actual_path, F_OK) == 0)
			return (actual_path);
		free(actual_path);
		i++;
	}
	return (NULL);
}



char	*find_actual_path(char **command)
{
	int i;
	char *actual_path;

	find_path();
	//make error checks
	if (command[0] == NULL)
		ft_strdup("");
	if (command == NULL)
		return (NULL);
	// if it is absolute path return it
	if (command[0][0] == '/' && access(command[0], F_OK) != -1))
	 	return (command[0]);
	actual_path = access_valid_path(command[0]);
	if (actual_path)
		return (actual_path);
	// free path to prevent leaks
	return (NULL);

}
