/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:21:05 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/21 11:21:20 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

char	*next_arg_in_quote(char *str, int i)
{
	int	j;

	if (str[i] == '\'')
	{
		i++;
		j = i;
		while (str[j] != '\'' && str[j] != '\0')
			j++;
		return (ft_substr(str, i, j - i));
	}
	else
	{
		i++;
		j = i;
		while (str[j] != '"' && str[j] != '\0')
			j++;
		return (ft_substr(str, i, j - i));
	}
}

char	*take_next_arg(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (NULL);
	if (str[i] == '\'' || str[i] == '"')
		return (next_arg_in_quote(str, i));
	else
	{
		j = i;
		while (str[j] != ' ' && str[j] != '\0'
			&& str[j] != '<' && str[j] != '>' && str[j] != '|')
			j++;
		return (ft_substr(str, i, j - i));
	}
}

char	*last_arg_in_quote(char *str, int i, int j)
{
	if (str[i] == '\'')
	{
		i--;
		while (str[i] != '\'' && i != 0)
			i--;
		return (ft_substr(str, i + 1, ft_strlen(str) - i - j));
	}
	else
	{
		i--;
		while (str[i] != '"' && i != 0)
			i--;
		return (ft_substr(str, i + 1, ft_strlen(str) - i - j));
	}
}

char	*take_last_arg(char *str, int i)
{
	int	j;

	j = ft_strlen(str) - i;
	while (str[i] == ' ')
		i--;
	if (i == -1)
		return (NULL);
	if (str[i] == '\'' || str[i] == '"')
		return (last_arg_in_quote(str, i, j));
	else
	{
		while (str[i] != ' ' && i != 0
			&& str[i] != '<' && str[i] != '>' && str[i] != '|')
			i--;
		return (ft_substr(str, i + 1, ft_strlen(str) - i - j));
	}
}
