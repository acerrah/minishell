/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 03:57:25 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 01:13:36 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	clear_lex_cmd(void)
{
	int	i;

	i = 0;
	if (g_data->lex)
	{
		dynarray_destroy(g_data->lex);
		g_data->lex = dynarray_create();
	}
	if (g_data->cmd)
	{
		while (i < g_data->line && g_data->cmd[i])
			dynarray_destroy(g_data->cmd[i++]);
		free(g_data->cmd);
	}
}

void	clear_rd_fd(void)
{
	if (g_data->redirections->file)
	{
		dynintarray_destroy(g_data->redirections->type);
		g_data->redirections->type = dynintarray_create();
		dynarray_destroy(g_data->redirections->file);
		g_data->redirections->file = dynarray_create();
	}
	if (g_data->fd)
	{
		dynintarray_destroy(g_data->fd[0]);
		dynintarray_destroy(g_data->fd[1]);
		free(g_data->fd);
		g_data->fd = malloc(sizeof(t_dynintarray *) * 2);
		g_data->fd[IN] = dynintarray_create();
		g_data->fd[OUT] = dynintarray_create();
	}
}

void	loop_clear(char	*input_str, char *trim_input_str)
{
	if (input_str)
		free(input_str);
	if (trim_input_str)
		free(trim_input_str);
	g_data->signal_exit = 0;
	clear_lex_cmd();
	clear_rd_fd();
}
