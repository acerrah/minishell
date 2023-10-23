/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_intarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:48:44 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/22 14:51:35 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_dynintarray	*dynintarray_create(void)
{
	t_dynintarray	*d_arr;

	d_arr = malloc(sizeof(t_dynintarray));
	d_arr->arr = malloc(INITIAL_CAPACITY * sizeof(int));
	d_arr->size = 0;
	d_arr->capacity = INITIAL_CAPACITY;
	return (d_arr);
}

void	dynintarray_resize(t_dynintarray *d_arr, int newCapacity)
{
	int	*new_arr;
	int	i;

	i = 0;
	new_arr = malloc(newCapacity * sizeof(int));
	while (i < d_arr->size)
	{
		new_arr[i] = d_arr->arr[i];
		i++;
	}
	free(d_arr->arr);
	d_arr->arr = new_arr;
	d_arr->capacity = newCapacity;
}

int	dynintarray_pull(t_dynintarray *d_arr, int index)
{
	if (index < 0 || index >= d_arr->size)
	{
		printf("Index out of bounds\n");
		return (-1);
	}
	return (d_arr->arr[index]);
}

void	dynintarray_destroy(t_dynintarray *d_arr)
{
	free(d_arr->arr);
	free(d_arr);
}
