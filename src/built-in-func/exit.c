/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:27:28 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/22 10:30:25 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*g_data;

static int	digit_control(char *str)
{
	int	i;

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

void	ft_exit(char **command, int size)
{
	int	i;
	int	exit_code;

	i = 1;
	if (command[i] == 0)
	{
		printf("exit\n");
		exit(0);
	}
	else if (size > 2)
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
