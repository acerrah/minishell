/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:20:57 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/21 11:21:35 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	delete_last_arg(char *str, int i)
{
	while (str[i] == ' ')
		i--;
	if (i == -1)
		return ;
	if (str[i] == '\'')
	{
		str[i] = ' ';
		while (str[--i] != '\'' && i != -1)
			str[i] = ' ';
		str[i] = ' ';
	}
	else if (str[i] == '"')
	{
		str[i] = ' ';
		while (str[--i] != '"' && i != -1)
			str[i] = ' ';
		str[i] = ' ';
	}
	else
	{
		while (str[i] != ' ' && i != -1 && str[i] != '<'
			&& str[i] != '>' && str[i] != '|')
			str[i--] = ' ';
	}
}

void	delete_next_arg(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return ;
	if (str[i] == '\'')
	{
		str[i] = ' ';
		while (str[++i] != '\'' && str[i] != '\0')
			str[i] = ' ';
		str[i] = ' ';
	}
	else if (str[i] == '"')
	{
		str[i] = ' ';
		while (str[i++] != '"' && str[i] != '\0')
			str[i] = ' ';
		str[i] = ' ';
	}
	else
	{
		while (str[i] != ' ' && str[i] != '\0'
			&& str[i] != '<' && str[i] != '>' && str[i] != '|')
			str[i++] = ' ';
	}
}
