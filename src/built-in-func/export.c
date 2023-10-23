/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 08:23:31 by ioztimur          #+#    #+#             */
/*   Updated: 2023/10/23 01:53:24 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	push_to_exp(char *cmd, int j)
{
	char	*tmp;

	if (cmd[ft_strlen(cmd) - 1] == '=')
	{
		tmp = ft_strjoin(cmd, "\"\"");
		dynarray_push_to(g_data->exp, tmp, j);
		free(tmp);
	}
	else
	{
		tmp = format_exp(cmd);
		dynarray_push_to(g_data->exp, tmp, j);
		free(tmp);
	}
}

void	push_in_order(char **cmd, int i)
{
	size_t	j;
	char	*declare;

	j = 0;
	while (g_data->exp->size > j)
	{
		if (ascii_bigger(cmd[i], g_data->exp->data[j]) == 0)
		{
			declare = ft_strdup(cmd[i]);
			push_to_exp(declare, j);
			free(declare);
			break ;
		}
		j++;
		if (g_data->exp->size == j)
		{
			declare = ft_strdup(cmd[i]);
			push_to_exp(declare, j);
			free(declare);
			break ;
		}
	}
}

void	init_export(char **cmd, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		single_to_double_quote(cmd[i]);
		if (cmd[i][0] == '=' || ft_isdigit(cmd[i][0]) || eq_check(cmd[i]))
		{
			printf("bash: export: '%s': not a valid identifier\n", cmd[i]);
			i++;
			continue ;
		}
		else if (duplicate_check(cmd[i]) == 1)
			push_in_order(cmd, i);
		else if (cmd[i][0] != '=')
			push_in_order(cmd, i);
		if (int_strchr(cmd[i], '='))
			dynarray_push(g_data->env, cmd[i]);
		i++;
	}
}

void	ft_export(char **cmd, int size)
{
	size_t	i;

	i = 0;
	if (cmd[1] == 0)
	{
		while (i < g_data->exp->size)
		{
			printf("declare -x %s\n", g_data->exp->data[i]);
			i++;
		}
	}
	else
		init_export(cmd, size);
}
