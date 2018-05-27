#include "map.h"
#include "list.h"
#include "set.h"

//https://moodle.technion.ac.il/mod/hsuforum/discuss.php?d=440

typedef struct key_val_pair_t {
  void* key;
  void* value;
}* KeyValuePair;

const char* copyString(const char* str);
void freeString(const char* str);
int compareStrings(void * str_a, void * str_b);
bool stringCheck(const char* string);

List mapToList(Map map, ListResult* status);
// There _is_ a function setToList in libmtm.a;
// however, it is not declared in the set.h;
// using our own implementation.
List mtmSetToList(Set set, ListResult* status);
List mapKeyToList(Map map, ListResult* status);
void listPutValue(KeyValuePair listElement, void* value);
void* listGetValue(KeyValuePair listElement);
void* listGetKey(KeyValuePair listElement);
