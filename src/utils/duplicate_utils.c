/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 08:48:21 by ioztimur          #+#    #+#             */
/*   Updated: 2023/10/22 08:50:22 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	duplicate_in_env(char *variable, int j)
{
	size_t	i;

	i = 0;
	while (i < g_data->env->size)
	{
		if (ft_strncmp(variable, g_data->env->data[i], j + 1) == 0)
		{
			dynarray_remove(g_data->env, i);
			break ;
		}
		i++;
	}
}

int	duplicate_check(char *variable)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (variable[j] && variable[j] != '=')
		j++;
	if (g_data->exp->data[i][j] == '=')
		j++;
	while (i < g_data->exp->size)
	{
		if (ft_strncmp(variable, g_data->exp->data[i], j) == 0)
		{
			dynarray_remove(g_data->exp, i);
			duplicate_in_env(variable, j);
			return (1);
		}
		i++;
	}
	return ((0));
}
