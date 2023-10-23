/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 06:00:09 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 03:29:40 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	malloc_cmd(void)
{
	int	i;

	i = g_data->pipe_count;
	g_data->line = i + 1;
	g_data->cmd = malloc(sizeof(t_dynarray *) * (i + 1));
	g_data->cmd_size = i + 1;
}

void	spliting_lex(size_t i, int j, int *k)
{
	int	in_single_quotes;
	int	in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	while (g_data->lex->data[i][j])
	{
		if (g_data->lex->data[i][j] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (g_data->lex->data[i][j] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (g_data->lex->data[i][j] == ' '
			&& !in_single_quotes && !in_double_quotes)
		{
			while (g_data->lex->data[i][j + 1] == ' ')
				j++;
			g_data->lex->data[i][j] = '\0';
			j++;
			(*k)++;
			continue ;
		}
		if (g_data->lex->data[i][j + 1] == '\0')
			(*k)++;
		j++;
	}
}

char	*return_env_var(size_t *i)
{
	int		n;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	n = 0;
	tmp = ft_strtrim(g_data->lex->data[(*i)], " ");
	tmp1 = ft_strchr(tmp, '$');
	if (tmp1 && (tmp1 - 1)[0] != '\'')
	{
		tmp2 = env_res(tmp1 + 1, 0);
		while (tmp[n] && tmp[n] != '$')
			n++;
		tmp3 = ft_substr(tmp, 0, n);
		free(tmp);
		tmp = ft_strjoin(tmp3, tmp2);
		free(tmp3);
		free(tmp2);
	}
	return (tmp);
}

void	push_to_cmd(size_t *i, int j, int *k, int m)
{
	int		l;
	char	*tmp;

	l = 0;
	while (j < (*k))
	{
		tmp = return_env_var(i);
		dynarray_push(g_data->cmd[m], tmp);
		free(tmp);
		l += ft_strlen(g_data->lex->data[(*i)]) + 1;
		g_data->lex->data[(*i)] += ft_strlen(g_data->lex->data[(*i)]) + 1;
		j++;
	}
	g_data->lex->data[(*i)] -= l;
}

void	trimming(size_t *i, int *k, int *m)
{
	char	*tmp;

	while ((*i) < g_data->lex->size)
	{
		if (g_data->lex->data[(*i)][0] == '|')
		{
			(*i)++;
			continue ;
		}
		tmp = ft_strtrim(g_data->lex->data[(*i)], " ");
		free(g_data->lex->data[(*i)]);
		g_data->lex->data[(*i)] = ft_strdup(tmp);
		free(tmp);
		spliting_lex((*i), 0, k);
		g_data->cmd[(*m)] = dynarray_create();
		push_to_cmd(i, 0, k, (*m));
		(*k) = 0;
		(*i)++;
		(*m)++;
	}
}
