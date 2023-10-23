/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:31:05 by ioztimur          #+#    #+#             */
/*   Updated: 2023/10/23 01:31:42 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	single_to_double_quote(char *command)
{
	if (command[0] == '\'' && command[ft_strlen(command) - 1] == '\'')
	{
		command[0] = '\"';
		command[ft_strlen(command) - 1] = '\"';
		return ;
	}
}

char	*add_quotes(char *str)
{
	int		i;
	int		len;
	char	*new_str;
	int		j;

	i = 1;
	j = 0;
	len = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * len + 3);
	new_str[0] = '\"';
	while (str[j])
	{
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[len + 1] = '\"';
	new_str[len + 2] = '\0';
	return (new_str);
}

int	eq_check(char *command)
{
	char	*variable;
	int		i;
	char	**str;

	variable = NULL;
	i = 0;
	if (ft_strchr(command, '=') != 0)
	{
		str = ft_split(command, '=');
		variable = ft_strdup(str[0]);
		while (str[i])
			free(str[i++]);
		free(str);
		i = int_strchr(variable, 32);
		free(variable);
		return (i);
	}
	else
		return (0);
}

void	free_exp_data(char *tmp, char *variable, char *value, char **str)
{
	int	i;

	i = 0;
	free(tmp);
	free(variable);
	free(value);
	while (str[i])
		free(str[i++]);
	free(str);
}

char	*format_exp(char *command)
{
	char	*variable;
	char	*value;
	char	**str;
	char	*ret;
	char	*tmp;

	str = ft_split(command, '=');
	variable = ft_strdup(str[0]);
	if (str[1])
	{
		tmp = ft_strdup(str[1]);
		if (str[1][0] != '\"' && str[1][ft_strlen(str[1]) - 1] != '\"')
			value = add_quotes(tmp);
		else
			value = ft_strdup(tmp);
		free(tmp);
	}
	else
		value = ft_strdup("");
	tmp = ft_strjoin(variable, "=");
	ret = ft_strjoin(tmp, value);
	return (ret);
}
