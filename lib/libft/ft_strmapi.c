/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:28:35 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 14:51:35 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*rtn;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	rtn = (char *)malloc(len * sizeof(char) + 1);
	if (!rtn)
		return (0);
	while (i < len)
	{
		rtn[i] = (*f)(i, s[i]);
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
