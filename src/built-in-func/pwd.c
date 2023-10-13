/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:50:05 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/13 09:51:18 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_pwd(void)
{
	char buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX))
	{
		ft_putendl_fd(buff, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
