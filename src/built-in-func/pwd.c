/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioztimur <ioztimur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:50:05 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/22 00:13:04 by ioztimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX))
	{
		ft_putendl_fd(buff, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
