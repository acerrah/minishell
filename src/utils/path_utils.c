/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:10:02 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/17 10:40:08 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

static void	find_path(void)
{
	int i;

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

char	*new_str_join(char *s1, char *s2)
{
	char	*back;
	size_t	total_len;

	if (!s1 || !s2)
		return (0);
	total_len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	back = malloc(total_len * sizeof(char));
	if (!back)
		return (0);
	ft_strlcpy(back, s1, ft_strlen(s1) + 1);
	ft_strlcat(back, s2, total_len);
	free(s1);
	return (back);
}

static char	*access_valid_path(char *command)
{
	int i;
	char *actual_path;

	i = 0;
	while (g_data->path[i])
	{
		actual_path = ft_strdup(g_data->path[i]);
		actual_path = new_str_join(actual_path, "/");
		actual_path = new_str_join(actual_path, command);
		if (access(actual_path, F_OK) != -1)
			return (actual_path);
		free(actual_path);
		i++;
	}
	return (NULL);
}



char	*find_actual_path(char **command)
{
	char *actual_path;

	find_path();
	//make error checks
	if (command[0] == NULL)
		ft_strdup("");
	if (command == NULL)
		return (NULL);
	// if it is absolute path return it
	if (command[0][0] == '/' && access(command[0], F_OK) != -1)
		return (command[0]);
	actual_path = access_valid_path(command[0]);
	if (actual_path)
		return (actual_path);
	// free path to prevent leaks
	return (NULL);

}
