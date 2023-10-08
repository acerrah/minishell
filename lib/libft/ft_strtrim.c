/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:28:51 by acerrah           #+#    #+#             */
/*   Updated: 2023/02/15 21:21:24 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	trimcheck(char a, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (a == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*rtn;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1) - 1;
	while (trimcheck(s1[i], set))
		i++;
	while (trimcheck(s1[len], set))
		len--;
	rtn = ft_substr(s1, i, len - i + 1);
	if (!rtn)
		return (NULL);
	return (rtn);
}
