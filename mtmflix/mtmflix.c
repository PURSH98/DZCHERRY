//Add ifndef?

#include <stdlib.h>
#include "libmtm.h"
#include "libmtm_ex3.h"
#include "utilities.h"


struct mtmFlix_t {
	Name name;
	Series series;
	User user;
};

MtmFlix mtmFlixCreate();
void mtmFlixDestroy(MtmFlix mtmflix);

MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum, Genre genre, int* ages, int episodesDuration);
MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name);
MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username, const char* seriesName);
MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username, const char* seriesName);

MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age);
MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username);
MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1, const char* username2);
MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1, const char* username2);
MtmFlixResult mtmFlixGetRecommendations(MtmFlix mtmflix, const char* username, int count, FILE* outputStream);

MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, FILE* outputStream);
MtmFlixResult mtmFlixReportUsers(MtmFlix mtmflix, FILE* outputStream);


MtmFlix mtmFlixCreate() {
	MtmFlix mtmflix = malloc(sizeof(MtmFlix));
	if (mtmflix == NULL) {
		return NULL;
	}
	mtmflix->user = mapCreate(UserCopy, StringCopy, UserFree, StringFree, StringCompare);
	if (mtmflix->user == NULL) {
		mtmFlixDestroy(mtmflix);
		return NULL;
	}
	mtmflix->series = mapCreate(SeriesCopy, StringCopy, SeriesFree, StringFree, StringCompare);
	if (mtmflix->series == NULL) {
		mtmFlixDestroy(mtmflix);
		return NULL;
	}
	return mtmflix;
}

void mtmFlixDestroy(MtmFlix mtmflix) {
	mapDestroy(mtmflix->user);
	mtmflix->user = NULL;
	mapDestroy(mtmflix->series);
	mtmflix->series = NULL;
	free(mtmflix);
	mtmflix = NULL;
}

MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {
	if (mtmflix == NULL || username == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!CheckString(username) || age <= MTM_MIN_AGE || age >= MTM_MAX_AGE) {
		return MTMFLIX_ILLEGAL_USERNAME; //why are errors commented out in header? and why there's no such error?
	}
	if (mapContains(mtmflix->user, username)) {
		return MTMFLIX_USERNAME_ALREADY_USED;
	}
	User user = UserCreate(age, NULL, NULL);
	if (user == NULL) {
		return MTMFLIX_OUT_OF_MEMORY;
	}
	switch (mapPut(mtmflix, username, user)) {
		case MAP_OUT_OF_MEMORY : return MTMFLIX_OUT_OF_MEMORY; break;
		case MAP_SUCCESS : return MTM_SUCCESS; break; //check stilistic guidelines
	}
}

MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum, Genre genre, int* ages, int episodesDuration) {
	Series series = SeriesCreate(episodesNum, genre, ages, episodesDuration);
	if (mapPut(mtmflix->series, name, series) == //проверить статусы, поступить соответствующим образом
}

MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name) {
	mapRemove(mtmflix, name);
}

MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username, const char* seriesName) {
	UserAddFavSeries(username, seriesName);
}

MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username, const char* seriesName) {
	//delete from dictionary via user's function
}

MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username);

MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1, const char* username2) {
	UserAddFriend(mapGet(mtmflix->user, username1), username2);
}

MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1, const char* username2) {
	UserRemoveFriend(mapGet(mtmflix->user, username1), username2);
}

MtmFlixResult mtmFlixGetRecommendations(MtmFlix mtmflix, const char* username, int count, FILE* outputStream);

MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, FILE* outputStream);

MtmFlixResult mtmFlixReportUsers(MtmFlix mtmflix, FILE* outputStream);
