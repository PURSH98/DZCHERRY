#include <malloc.h>
#include <stdio.h>
#include "map_mtm.h"

typedef struct Node_t *Node;

struct Node_t {
    MapKeyElement key;
    MapDataElement data;
    Node next;
};

struct Map_t {
    int size;
    Node first;
    Node current;
    copyMapDataElements copyData;
    copyMapKeyElements copyKey;
    freeMapDataElements freeData;
    freeMapKeyElements freeKey;
    compareMapKeyElements compareKey;
};

static Node nodeCopy(Map map, Node node);

static Node nodeCreate(Map map, MapKeyElement key, MapDataElement data);

static Node nodeCreate(Map map, MapKeyElement key, MapDataElement data) {
    if (key == NULL || data == NULL) {
        return NULL;
    }
    Node new_node = malloc(sizeof(*new_node));
    new_node->key = map->copyKey(key);
    new_node->data = map->copyData(data);
    new_node->next = NULL;
    return new_node;
}

static Node nodeCopy(Map map, Node node) {
    if (map == NULL || node == NULL) {
        return NULL;
    }
    Node node_copy = malloc(sizeof(*node_copy));
    if (node_copy == NULL) {
        return NULL;
    }
    node_copy->data = map->copyData(node->data);
    node_copy->key = map->copyKey(node->key);
    node_copy->next = NULL;
    return node_copy;
}

Map mapCreate(copyMapDataElements copyDataElement, copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements) {
    if (copyDataElement == NULL || copyKeyElement == NULL ||
        freeDataElement == NULL || freeKeyElement == NULL ||
        compareKeyElements == NULL) {
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

Map mapCopy(Map map) {
    if (map == NULL) {
        return NULL;
    }
    Map map_copy = mapCreate(map->copyData, map->copyKey,
                             map->freeData, map->freeKey,
                             map->compareKey);
    if (map_copy == NULL) {
        return NULL;
    }
    if (map->size == 0) {
        return map_copy;
    }
    map_copy->first = nodeCopy(map, map->first);
    map_copy->current = map_copy->first;
    map->current = map->first->next;
    while (map->current != NULL) {
        Node temp_node = nodeCopy(map, map->current);
        map_copy->current->next = temp_node;
        map_copy->current = map_copy->current->next;
        map->current = map->current->next;
    }
    return map_copy;
}

int mapGetSize(Map map) {
    if (map == NULL) {
        return -1;
    }
    int map_size = 0;
    map->current = map->first;
    while (map->current != NULL) {
        map_size++;
        map->current = map->current->next;
    }
    map->size = map_size;
    return map->size;
}

bool mapContains(Map map, MapKeyElement element) {
    if (map == NULL || element == NULL) {
        return false;
    }
    map->current = map->first;
    while (map->current != NULL) {
        if (map->compareKey(map->current->key, element) == 0) {
            return true;
        }
        map->current = map->current->next;
    }
    return false;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement) {
    if (map == NULL || keyElement == NULL || dataElement == NULL) {
        return MAP_NULL_ARGUMENT;
    }
    if (map->first == NULL) {
        map->first = nodeCreate(map, keyElement, dataElement);
        map->size++;
        return MAP_SUCCESS;
    }
    if (mapContains(map, keyElement) == true) {
        map->current = map->first;
        while (map->current != NULL) {
            if (map->compareKey(map->current->key, keyElement) == 0) {
                map->freeData(map->current->data);
                map->current->data = map->copyData(dataElement);
                map->size++;
                return MAP_SUCCESS;
            }
            map->current = map->current->next;
        }
    } else {
        if (map->compareKey(map->first->key, keyElement) == 1) {
            Node new_node = nodeCreate(map, keyElement, dataElement);
            new_node->next = map->first;
            map->first = new_node;
            map->size++;
            return MAP_SUCCESS;
        }
        map->current = map->first->next;
        Node previous_node = map->first;
        while (map->current != NULL) {
            if (map->compareKey(map->current->key, keyElement) == 1) {
                previous_node->next = nodeCreate(map, keyElement, dataElement);
                previous_node->next->next = map->current;
                map->size++;
                return MAP_SUCCESS;
            }
            previous_node = previous_node->next;
            map->current = map->current->next;
        }
        previous_node->next = nodeCreate(map, keyElement, dataElement);
        map->size++;
        return MAP_SUCCESS;
    }
    return MAP_SUCCESS;
}

MapDataElement mapGet(Map map, MapKeyElement keyElement) {
    if (map == NULL || keyElement == NULL) {
        return NULL;
    }
    if (map->first == NULL) {
        return NULL;
    }
    Node iterator_init = map->current;
    map->current = map->first;
    while (map->current != NULL) {
        if (map->compareKey(map->current->key, keyElement) == 0) {
            return map->current->data;
        }
        map->current = map->current->next;
    }
    map->current = iterator_init;
    return NULL;
}

MapResult mapRemove(Map map, MapKeyElement keyElement) {
    if (map == NULL || keyElement == NULL) {
        return MAP_NULL_ARGUMENT;
    }
    if (map->size == 0) {
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    map->current = map->first;
    Node previous_node = map->first;
    if (map->compareKey(map->current->key, keyElement) == 0) {
        map->first = map->current->next;
        map->freeData(map->current->data);
        map->freeKey(map->current->key);
        free(map->current);
        return MAP_SUCCESS;
    }
    map->current = map->current->next;
    while (map->current != NULL) {
        if (map->compareKey(map->current->key, keyElement) == 0) {
            previous_node->next = map->current->next;
            map->freeData(map->current->data);
            map->freeKey(map->current->key);
            free(map->current);
            map->size--;
            return MAP_SUCCESS;
        }
        previous_node = map->current;
        map->current = map->current->next;
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}

MapKeyElement mapGetFirst(Map map) {
    if (map == NULL) {
        return NULL;
    }
    if (map->first == NULL) {
        return NULL;
    }
    map->current = map->first;
    return map->first->key;
}

MapKeyElement mapGetNext(Map map) {
    if (map == NULL) {
        return NULL;
    }
    if (map->current == NULL
        || map->current->next == NULL) {
        return NULL;
    }
    map->current = map->current->next;
    return map->current->key;
}

MapResult mapClear(Map map) {
    if (map == NULL) {
        return MAP_NULL_ARGUMENT;
    }
    map->current = map->first;
    while (map->current != NULL) {
        Node previous_node = map->current;
        map->current = map->current->next;
        map->freeData(previous_node->data);
        map->freeKey(previous_node->key);
        free(previous_node);
        map->size--;
    }
    map->first = NULL;
    return MAP_SUCCESS;
}
