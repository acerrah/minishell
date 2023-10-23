/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:40:38 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 03:02:15 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

/* Lexer divides the input string into tokens and stores them in a dynamic */
/* array. The tokens are separated by pipes with attention to quotes.      */
/* The tokens are stored in the dynamic array in the following order:      */
/* <token, pipe, token, pipe, token, pipe, token, NULL>                    */

int	pipe_syntax_error(int last_pipe, int i, char *input_str)
{
	char	*token;
	char	*trim_token;

	token = ft_substr(input_str, last_pipe, i - last_pipe);
	trim_token = ft_strtrim(token, " ");
	if (ft_strcmp(token, "") == 0)
	{
		printf("minishell: synta error near unexpected token `|'\n");
		free(token);
		free(trim_token);
		return (258);
	}
	free(token);
	free(trim_token);
	return (0);
}

void	push_tokens(char *input_str, int i, int j)
{
	char	*token;

	token = ft_substr(input_str, i, j);
	dynarray_push(g_data->lex, token);
	free(token);
}

int	lexer(char *input_str, int in_single_quotes,
	int in_double_quotes, int last_pipe)
{
	int		i;

	i = 0;
	while (input_str[i])
	{
		if (input_str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (input_str[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (input_str[i] == '|' && !in_single_quotes && !in_double_quotes)
		{
			if (pipe_syntax_error(last_pipe, i, input_str) == 258)
				return (258);
			push_tokens(input_str, last_pipe, i - last_pipe);
			push_tokens(input_str, i, 1);
			last_pipe = i + 1;
		}
		i++;
	}
	if (input_str[i] == '\0')
		push_tokens(input_str, last_pipe, i - last_pipe);
	return (0);
}
