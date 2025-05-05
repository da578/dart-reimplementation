#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static const char dummy_value = '\0';

void set_add(Set *set, const char*key) {
    set->map->put(set->map, key, (void*) &dummy_value);
}

bool set_contains(Set *set, const char *key) {
    return set->map->get(set->map, key) != NULL;
}

void set_remove(Set *set, const char *key) {
    set->map->remove(set->map, key);
}

void set_destroy(Set *set) {
    set->map->destroy(set->map);
    free(set);
}

Set *set_empty (size_t capacity) {
    Set *set = (Set*)malloc(sizeof(Set));
    assert(set != NULL);
    set->map = MapFactory.empty(capacity);

    set->add = set_add;
    set->contains = set_contains;
    set->remove = set_remove;
    set->destroy = set_destroy;

    return set;
}

const SetClass SetFactory = {
    .empty = set_empty 
};