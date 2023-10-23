/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 06:00:04 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 02:39:58 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	take_pipe_count(void)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	while (i < g_data->lex->size)
	{
		tmp = ft_strtrim(g_data->lex->data[i], " ");
		if (tmp[0] == '|')
			j++;
		i++;
		free(tmp);
	}
	g_data->pipe_count = j;
}

char	*delete_character(char *str, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*rtn;

	tmp = ft_substr(str, 0, i);
	tmp2 = ft_substr(str, i + 1, ft_strlen(str) - 1);
	rtn = ft_strjoin(tmp, tmp2);
	if (tmp)
		free(tmp);
	if (tmp2)
		free(tmp2);
	return (rtn);
}

void	modify_dynarray(int k, int i, int j)
{
	char	*tmp;

	tmp = delete_character(g_data->cmd[k]->data[i], j);
	dynarray_remove(g_data->cmd[k], i);
	dynarray_push_to(g_data->cmd[k], tmp, i);
	free (tmp);
}

void	modify_parser(size_t i, int *k, int *j, int single_quote)
{
	int		double_quote;

	double_quote = 0;
	while ((i) < g_data->cmd[(*k)]->size)
	{
		while (g_data->cmd[(*k)]->data[(i)][(*j)])
		{
			if (g_data->cmd[(*k)]->data[(i)][(*j)] == '\'' && !double_quote)
			{
				single_quote = !single_quote;
				modify_dynarray((*k), (i), (*j));
				continue ;
			}
			if (g_data->cmd[(*k)]->data[(i)][(*j)] == '\"' && !single_quote)
			{
				double_quote = !double_quote;
				modify_dynarray((*k), (i), (*j));
				continue ;
			}
			(*j)++;
		}
		(*j) = 0;
		(i)++;
	}
}

int	parser(size_t i, int k, int m, int j)
{
	int		single_quote;

	single_quote = 0;
	take_pipe_count();
	if (open_fd() == -2)
		return (-2);
	malloc_cmd();
	trimming(&i, &k, &m);
	k = 0;
	while (k < g_data->line)
	{
		modify_parser(0, &k, &j, single_quote);
		k++;
	}
	return (0);
}
