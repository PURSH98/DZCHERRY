//see header for explanation
#include <string.h>


static ??? SeriesMapToList (Map map, Type type) { //what does it return? we have no list types
	List list = listCreate(copy, destroy);
	mapGetFirst(Map map);
	MAP_FOREACH(type,iterator,map) { //FOREACH example https://moodle.technion.ac.il/mod/hsuforum/discuss.php?d=397
	
	}
	//empty list
	//for series in series
	//add series contents to list
}


StringCopy
StringCompare
StringFree

//create a private copy of a string. do we need this?
const char* stringDuplicate(char* str) {
	char* copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}

bool stringCheck (char* string) {
	int length = strlen(string);
	for (int i = 0; i < length; i++) {
		if !((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z') || (string[i] >= '0' && <= '9')) {
			return false;
		}
	}
	return true;
}