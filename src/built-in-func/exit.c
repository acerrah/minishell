/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:27:28 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/16 21:24:58 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern t_data *g_data;

int	len_2d(char **command)
{
	int i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

static int digit_control(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void ft_exit(char **command)
{
	int i;
	int exit_code;

	i = 1;
	if (command[i] == 0)
		exit(0);
	else if (len_2d(command) > 2)
	{
		printf("exit: too many arguments\n");
		exit (1);
	}
	else
	{
		if (digit_control(command[i]) == 0)
			printf("bash: exit: %s: numeric argument required\n", command[i]);
		exit_code = ft_atoi(command[i]);
		exit(exit_code);
	}
}
