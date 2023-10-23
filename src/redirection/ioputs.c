/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:21:01 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 05:17:43 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

int	output(char *str, int j)
{
	char	*file;

	if (str[j + 1] == '>')
	{
		dynintarray_push(g_data->redirections->type, REDIR_OUT_APPEND);
		file = take_next_arg(&str[j + 2]);
		dynarray_push(g_data->redirections->file, file);
		delete_next_arg(str, j + 2);
		str[j] = ' ';
		str[j + 1] = ' ';
	}
	else
	{
		str[j] = ' ';
		while (str[j] == ' ')
			j++;
		if (str[j] == '<' || str[j] == '>')
			return (258);
		dynintarray_push(g_data->redirections->type, REDIR_OUT);
		file = take_next_arg(&str[j]);
		dynarray_push(g_data->redirections->file, file);
		delete_next_arg(str, j);
	}
	free(file);
	return (0);
}

int	input(char *str, int j)
{
	char	*file;

	if (str[j + 1] == '<')
	{
		dynintarray_push(g_data->redirections->type, REDIR_HEREDOC);
		file = take_next_arg(&str[j + 2]);
		dynarray_push(g_data->redirections->file, file);
		delete_next_arg(str, j + 2);
		str[j] = ' ';
		str[j + 1] = ' ';
	}
	else
	{
		str[j] = ' ';
		while (str[j] == ' ')
			j++;
		if (str[j] == '>' || str[j] == '<')
			return (258);
		dynintarray_push(g_data->redirections->type, REDIR_IN);
		file = take_next_arg(&str[j]);
		dynarray_push(g_data->redirections->file, file);
		delete_next_arg(str, j);
	}
	free(file);
	return (0);
}

int	ioput(char *str, int j, int in_single_quotes, int in_double_quotes)
{
	if (str[j] == '>' && !in_single_quotes && !in_double_quotes)
	{
		if (output(str, j) == 258)
			return (258);
	}
	else if (str[j] == '<' && !in_single_quotes && !in_double_quotes)
	{
		if (input(str, j) == 258)
			return (258);
	}
	return (0);
}
