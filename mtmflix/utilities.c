#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mtmflix.h"
#include "utilities.h"
#include "set.h"

//creates a const copy of a given string
const char* copyString(const char* str) {
  int length = strlen(str);
  char* new_str = malloc(length+1);
  if (new_str == NULL) {
    return NULL; //DO SOMETHING WITH THIS
  }
  assert(new_str);
  strcpy(new_str, str);
  return new_str;
}

//frees a string
void freeString(const char* str) {
  free((void*)str);
}

int compareStrings(void * str_a, void * str_b) {
  return strcmp((char*)str_a, (char*)str_b);
}

//Checks if the string can be
//legal series or user name
bool stringCheck(const char* string) {
	int length = strlen(string);
	if(length==0){
        return false;
	}
	for (int i = 0; i < length; i++) {
		if (!((string[i] >= 'A' && string[i] <= 'Z') || 
      (string[i] >= 'a' && string[i] <= 'z') || 
      (string[i] >= '0' && string[i] <= '9'))) {
			return false;
		}
	}
	return true;
}

//Creates a copy of the element of the
//specific type list, which stores key-value pairs
ListElement copyKeyValuePair(ListElement keyValuePair) {
  assert(keyValuePair);
  KeyValuePair copy = malloc(sizeof(KeyValuePair));
  if (keyValuePair == NULL) {
    return NULL;
  }
  copy->key   = ((KeyValuePair) keyValuePair)->key;
  copy->value = ((KeyValuePair) keyValuePair)->value;
  return copy;
}

void freeKeyValuePair(ListElement keyValuePair) {
  free(keyValuePair);
}

//Creates a list based on the given map
//List does store elements as key-value pairs
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
    KeyValuePair listElement = malloc(sizeof(KeyValuePair));
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

//Creates a list based on the give set
List mtmSetToList(Set set, ListResult* status){
    *status=LIST_SUCCESS;
    if (set == NULL) {
        *status = LIST_NULL_ARGUMENT;
        return NULL;
    }
    List newList = listCreate((CopyListElement)copyString,
            (FreeListElement)freeString);
    int setSize = setGetSize(set);
    if (setSize == 0) {
        return newList;
    }
    SET_FOREACH(ListElement, setElement, set) {
        ListElement listElement = malloc(sizeof(ListElement));
        if (listElement == NULL) {
            *status = LIST_OUT_OF_MEMORY;
            return NULL;
        }
        listElement = setElement;
        if (listInsertLast(newList, listElement) != LIST_SUCCESS) {
            *status = LIST_INVALID_CURRENT;
            return NULL;
        }
    }
    return newList;
}

//Creates a simple list based on the given map
List mapKeyToList(Map map, ListResult* status){
    *status=LIST_SUCCESS;
    if (map == NULL) {
        *status = LIST_NULL_ARGUMENT;
        return NULL;
    }
    List newList = listCreate((CopyListElement)copyString,
            (FreeListElement)freeString);
    int mapSize = mapGetSize(map);
    if (mapSize == 0) {
        return newList;
    }
    MAP_FOREACH(ListElement, mapKeyElement, map) {
        ListElement listElement = malloc(sizeof(ListElement));
        if (listElement == NULL) {
            *status = LIST_OUT_OF_MEMORY;
            return NULL;
        }
        listElement = mapKeyElement;
        if (listInsertLast(newList, listElement) != LIST_SUCCESS) {
            *status = LIST_INVALID_CURRENT;
            return NULL;
        }
    }
    return newList;
}

//Puts value into the value field
//of list element of the key-value type
void listPutValue(KeyValuePair listElement, void* value){
    if(listElement==NULL||value==NULL){
        return;
    }
    listElement->value=value;
}

//Returns value of list element
//of the key-value type
void* listGetValue(KeyValuePair listElement){
    if(listElement==NULL){
        return NULL;
    }
    return listElement->value;
}

//Returns key of list element
//of the key-value type
void* listGetKey(KeyValuePair listElement){
    if(listElement==NULL){
        return NULL;
    }
    return listElement->key;
}



