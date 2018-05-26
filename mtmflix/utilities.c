#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mtmflix.h"
#include "map.h"
#include "list.h"

// StringCopy
// StringCompare
// StringFree

//create a private copy of a string. do we need this?
// const char* stringDuplicate(char* str) {
// 	char* copy = malloc(strlen(str) + 1);
// 	return copy ? strcpy(copy, str) : NULL;
// }

bool stringCheck (char* string) {
	int length = strlen(string);
	for (int i = 0; i < length; i++) {
		if (!((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z') || (string[i] >= '0' && string[i] <= '9'))) {
			return false;
		}
	}
	return true;
}

//map element to set element
//list element to set element

typedef struct key_val_pairs {
  void* key;
  void* value;
} *KeyValuePair;

/* Adapted from the reference implementation
   of copyString */
ListElement copyKeyValuePair(ListElement keyValuePair) {
  assert(keyValuePair);
  KeyValuePair copy = malloc(sizeof(key_val_pair));
  if (copy == NULL) {
    return NULL;
  }
  copy->key   = ((KeyValuePair) keyValuePair)->key;
  copy->value = ((KeyValuePair) keyValuePair)->value;
  return copy;
}

void freeKeyValuePair(ListElement keyValuePair) {
  free(keyValuePair);
}

List mapToList(Map map, ListResult* status) {
  *status = LIST_SUCCESS;
  if (map == NULL) {
    *status = LIST_NULL_ARGUMENT;
    return NULL;
  }
  List newList = listCreate(copyKeyValuePair, freeKeyValuePair);
  int mapSize = mapGetSize(map);
  if (mapSize == 0) {
    return newList;
  }
  MAP_FOREACH(KeyValuePair, keyValuePair, map) {
    KeyValuePair listElement = malloc(sizeof(key_val_pair));
    if (listElement == NULL) {
      *status = LIST_OUT_OF_MEMORY;
      return NULL;
    }
    listElement->key   = keyValuePair->key;
    listElement->value = mapGet(map, keyValuePair->key);
    if (listInsertLast(newList, listElement) != LIST_SUCCESS) {
      *status = LIST_INVALID_CURRENT;
      return NULL;
    }
  }
  return newList;
}
