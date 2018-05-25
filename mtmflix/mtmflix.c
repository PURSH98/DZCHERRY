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
	//create a network
	MtmFlix mtmflix = malloc(sizeof(MtmFlix));
	mtmflix->user = mapCreate();
	mtmflix->series = mapCreate();
	//проверить, что они не возвращают ошибку
	//возможно, сначала инициализировать их на NULL?
	return mtmflix;
	//errors
}

void mtmFlixDestroy(MtmFlix mtmflix) {
	//DESTROY ALL FIELDS
	mapDestroy(mtmflix->user);
	mapDestroy(mtmflix->series);
	free(mtmflix);
	mtmflix = NULL;
	//destroy a network
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

MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {
	User user = UserCreate(age); //should we add username to user struct too? but then we will keep two instances of a name
	if (mapPut mtmflix->users(mtmflix, username, user) ==
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
