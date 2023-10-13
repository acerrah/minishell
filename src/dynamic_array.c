/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:12:14 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/13 11:27:22 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*  Dynamic arrays for strings.                                               */
/*  The dynamic array is implemented as a struct with the following fields:   */
/*  data - pointer to the array of strings                                    */
/*  size - number of strings in the array                                     */
/*  capacity - maximum number of strings that can be stored in the array      */
/*  The dynamic array is created with the dynarray_create function.           */
/*  The dynarray_push function adds a string to the end of the array.         */
/*  The dynarray_destroy function frees the memory allocated for the array.   */
/*  The dynarray_resize function changes the capacity of the array but        */
/*  it is not used manually, it is called automatically when the array        */
/*  is full and a new string is added to it.                                  */
t_dynarray *dynarray_create() {
    t_dynarray *arr = malloc(sizeof(t_dynarray));
    if (!arr)
        return NULL;
    arr->data = malloc(INITIAL_CAPACITY * sizeof(char *));
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    return arr;
}

void dynarray_destroy(t_dynarray *arr) {
    size_t i;

    i = 0;
    if (!arr)
        return;
    while (i < arr->size)
        free(arr->data[i++]);
    free(arr->data);
    free(arr);
}

int dynarray_resize(t_dynarray *arr, size_t new_capacity) {
    char **new_data = malloc(new_capacity * sizeof(char *));
    if (!new_data)
        return -1;
    ft_memcpy(new_data, arr->data, arr->size * sizeof(char *));
    free(arr->data);
    arr->data = new_data;
    arr->capacity = new_capacity;
    return 0;
}

int dynarray_push(t_dynarray *arr, char *str) {
    if (arr->size == arr->capacity)
        if (dynarray_resize(arr, arr->capacity * 2) != 0)
            return -1;
    if (str)
        arr->data[arr->size++] = ft_strdup(str);
    else
        arr->data[arr->size++] = NULL;
    return 0;
}

int dynarray_remove(t_dynarray *arr, size_t index)
{
    size_t i;

    i = index;
    if (index >= arr->size)
        return -1;
    free(arr->data[index]);
    while (i < arr->size - 1)
    {
        arr->data[i] = arr->data[i + 1];
        i++;
    }
    arr->size--;
    if (arr->size * 4 <= arr->capacity && arr->capacity > INITIAL_CAPACITY)
        if (dynarray_resize(arr, arr->capacity / 2) != 0)
            return -1;
    return 0;
}
