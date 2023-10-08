/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:24:41 by acerrah           #+#    #+#             */
/*   Updated: 2022/10/18 11:24:42 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *nnew)
{
	if (!nnew || !lst)
		return ;
	if (!*lst)
	{
		(*lst) = nnew;
	}
	else
	{
		(ft_lstlast(*lst))->next = nnew;
		(ft_lstlast(*lst))->next = NULL;
	}
}
