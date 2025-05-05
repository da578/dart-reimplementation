#ifndef SET_H
#define SET_H

#include "map.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct Set Set;

typedef void (*SetAddFunc)(Set *, const char*);
typedef bool (*SetContainsFunc)(Set*, const char*);
typedef void (*SetRemoveFunc)(Set*, const char*);
typedef void (*SetDestroyFunc)(Set *);

struct Set {
    Map *map;

    SetAddFunc add;
    SetContainsFunc contains;
    SetRemoveFunc remove;
    SetDestroyFunc destroy;
};

typedef Set* (*SetEmptyFunc)(size_t capacity);

typedef struct {
    SetEmptyFunc empty;
} SetClass;

extern const SetClass SetFactory;

#endif