/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:46:05 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/15 12:58:14 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Ctrl-C is used to send a signal to terminate a running process,
while Ctrl-D is used to indicate the end of input or close stdin in a terminal. */

extern t_data *g_data;


void sigint_handler(int sig)
{
	(void)sig;
	if (g_data->signal_selection == HEREDOC)
	{
		g_data->signal_flag = 0;
		ft_putendl_fd("Deutchland Train> ", 1);

	}
	else if(g_data->signal_selection != CHILD)
	{
		g_data.signal_flag = 0;
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


void ft_signal_handler(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR) // CTRL-C Handler
	{
        printf("Failed to register the Ctrl-C signal handler.\n");
        return 1;
    }
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR) // CTRL-\ Handler
	{
		ft_putendl_fd("Failed to register the Ctrl-\\ signal handler.", 1);
		return  1;
	}
}
