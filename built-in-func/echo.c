/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:50:11 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/10 22:07:44 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_flag(char *str)
{
	int i;

	i = 0;
	if (!str || str[i] != '-')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int ft_echo(char **av)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	while (av[i] && check_flag(av[i]))
	{
		n_flag = 0;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1] && av[i + 1][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
	return (SUCCESS);
}
