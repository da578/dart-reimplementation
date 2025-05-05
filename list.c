#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void list_expand(List *list)
{
    list->capacity *= 2;
    list->data = (void **)realloc(list->data, list->capacity * sizeof(void *));
    assert(list->data != NULL);
}

void list_add(List *list, void *item)
{
    if (list->size == list->capacity)
        list_expand(list);
    list->data[list->size++] = item;
}

void *list_get(List *list, size_t index)
{
    assert(index < list->size);
    return list->data[index];
}

void list_destroy(List *list)
{
    free(list->data);
    free(list);
}

void list_remove(List *list, size_t index)
{
    assert(index < list->size);
    for (size_t i = index; i < list->size - 1; i++)
        list->data[i] = list->data[i + 1];
    list->size--;
}

List *create_list(size_t initial_capacity, bool growable)
{
    List *list = (List *)malloc(sizeof(List));
    assert(list != NULL);

    list->capacity = initial_capacity;
    list->size = 0;
    list->is_growable = growable;
    list->is_unmodifiable = false;
    list->data = (void **)malloc(initial_capacity * sizeof(void *));
    assert(list->data != NULL);

    list->add = list_add;
    list->get = list_get;
    list->destroy = list_destroy;
    list->remove = list_remove;
    list->expand = list_expand;

    return list;
}

List *list_empty(size_t capacity, bool growable)
{
    return create_list(capacity, growable);
}

List *list_filled(size_t capacity, void *element, bool growable)
{
    List *list = create_list(capacity, growable);
    for (int i = 0; i < capacity; i++)
    {
        list->data[i] = element;
        list->size++;
    }
    return list;
}

List *list_from(void **elements, size_t capacity, bool growable)
{
    List *list = create_list(capacity, growable);
    for (int i = 0; i < capacity; i++)
    {
        list->data[i] = elements[i];
        list->size++;
    }
    return list;
}

List *list_generate(size_t capacity, void *(*generator)(int), bool growable)
{
    List *list = create_list(capacity, growable);
    for (int i = 0; i < capacity; i++)
    {
        list->data[i] = generator(i);
        list->size++;
    }
    return list;
}

List *list_unmodifiable(void **elements, int capacity)
{
    List *list = create_list(capacity, false);
    list->is_unmodifiable = true;
    for (int i = 0; i < capacity; i++)
    {
        list->data[i] = elements[i];
        list->size++;
    }
    return list;
}

const ListClass ListFactory = {
    .empty = list_empty,
    .filled = list_filled,
    .from = list_from,
    .generate = list_generate,
    .unmodifiable = list_unmodifiable,
};