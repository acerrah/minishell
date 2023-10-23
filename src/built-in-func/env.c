/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:31:17 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/22 22:47:32 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

static void	write_environment(void)
{
	size_t	i;

	i = 0;
	while (i < g_data->env->size)
		printf("%s\n", g_data->env->data[i++]);
}

void	ft_env(char **command)
{
	int	i;

	i = 1;
	if (command[i] == 0)
		write_environment();
}
