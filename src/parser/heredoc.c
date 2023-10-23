/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:13:40 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 15:41:32 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

int	reopen(int fd)
{
	g_data->signal_select = 0;
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	return (fd);
}

int	ctrlc(char *line, int fd)
{
	free(line);
	close(fd);
	g_data->signal_select = 0;
	return (-2);
}

int	heredoc(char *str, int fd, char *line)
{
	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	g_data->signal_select = HEREDOC;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ctrl_d(line);
			break ;
		}
		if (ft_strcmp(line, str) == 0)
		{
			free(line);
			break ;
		}
		if (g_data->signal_flag == 1)
			return (ctrlc(line, fd));
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (reopen(fd));
}
