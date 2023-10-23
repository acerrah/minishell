/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_res.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 04:08:04 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 03:31:58 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

int	check_is_alnum(char c)
{
	if (('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c)
		|| ('0' <= c && '9' >= c) || c == ' ' || c == '_')
		return (1);
	return (0);
}

char	*take_next(char *str)
{
	int		i;
	char	*env_value;
	char	*tmp;

	i = 0;
	if (str[0] == '?')
		return (ft_itoa(g_data->exit_status));
	while (str[i] && check_is_alnum(str[i]) == 1 && str[i] != ' ')
		i++;
	env_value = ft_substr(str, 0, i);
	i = -1;
	while (++i < (int)g_data->env->size)
	{
		if (!(ft_strncmp(g_data->env->data[i],
					env_value, ft_strlen(env_value)))
			&& g_data->env->data[i][ft_strlen(env_value)] == '=')
		{
			tmp = ft_substr(g_data->env->data[i], ft_strlen(env_value) + 1,
					ft_strlen(g_data->env->data[i]) - ft_strlen(env_value));
			free(env_value);
			return (tmp);
		}
	}
	free(env_value);
	return (ft_strdup(""));
}

char	*env_res(char *str, int i)
{
	char	*var;
	char	*tmp1;
	char	*tmp2;

	var = take_next(str);
	if (str[0] == '?')
	{
		tmp1 = ft_substr(str, 1, ft_strlen(str) - 1);
		tmp2 = ft_strjoin(var, tmp1);
		if (tmp1)
			free(tmp1);
		free(var);
		return (tmp2);
	}
	while (str[i] && str[i] != ' ' && str[i] != '$' && check_is_alnum(str[i]))
		i++;
	if (str[i] == '$')
		tmp1 = env_res(&str[i + 1], 0);
	else
		tmp1 = ft_substr(str, i, ft_strlen(str) - i);
	tmp2 = ft_strjoin(var, tmp1);
	free(var);
	free(tmp1);
	return (tmp2);
}
