/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:10:02 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/23 04:06:44 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

static void	find_path(void)
{
	int	i;

	i = 0;
	while (g_data->env->data[i])
	{
		if (ft_strncmp(g_data->env->data[i], "PATH=", 5) == 0)
		{
			g_data->path = ft_split(g_data->env->data[i] + 5, ':');
			break ;
		}
		i++;
	}
}

void	free_path(void)
{
	int	i;

	i = 0;
	while (g_data->path[i])
	{
		free(g_data->path[i]);
		i++;
	}
	free(g_data->path);
}

char	*access_valid_path(char *command)
{
	int		i;
	char	*actual_path;
	char	*tmp;

	i = 0;
	if (access(command, X_OK) != -1)
		return (ft_strdup(command));
	while (g_data->path[i])
	{
		tmp = ft_strjoin(g_data->path[i], "/");
		actual_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(actual_path, F_OK) != -1)
		{
			free_path();
			return (actual_path);
		}
		free(actual_path);
		i++;
	}
	free_path();
	return (NULL);
}

char	*find_actual_path(char **command)
{
	char	*actual_path;

	find_path();
	if (g_data->path == NULL)
		return (NULL);
	if (command[0] == NULL)
		return (ft_strdup(""));
	if (command == NULL)
		return (NULL);
	if (command[0][0] == '/' && access(command[0], F_OK) != -1)
		return (ft_strdup(command[0]));
	actual_path = access_valid_path(command[0]);
	if (actual_path)
		return (actual_path);
	return (NULL);
}

int	int_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s && *s != 0)
		return (0);
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
