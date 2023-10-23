/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:37:41 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/23 00:34:11 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*  Dynamic arrays for strings.			                                      */
/*  The dynamic array is implemented as a struct with the following fields:   */
/*  data - pointer to the array of strings			                          */
/*  size - number of strings in the array			                          */
/*  capacity - maximum number of strings that can be stored in the array	  */
/*  The dynamic array is created with the dynarray_create function.           */
/*  The dynarray_push function adds a string to the end of the array          */
/*  The dynarray_destroy function frees the memory allocated for the array.   */
/*  The dynarray_resize function changes the capacity of the array but        */
/*  it is not used manually, it is called automatically when the array        */
/*  is full and a new string is added to it.			                      */
t_dynarray	*dynarray_create(void)
{
	t_dynarray	*arr ;

	arr = malloc(sizeof(t_dynarray));
	if (!arr)
		return (NULL);
	arr->data = ft_calloc(INITIAL_CAPACITY, sizeof(char *));
	if (!arr->data)
	{
		free(arr);
		return (NULL);
	}
	arr->size = 0;
	arr->capacity = INITIAL_CAPACITY;
	return (arr);
}

void	dynarray_destroy(t_dynarray *arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (i < arr->size && arr->data[i])
	{
		free(arr->data[i]);
		i++;
	}
	free(arr->data);
	free(arr);
}

int	dynarray_resize(t_dynarray *arr, size_t new_capacity)
{
	char	**new_data;
	size_t	i;

	i = 0;
	new_data = ft_calloc(new_capacity, sizeof(char *));
	if (!new_data)
		return (-1);
	while (i < arr->size)
	{
		new_data[i] = arr->data[i];
		i++;
	}
	free(arr->data);
	arr->data = new_data;
	arr->capacity = new_capacity;
	return (0);
}

int	dynarray_remove(t_dynarray *arr, size_t index)
{
	size_t	i;

	i = index;
	if (index >= arr->size)
		return (-1);
	free(arr->data[index]);
	while (i < arr->size - 1)
	{
		arr->data[i] = arr->data[i + 1];
		i++;
	}
	arr->size--;
	if (arr->size * 4 <= arr->capacity && arr->capacity > INITIAL_CAPACITY)
		if (dynarray_resize(arr, arr->capacity / 2) != 0)
			return (-1);
	return (0);
}
