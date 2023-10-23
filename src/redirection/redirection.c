/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:21:02 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 04:12:41 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;
/* types are as follows: */
/* -2: no redirection	*/
/*  0: |				 */
/*  1: >				 */
/*  2: >>				*/
/*  3: <				 */
/*  4: <<				*/

void	quotes(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !in_double_quotes)
		*in_single_quotes = !(*in_single_quotes);
	else if (c == '"' && !in_single_quotes)
		*in_double_quotes = !(*in_double_quotes);
}

int	return_error(void)
{
	printf("minishell: syntax error near unexpected token\n");
	g_data->exit_status = 258;
	return (258);
}

int	check(void)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < g_data->redirections->file->size)
	{
		tmp = ft_strtrim(g_data->redirections->file->data[i], " ");
		if (!tmp)
		{
			free(tmp);
			return (return_error());
		}
		free(tmp);
		i++;
	}
	return (0);
}

int	redirections(int i, int j, int in_single_quotes, int in_double_quotes)
{
	char	**str;

	str = g_data->lex->data;
	while (i < (int)g_data->lex->size)
	{
		while (str[i][j])
		{
			if (str[i][j] == '|' && !in_single_quotes && !in_double_quotes)
			{
				dynarray_push(g_data->redirections->file, "|");
				dynintarray_push(g_data->redirections->type, PIPE);
				break ;
			}
			quotes(str[i][j], &in_single_quotes, &in_double_quotes);
			if (ioput(str[i], j, in_single_quotes, in_double_quotes) == 258)
				return (return_error());
			j++;
		}
		j = 0;
		i++;
	}
	return (check());
}
