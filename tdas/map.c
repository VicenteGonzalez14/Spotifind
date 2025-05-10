
#include <stdlib.h>
#include <string.h>
#include "map.h"

#define HASH_SIZE 100

typedef struct Pair {
    void *key;
    void *value;
    struct Pair *next;
} Pair;

struct Map {
    Pair **buckets;
    Pair *current;
    int (*is_equal)(void *, void *);
};

unsigned int hash_str(const char *key) {
    unsigned int hash = 0;
    while (*key) hash = hash * 31 + *key++;
    return hash;
}

Map *map_create(int (*is_equal)(void *, void *)) {
    Map *map = malloc(sizeof(Map));
    map->buckets = calloc(HASH_SIZE, sizeof(Pair *));
    map->is_equal = is_equal;
    map->current = NULL;
    return map;
}

void map_insert(Map *map, void *key, void *value) {
    unsigned int hash = hash_str((char *)key) % HASH_SIZE;
    Pair *current = map->buckets[hash];
    while (current) {
        if (map->is_equal(current->key, key)) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    Pair *new_pair = malloc(sizeof(Pair));
    new_pair->key = key;
    new_pair->value = value;
    new_pair->next = map->buckets[hash];
    map->buckets[hash] = new_pair;
}

MapPair *map_search(Map *map, void *key) {
    unsigned int hash = hash_str((char *)key) % HASH_SIZE;
    Pair *current = map->buckets[hash];
    static MapPair pair;
    
    while (current) {
        if (map->is_equal(current->key, key)) {
            pair.key = current->key;
            pair.value = current->value;
            return &pair;
        }
        current = current->next;
    }
    return NULL;
}

MapPair *map_first(Map *map) {
    static MapPair pair;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (map->buckets[i] != NULL) {
            map->current = map->buckets[i];
            pair.key = map->current->key;
            pair.value = map->current->value;
            return &pair;
        }
    }
    return NULL;
}

MapPair *map_next(Map *map) {
    static MapPair pair;
    if (map->current && map->current->next) {
        map->current = map->current->next;
        pair.key = map->current->key;
        pair.value = map->current->value;
        return &pair;
    }
    
    unsigned int hash = hash_str((char *)map->current->key) % HASH_SIZE;
    for (int i = hash + 1; i < HASH_SIZE; i++) {
        if (map->buckets[i] != NULL) {
            map->current = map->buckets[i];
            pair.key = map->current->key;
            pair.value = map->current->value;
            return &pair;
        }
    }
    return NULL;
}

void map_clean(Map *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Pair *current = map->buckets[i];
        while (current) {
            Pair *next = current->next;
            free(current);
            current = next;
        }
    }
    free(map->buckets);
    free(map);
}
