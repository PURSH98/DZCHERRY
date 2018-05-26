#include <stdlib.h>
#include "mtmflix.h"
#include "utilities.h"
#include "series.h"
#include "user.h"

struct mtmFlix_t {
	Map series;     // keys: string; values: Series
	Map users;       // keys: string; values: User
}

// MtmFlix mtmFlixCreate();
// void mtmFlixDestroy(MtmFlix mtmflix);

// MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum, Genre genre, int* ages, int episodesDuration);
// MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name);
// MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username, const char* seriesName);
// MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username, const char* seriesName);

// MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age);
// MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username);
// MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1, const char* username2);
// MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1, const char* username2);
// MtmFlixResult mtmFlixGetRecommendations(MtmFlix mtmflix, const char* username, int count, FILE* outputStream);

// MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, FILE* outputStream);
// MtmFlixResult mtmFlixReportUsers(MtmFlix mtmflix, FILE* outputStream);

MtmFlix mtmFlixCreate() {
	MtmFlix mtmflix = malloc(sizeof(MtmFlix));
	if (mtmflix == NULL) {
		return NULL;
	}
	mtmflix->users = mapCreate((copyMapDataElements)userCopy, (copyMapKeyElements)copyString, (freeMapDataElements)userFree, (freeMapKeyElements)freeString, (compareMapKeyElements)compareStrings);
	if (mtmflix->users == NULL) {
		mtmFlixDestroy(mtmflix);
		return NULL;
	}
	mtmflix->series = mapCreate((copyMapDataElements)seriesCopy, (copyMapKeyElements)copyString, (freeMapDataElements)seriesFree, (freeMapKeyElements)freeString, (compareMapKeyElements)compareStrings);
	if (mtmflix->series == NULL) {
		mtmFlixDestroy(mtmflix);
		return NULL;
	}
	return mtmflix;
}

void mtmFlixDestroy(MtmFlix mtmflix) {
	mapDestroy(mtmflix->users);
	mtmflix->users = NULL;
	mapDestroy(mtmflix->series);
	mtmflix->series = NULL;
	free(mtmflix);
	mtmflix = NULL;
}

MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {
	if (mtmflix == NULL || username == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!checkString(username)) {
		return MTMFLIX_ILLEGAL_USERNAME; //why are errors commented out in header? and why there's no such error?
	}
	if (mapContains(mtmflix->user, username)) {
		return MTMFLIX_USERNAME_ALREADY_USED;
	}
	if (age <= MTM_MIN_AGE || age >= MTM_MAX_AGE) {
		return MTMFLIX_ILLEGAL_AGE;
	}
	User user = userCreate(age, NULL, NULL);
	if (user == NULL) {
		return MTMFLIX_OUT_OF_MEMORY;
	}
	switch (mapPut(mtmflix->user, username, user)) {
		case MAP_OUT_OF_MEMORY : return MTMFLIX_OUT_OF_MEMORY; break;
		case MAP_SUCCESS : return MTMFLIX_SUCCESS; break; //check stilistic guidelines
	}
}

MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username) {
	if (mtmflix == NULL || username == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	} 
	//iterate over users to remove from friends
	switch (mapRemove (mtmflix->user, username)) {
		case MAP_ITEM_DOES_NOT_EXIST : return MTMFLIX_USER_DOES_NOT_EXIST;
		case MAP_SUCCESS : return MTMFLIX_SUCCESS;
	}
}

MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum, Genre genre, int* ages, int episodesDuration) {
	if (mtmflix == NULL || name == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!CheckString(name)) {
		return MTMFLIX_ILLEGAL_SERIES_NAME; //why are errors commented out in header? and why there's no such error?
	}
	if (mapContains(mtmflix->series, name)) {
		return MTMFLIX_SERIES_ALREADY_EXISTS;
	}
	if (episodesNum <= 0) {
		return MTMFLIX_ILLEGAL_EPISODES_NUM;
	}
	if (episodesDuration <= 0) {
		return MTMFLIX_ILLEGAL_EPISODES_DURATION;
	}
	Series series = SeriesCreate(episodesNum, genre, ages, episodesDuration);
	if (series == NULL) {
		return MTMFLIX_OUT_OF_MEMORY;
	}
	switch (mapPut(mtmflix->series, name, series)) {
		case MAP_OUT_OF_MEMORY : return MTMFLIX_OUT_OF_MEMORY;
		case MAP_SUCCESS : return MTMFLIX_SUCCESS; //check stilistic guidelines
	}
}

MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name) {
	//iterate over users to remove from preferences
	if (mtmflix == NULL || name == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	switch (mapRemove (mtmflix->series, name)) {
		case MAP_ITEM_DOES_NOT_EXIST : return MTMFLIX_NO_SERIES;
		case MAP_SUCCESS : return MTMFLIX_SUCCESS;
	}
}

MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, FILE* outputStream {
	List series_node = mapToList(mtmflix->series);
	listSort(series_node, seriesListCompare); //not sure about the first parameter
	LIST_FOREACH(KeyValuePair,series,series_node) {
		mtmPrintSeries(series->key, seriesGetGenre(series->key)); //check
	}
}

int seriesListCompare(ListElement list_element_a, ListElement list_element_b) {
	void* series_a = ((KeyValuePair)list_element_a)->value;
	void* series_b = ((KeyValuePair)list_element_b)->value;
	int genre_comparison_result = compareSeriesByGenre(series_a, series_b);
	if (genre_comparison_result != 0) {
		return genre_comparison_result;
	}
	void* key_a = ((KeyValuePair)list_element_a)->key;
	void* key_b = ((KeyValuePair)list_element_b)->key;
	return strcmp(key_a, key_b);
}

// MtmFlixResult mtmFlixReportUsers(MtmFlix mtmflix, FILE* outputStream);


// MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username, const char* seriesName) {
// 	userAddFavSeries(username, seriesName);
// }

// MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username, const char* seriesName) {
// 	//delete from dictionary via user's function
// }


// MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1, const char* username2) {
// 	userAddFriend(mapGet(mtmflix->user, username1), username2);
// }

// MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1, const char* username2) {
// 	userRemoveFriend(mapGet(mtmflix->user, username1), username2);
// }

// MtmFlixResult mtmFlixGetRecommendations(MtmFlix mtmflix, const char* username, int count, FILE* outputStream);

// Windows expects a main function
// in a console app.
int main() {
	return 0;
}