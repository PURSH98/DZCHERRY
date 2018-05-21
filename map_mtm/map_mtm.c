#include <malloc.h>
#include <stdio.h>
#include "map_mtm.h"

typedef struct Node *Node;

struct Node {
    MapKeyElement key;
    MapDataElement data;
    Node *next;
};

struct Map_t {
    int size;
    MapKeyElement first;
    MapKeyElement current;
    copyMapDataElements copyData;
    copyMapKeyElements copyKey;
    freeMapDataElements freeData;
    freeMapKeyElements freeKey;
    compareMapKeyElements compareKey;
};

Map mapCreate(copyMapDataElements copyDataElement, copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements) {
    if ((copyDataElement && copyKeyElement && freeDataElement &&
         freeKeyElement && compareKeyElements) == NULL) {
        return NULL;
    }
    Map map = malloc(sizeof(*map));
    if (map == NULL) {
        return NULL;
    }
    map->size = 0;
    map->first = NULL;
    map->current = NULL;
    map->copyData = copyDataElement;
    map->copyKey = copyKeyElement;
    map->freeData = freeDataElement;
    map->freeKey = freeKeyElement;
    map->compareKey = compareKeyElements;
    return map;
}

void mapDestroy(Map map) {
    if (map == NULL) {
        return;
    }
    MapResult result = mapClear(map);
    if (result == MAP_NULL_ARGUMENT) {
        return;
    }
    free(map);
}

Map mapCopy(Map map) {       //???
    if (map == NULL) {
        return NULL;
    }
    Map map_copy = malloc(sizeof(*map_copy));
    if (map_copy == NULL) {
        return NULL;
    }
    map_copy->size = map->size;
    map_copy->copyData = map->copyData;
    map_copy->copyKey = map->copyKey;
    map_copy->freeData = map->freeData;
    map_copy->freeKey = map->freeKey;
    map_copy->compareKey = map->compareKey;
}

int mapGetSize(Map map) {
    if (map == NULL) {
        return -1;
    }
    return map->size;
}

bool mapContains(Map map, MapKeyElement element) {       //???
    if ((map && element) == NULL) {
        return false;
    }
}