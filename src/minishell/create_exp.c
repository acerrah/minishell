/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 06:06:53 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 07:15:29 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

int	ascii_bigger(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] != '=' && str2[i] != '=')
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '=')
		return (0);
	else
		return (1);
}

void	push_env_to_exp(int (*i), size_t (*j))
{
	char	*declare;

	declare = ft_strdup(g_data->env->data[(*i)]);
	dynarray_push_to(g_data->exp, declare, (*j));
	free(declare);
	(*i)++;
	(*j) = 0;
}

void	copy_exp(void)
{
	int		i;
	size_t	j;
	char	*declare;

	i = 0;
	j = 0;
	declare = ft_strdup(g_data->env->data[i]);
	dynarray_push(g_data->exp, declare);
	free(declare);
	while (g_data->env->size > j)
	{
		if (g_data->env->size == (size_t)i)
			break ;
		if (ascii_bigger(g_data->env->data[i], g_data->exp->data[j]) == 0)
		{
			push_env_to_exp(&i, &j);
			continue ;
		}
		j++;
		if (g_data->exp->size == j)
			push_env_to_exp(&i, &j);
	}
}
