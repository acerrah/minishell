/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:48:55 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 11:55:27 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dynarray_push(t_dynarray *arr, char *str)
{
	if (arr->size == arr->capacity)
		if (dynarray_resize(arr, arr->capacity * 2) != 0)
			return (-1);
	if (str)
		arr->data[arr->size++] = ft_strdup(str);
	else
		arr->data[arr->size++] = NULL;
	return (0);
}

int	dynarray_push_to(t_dynarray *arr, char *str, size_t index)
{
	size_t	i;

	i = arr->size;
	if (index > arr->size)
		return (-1);
	if (arr->size == arr->capacity)
		if (dynarray_resize(arr, arr->capacity * 2) != 0)
			return (-1);
	while (i > index)
	{
		arr->data[i] = arr->data[i - 1];
		i--;
	}
	if (str)
		arr->data[index] = ft_strdup(str);
	else
		arr->data[index] = NULL;
	arr->size++;
	return (0);
}

void	dynintarray_push(t_dynintarray *d_arr, int value)
{
	if (d_arr->size == d_arr->capacity)
		dynintarray_resize(d_arr, d_arr->capacity * 2);
	d_arr->arr[d_arr->size] = value;
	d_arr->size++;
}

void	dynintarray_set(t_dynintarray *d_arr, int index, int value)
{
	if (index < 0 || index >= d_arr->size)
	{
		printf("Index out of bounds\n");
		return ;
	}
	d_arr->arr[index] = value;
}
