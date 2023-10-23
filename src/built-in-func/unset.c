/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 03:36:54 by ioztimur          #+#    #+#             */
/*   Updated: 2023/10/23 03:51:08 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	remove_from_env(char *cmd)
{
	size_t	c;
	char	*tmp;

	c = 0;
	tmp = ft_strjoin(cmd, "=");
	while (c < g_data->env->size)
	{
		if (ft_strncmp(tmp, g_data->env->data[c], ft_strlen(tmp)) == 0)
		{
			dynarray_remove(g_data->env, c);
			free(tmp);
			break ;
		}
		c++;
	}
}

int	ft_unset(char **command, int size)
{
	int		i;
	size_t	j;

	i = 1;
	j = 0;
	if (command[i] == 0)
		printf("unset: not enough arguments\n");
	while (i < size)
	{
		while (j < g_data->exp->size)
		{
			if (ft_strncmp(command[i], g_data->exp->data[j], \
			ft_strlen(command[i])) == 0)
			{
				dynarray_remove(g_data->exp, j);
				remove_from_env(command[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
