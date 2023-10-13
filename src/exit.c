/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:27:28 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/13 13:28:00 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"

extern t_data *g_data;

void ft_exit(char **command)
{
	int i;

	i = 0;
	if (command[i] == 0)
		exit(0);
	else if (command[i + 1] == 0)
		exit(ft_atoi(command[i]));
	else
		printf("exit: too many arguments\n");
}
