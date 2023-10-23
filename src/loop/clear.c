/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:43:45 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 03:11:57 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	clear_rd(void)
{
	dynintarray_destroy(g_data->redirections->type);
	g_data->redirections->type = dynintarray_create();
	dynarray_destroy(g_data->redirections->file);
	g_data->redirections->file = dynarray_create();
}

int	clear_ctrlc(int check, char	*input_str, char *trim_input_str)
{
	if (check == -2)
	{
		if (input_str)
			free(input_str);
		if (trim_input_str)
			free(trim_input_str);
		if (g_data->lex)
		{
			dynarray_destroy(g_data->lex);
			g_data->lex = dynarray_create();
		}
		clear_rd_fd();
		g_data->signal_flag = 0;
		return (1);
	}
	return (0);
}

int	check_and_clear(int check, char	*input_str, char *trim_input_str)
{
	if (check == 258)
	{
		if (input_str)
			free(input_str);
		if (trim_input_str)
			free(trim_input_str);
		if (g_data->lex)
		{
			dynarray_destroy(g_data->lex);
			g_data->lex = dynarray_create();
		}
		if (g_data->redirections->type)
			clear_rd();
		return (258);
	}
	if (clear_ctrlc(check, input_str, trim_input_str) == 1)
		return (1);
	return (0);
}
