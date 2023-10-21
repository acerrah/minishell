#include "../inc/minishell.h"

t_dynintarray* dynintarray_create() {
    t_dynintarray *d_arr = malloc(sizeof(t_dynintarray));
    d_arr->arr = malloc(INITIAL_CAPACITY * sizeof(int));
    d_arr->size = 0;
    d_arr->capacity = INITIAL_CAPACITY;
    return d_arr;
}

void dynintarray_resize(t_dynintarray *d_arr, int newCapacity) {
    int *newArr = malloc(newCapacity * sizeof(int));
    for (int i = 0; i < d_arr->size; i++) {
        newArr[i] = d_arr->arr[i];
    }
    free(d_arr->arr);
    d_arr->arr = newArr;
    d_arr->capacity = newCapacity;
}

void dynintarray_push(t_dynintarray *d_arr, int value) {
    if (d_arr->size == d_arr->capacity) {
        dynintarray_resize(d_arr, d_arr->capacity * 2);
    }
    d_arr->arr[d_arr->size] = value;
    d_arr->size++;
}

int dynintarray_pull(t_dynintarray *d_arr, int index) {
    if (index < 0 || index >= d_arr->size) {
        printf("Index out of bounds\n");
        return -1;
    }
    return d_arr->arr[index];
}

void dynintarray_set(t_dynintarray *d_arr, int index, int value) {
    if (index < 0 || index >= d_arr->size) {
        printf("Index out of bounds\n");
        return;
    }
    d_arr->arr[index] = value;
}

void dynintarray_destroy(t_dynintarray *d_arr) {
    free(d_arr->arr);
    free(d_arr);
}
