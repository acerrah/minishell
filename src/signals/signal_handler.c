/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:46:05 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/23 03:09:42 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

void	ctrl_d(char	*input)
{
	if (!input)
	{
		if (g_data->signal_select != HEREDOC)
		{
			write(1, "\b\b", 2);
			printf("exit\n");
			exit(0);
		}
		else
		{
			g_data->signal_exit = 1;
			return ;
		}
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_data->signal_select == HEREDOC)
	{
		g_data->signal_flag = 1;
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
	}
	else
	{
		g_data->signal_flag = 0;
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
	}
}

void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_data->signal_select == CHILD)
		ft_putendl_fd("Quit (core dumped)", 1);
}

int	ft_signal_handler(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		printf("Failed to register the Ctrl-C signal handler.\n");
		return (1);
	}
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	{
		ft_putendl_fd("Failed to register the Ctrl-\\ signal handler.", 1);
		return (1);
	}
	return (0);
}
