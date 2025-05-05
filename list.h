#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct List List;

List *create_list(size_t initial_capacity, bool growable);

typedef List *(*ListEmptyFunc)(size_t, bool);
typedef List *(*ListFilledFunc)(size_t, void *, bool);
typedef List *(*ListFromFunc)(void **, size_t, bool);
typedef List *(*ListGenerateFunc)(size_t, void *(*)(size_t), bool);
typedef List *(*ListUnmodifiableFunc)(void **, size_t);

typedef void (*ListAddFunc)(List *, void *);
typedef void *(*ListGetFunc)(List *, size_t);
typedef void (*ListDestroyFunc)(List *);
typedef void (*ListRemoveFunc)(List *, size_t);
typedef void (*ListExpandFunc)(List *);

struct List
{
    size_t capacity;
    size_t size;
    void **data;
    bool is_growable;
    bool is_unmodifiable;

    ListAddFunc add;
    ListGetFunc get;
    ListDestroyFunc destroy;
    ListRemoveFunc remove;
    ListExpandFunc expand;
};

typedef struct
{
    ListEmptyFunc empty;
    ListFilledFunc filled;
    ListFromFunc from;
    ListGenerateFunc generate;
    ListUnmodifiableFunc unmodifiable;
} ListClass;

extern const ListClass ListFactory;

#endif