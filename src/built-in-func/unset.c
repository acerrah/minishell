/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:31:54 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/13 12:52:28 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

int ft_unset(char **command)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (command[i] == 0)
		printf("unset: not enough arguments\n");
	while (command[i])
	{
		while (g_data->env->data[j])
		{
			if (ft_strncmp(command[i], g_data->env->data[j], ft_strlen(command[i]) == 0))
				dynarray_remove(g_data->env, j);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
