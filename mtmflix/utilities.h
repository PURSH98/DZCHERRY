#include "map.h"
#include "list.h"

//https://moodle.technion.ac.il/mod/hsuforum/discuss.php?d=440

typedef struct key_val_pair_t* KeyValuePair;

// copystring
char* copyString(char* str);
void freeString(char* str);
int compareStrings(char* str_a, char* str_b);
bool stringCheck (char* string);

// maptolist
List mapToList(Map map, ListResult* status);