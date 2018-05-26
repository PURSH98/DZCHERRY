#include "map.h"
#include "list.h"

//https://moodle.technion.ac.il/mod/hsuforum/discuss.php?d=440

typedef struct key_val_pair_t {
  void* key;
  void* value;
}* KeyValuePair;

const char* copyString(const char* str);
void freeString(char* str);
int compareStrings(char* str_a, char* str_b);
bool stringCheck(const char* string);

List mapToList(Map map, ListResult* status);