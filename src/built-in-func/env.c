/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:31:17 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/13 09:51:26 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

static void write_environment(void)
{
	int i;

	i = 0;
	while (g_data->env->data[i])
		printf("%s", g_data->env->data[i++]);
}

void ft_env(char **command, int flag)
{
	int i;

	i = 1;
	if (command[i] == 0 && flag == 0)
		write_environment();
}
