/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:17:54 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 01:39:59 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	execute_all(void)
{
	if (g_data->pipe_count == 0)
		init_one_command_execution();
	else if (g_data->pipe_count > 0)
		init_multi_command_execution();
}

int	check_str(char *input_str)
{
	if (input_str == NULL)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (input_str[0] == '\0')
	{
		free(input_str);
		return (1);
	}
	return (0);
}

static int	check_missing_quotes(char *rl)
{
	int	i;
	int	quote;

	quote = 0;
	i = -1;
	while (rl[++i])
	{
		if (quote == 0 && (rl[i] == 34 || rl[i] == 39))
			quote = rl[i];
		else if (quote == rl[i])
			quote = 0;
	}
	if (!!quote)
	{
		printf("minishell: syntax error: missing quote\n");
		free(rl);
	}
	return (!!quote);
}

void	loop(char *input_str, char *trim_input_str)
{
	while (TRUE)
	{
		input_str = readline("minishell-0.1$ ");
		if (check_str(input_str) != 0 || check_missing_quotes(input_str) != 0)
			continue ;
		trim_input_str = ft_strtrim(input_str, " ");
		if (trim_input_str == NULL)
		{
			loop_clear(input_str, trim_input_str);
			continue ;
		}
		add_history(input_str);
		if (check_and_clear(lexer(input_str, FALSE, FALSE, 0),
				input_str, trim_input_str) != 0)
			continue ;
		if (check_and_clear(redirections(0, 0, FALSE, FALSE),
				input_str, trim_input_str) != 0)
			continue ;
		if (check_and_clear(parser(0, 0, 0, 0), input_str,
				trim_input_str) == 1)
			continue ;
		execute_all();
		loop_clear(input_str, trim_input_str);
	}
}
