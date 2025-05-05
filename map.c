#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

Entry *find_entry(Entry **bucket, const char *key)
{
    Entry *entry = *bucket;
    while (entry && entry->key)
    {
        if (strcmp(entry->key, key) == 0)
            return entry;
        entry = entry->next;
    }
    return NULL;
}

void free_bucket(Entry *entry)
{
    while (entry)
    {
        Entry *next = entry->next;
        free(entry);
        entry = next;
    }
}

void map_put(Map *map, const char *key, void *value)
{
    unsigned long index = hash(key) % map->size;
    Entry *entry = find_entry(&map->buckets[index], key);

    if (entry)
    {
        entry->value = value;
        return;
    }

    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    assert(new_entry != NULL);
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
}

void *map_get(Map *map, const char *key) {
    unsigned long index = hash(key) % map->size;
    Entry* entry = find_entry(&map->buckets[index], key);
    return entry ? entry->value : NULL;
}

void map_remove(Map *map, const char *key)
{
    unsigned long index = hash(key) % map->size;
    Entry *entry = map->buckets[index];
    Entry *prev = NULL;

    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            if (prev)
                prev->next = entry->next;
            else
                map->buckets[index] = entry->next;
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void map_destroy(Map *map)
{
    for (size_t i = 0; i < map->size; i++)
        free_bucket(map->buckets[i]);
    free(map->buckets);
    free(map);
}

Map *map_empty(size_t capacity) {
    Map *map = (Map*)malloc(sizeof(Map));
    assert(map != NULL);
    map->size = capacity;
    map->buckets = (Entry**) calloc(capacity, sizeof(Entry*));
    assert(map->buckets != NULL);

    map->put = map_put;
    map->get = map_get;
    map->remove = map_remove;
    map->destroy = map_destroy;

    return map;
}

const MapClass MapFactory = {
    .empty = map_empty
};