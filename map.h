#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Map Map;
typedef struct Entry Entry;

typedef void (*MapPutFunc)(Map *, const char *, void *);
typedef void *(*MapGetFunc)(Map *, const char *);
typedef void (*MapRemoveFunc)(Map *, const char *);
typedef void (*MapDestroyFunc)(Map *);

struct Entry
{
    const char *key;
    void *value;
    Entry *next;
};

struct Map
{
    size_t size;
    Entry **buckets;

    MapPutFunc put;
    MapGetFunc get;
    MapRemoveFunc remove;
    MapDestroyFunc destroy;
};

typedef Map *(*MapEmptyFunc)(size_t capacity);

typedef struct
{
    MapEmptyFunc empty;
} MapClass;

extern const MapClass MapFactory;

#endif