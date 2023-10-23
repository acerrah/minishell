/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_g_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:36:59 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 17:37:24 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

/* handle_g_data function creates the global data structure and  */
/* fills it with the environment variables.                      */
/* ft_strdup_2d function duplicates an array of strings.         */
char	**ft_strdup_2d(char	**str)
{
	int		i;
	char	**rtn;

	i = 0;
	while (str[i])
		i++;
	rtn = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		rtn[i] = ft_strdup(str[i]);
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

void	create_data(void)
{
	g_data->lex = dynarray_create();
	g_data->lex_parsed = dynarray_create();
	g_data->redirections = malloc(sizeof(t_redirections));
	g_data->redirections->type = dynintarray_create();
	g_data->redirections->file = dynarray_create();
	g_data->fd = malloc(sizeof(t_dynintarray *) * 2);
	g_data->fd[IN] = dynintarray_create();
	g_data->fd[OUT] = dynintarray_create();
}

void	handle_g_data(char	**env)
{
	int		i;

	i = 0;
	g_data = malloc(sizeof(t_data));
	g_data->env = dynarray_create();
	while (env[i])
		dynarray_push(g_data->env, env[i++]);
	g_data->exp = dynarray_create();
	copy_exp();
	create_data();
	g_data->signal_select = 0;
	g_data->signal_exit = 0;
	g_data->exit_status = 0;
}
