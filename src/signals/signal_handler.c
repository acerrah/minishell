/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:46:05 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/18 16:14:24 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Ctrl-C is used to send a signal to terminate a running process,
while Ctrl-D is used to indicate the end of input or close stdin in a terminal. */

extern t_data *g_data;

void	ctrl_d(char	*input)
{
	if (input ==  NULL)
	{
		if (g_data->signal_select != HEREDOC)
		{
			printf("exit\n");
			exit(0);
		}
		else
		{
			// set a flag that heredoc is finished
			return ;
		}
	}
}

void sigint_handler(int sig)
{
	(void)sig;
	if (g_data->signal_select == HEREDOC)
	{
		g_data->signal_flag = 0;
		ft_putendl_fd("Deutchland Train> ", 1);

	}
	else if(g_data->signal_select != CHILD)
	{
		g_data->signal_flag = 0;
		ft_putendl_fd("Deutchland Train> ", 1);
	}
	else
		ft_putendl_fd("", 1);

}

void sigquit_handler(int sig) {
    (void)sig;
    if (g_data->signal_select == CHILD) {
        ft_putendl_fd("Quit (core dumped)", 1);
    }
}


int ft_signal_handler(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR) // CTRL-C Handler
	{
        printf("Failed to register the Ctrl-C signal handler.\n");
        return 1;
    }
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR) // CTRL-\ Handler
	{
		ft_putendl_fd("Failed to register the Ctrl-\\ signal handler.", 1);
		return 1;
	}
	return (0);
}
