/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 03:59:29 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 19:12:39 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

int	if_pipe(size_t *i, int *j)
{
	if (g_data->redirections->type->arr[(*i)] == PIPE)
	{
		if (g_data->fd[IN]->size < (*j) + 1 && (*j) != 0)
			dynintarray_push(g_data->fd[IN], -2);
		else if (g_data->fd[IN]->size < (*j) + 1 && (*j) == 0)
			dynintarray_push(g_data->fd[IN], STDIN);
		if (g_data->fd[OUT]->size < (*j) + 1)
			dynintarray_push(g_data->fd[OUT], -2);
		dynintarray_push(g_data->fd[IN], -2);
		(*i)++;
		(*j)++;
		return (1);
	}
	return (0);
}

int	if_in(int i, int j)
{
	if (g_data->fd[IN]->size == j + 1)
	{
		if (g_data->fd[IN]->arr[j] > 2)
			close(g_data->fd[IN]->arr[j]);
		dynintarray_pull(g_data->fd[IN], j);
	}
	if (g_data->redirections->type->arr[i] == REDIR_IN)
		dynintarray_push(g_data->fd[IN],
			open(g_data->redirections->file->data[i], O_RDONLY));
	else if (g_data->redirections->type->arr[i] == REDIR_HEREDOC)
	{
		dynintarray_push(g_data->fd[IN],
			heredoc(g_data->redirections->file->data[i], 0, NULL));
		if (g_data->fd[IN]->arr[j] == -2)
			return (-2);
	}
	return (0);
}

void	if_out(int i, int j)
{
	if (g_data->fd[OUT]->size == j + 1)
	{
		if (g_data->fd[OUT]->arr[j] > 2)
			close(g_data->fd[OUT]->arr[j]);
		dynintarray_pull(g_data->fd[OUT], j);
	}
	if (g_data->redirections->type->arr[i] == REDIR_OUT)
		dynintarray_push(g_data->fd[OUT],
			open(g_data->redirections->file->data[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else
		dynintarray_push(g_data->fd[OUT],
			open(g_data->redirections->file->data[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644));
}

int	redir(void)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < g_data->redirections->file->size)
	{
		if (if_pipe(&i, &j) == 1)
			continue ;
		else if (g_data->redirections->type->arr[i] == REDIR_IN
			|| g_data->redirections->type->arr[i] == REDIR_HEREDOC)
		{
			if (if_in(i, j) == -2)
				return (-2);
		}
		else if (g_data->redirections->type->arr[i] == REDIR_OUT
			|| g_data->redirections->type->arr[i] == REDIR_OUT_APPEND)
			if_out(i, j);
		i++;
	}
	if (g_data->fd[OUT]->size < j + 1)
		dynintarray_push(g_data->fd[OUT], STDOUT);
	return (0);
}

int	open_fd(void)
{
	int		j;

	j = 0;
	if (g_data->redirections->file->size == 0)
	{
		dynintarray_push(g_data->fd[IN], STDIN);
		dynintarray_push(g_data->fd[OUT], STDOUT);
	}
	if (redir() == -2)
		return (-2);
	j = g_data->pipe_count;
	if (j > 0 && g_data->fd[OUT]->size != j + 1)
		dynintarray_push(g_data->fd[OUT], STDOUT);
	return (0);
}
