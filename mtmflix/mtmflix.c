#include <stdlib.h>
#include <string.h>
#include "mtmflix.h"
#include "utilities.h"
#include "user.h"
#include "assert.h"

static int seriesListCompare(ListElement list_element_a, 
	ListElement list_element_b);
static int seriesRankCompare(KeyValuePair series_1, KeyValuePair series_2);
static int getSeriesRank(Series series, User user);

struct mtmFlix_t {
	Map series;     // keys: string; values: Series
	Map users;       // keys: string; values: User
};

MtmFlix mtmFlixCreate() {
	MtmFlix mtmflix = malloc(sizeof(*mtmflix));
	if (mtmflix == NULL) {
		return NULL;
	}
	mtmflix->users = mapCreate((copyMapDataElements)userCopy, 
		(copyMapKeyElements)copyString, (freeMapDataElements)userFree, 
		(freeMapKeyElements)freeString, (compareMapKeyElements)compareStrings);
	if (mtmflix->users == NULL) {
		mtmFlixDestroy(mtmflix);
		return NULL;
	}
	mtmflix->series = mapCreate((copyMapDataElements)seriesCopy, 
		(copyMapKeyElements)copyString, (freeMapDataElements)seriesFree, 
		(freeMapKeyElements)freeString, (compareMapKeyElements)compareStrings);
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

//check if it suites PDF
MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {
	if (mtmflix == NULL || username == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!stringCheck(username)) {
		return MTMFLIX_ILLEGAL_USERNAME;
	}
	if (mapContains(mtmflix->users, (MapKeyElement) username)) {
		return MTMFLIX_USERNAME_ALREADY_USED;
	}
	if (age < MTM_MIN_AGE || age > MTM_MAX_AGE) {
		return MTMFLIX_ILLEGAL_AGE;
	}
	User user = userCreate(age);
	if (user == NULL) {
		return MTMFLIX_OUT_OF_MEMORY;
	}
	switch (mapPut(mtmflix->users, (MapKeyElement)username, 
		(MapDataElement)user)) {
		case MAP_OUT_OF_MEMORY : return MTMFLIX_OUT_OF_MEMORY;
		case MAP_SUCCESS : return MTMFLIX_SUCCESS;
		default : assert(false);
	}
	assert(false);
	return MTMFLIX_NULL_ARGUMENT;
}

MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username) {
	if (mtmflix == NULL || username == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	} 
	MAP_FOREACH(char*, username1, mtmflix->users) {
		mtmFlixRemoveFriend(mtmflix, username1, username);
	}
	switch (mapRemove (mtmflix->users, (MapKeyElement)username)) {
		case MAP_ITEM_DOES_NOT_EXIST : return MTMFLIX_USER_DOES_NOT_EXIST;
		case MAP_SUCCESS : return MTMFLIX_SUCCESS;
		default : assert(false); //we're not supposed to get here
	}
	assert(false);
	return MTMFLIX_NULL_ARGUMENT;
}

MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, 
	int episodesNum, Genre genre, int* ages, int episodesDuration) {
	if (mtmflix == NULL || name == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!stringCheck(name)) {
		return MTMFLIX_ILLEGAL_SERIES_NAME;
	}
	if (mapContains(mtmflix->series, (MapKeyElement)name)) {
		return MTMFLIX_SERIES_ALREADY_EXISTS;
	}
	if (episodesNum <= 0) {
		return MTMFLIX_ILLEGAL_EPISODES_NUM;
	}
	if (episodesDuration <= 0) {
		return MTMFLIX_ILLEGAL_EPISODES_DURATION;
	}
	Series series = seriesCreate(episodesNum, genre, ages, episodesDuration);
	if (series == NULL) {
		return MTMFLIX_OUT_OF_MEMORY;
	}
	switch (mapPut(mtmflix->series, (MapKeyElement)name, 
		(MapDataElement)series)) {
		case MAP_NULL_ARGUMENT : return MTMFLIX_NULL_ARGUMENT;
		case MAP_OUT_OF_MEMORY : return MTMFLIX_OUT_OF_MEMORY;
		case MAP_SUCCESS : return MTMFLIX_SUCCESS;
		default : assert(false); //we're not supposed to get here
	}
	assert(false);
	return MTMFLIX_NULL_ARGUMENT;//we're not supposed to get here
}

MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name) {
	if (mtmflix == NULL || name == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	MAP_FOREACH(char*, username, mtmflix->users) {
		mtmFlixSeriesLeave(mtmflix, username, name);
	}
	switch (mapRemove (mtmflix->series, (MapKeyElement)name)) {
		case MAP_NULL_ARGUMENT : return MTMFLIX_NULL_ARGUMENT;
		case MAP_ITEM_DOES_NOT_EXIST : return MTMFLIX_NO_SERIES;
		case MAP_SUCCESS : return MTMFLIX_SUCCESS;
		default : assert(false); //we're not supposed to get here
	}
	assert(false);
	return MTMFLIX_NULL_ARGUMENT;//we're not supposed to get here
}

MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, 
	FILE* outputStream) {
    if(mtmflix==NULL){
        return MTMFLIX_NULL_ARGUMENT;
    }
    if(mapGetSize(mtmflix->series)==0){
        return MTMFLIX_NO_SERIES;
    }
	ListResult list_result;
	List series_list = mapToList(mtmflix->series, &list_result);
	switch (list_result){
        case LIST_NULL_ARGUMENT:return MTMFLIX_NULL_ARGUMENT;
        case LIST_OUT_OF_MEMORY:return MTMFLIX_OUT_OF_MEMORY;
        default:break;
	}
	if(seriesNum==0){
	    seriesNum=mapGetSize(mtmflix->series);
	}
	listSort(series_list, seriesListCompare);
	char* prev_genre=NULL;
	int genre_count=0;
	LIST_FOREACH(KeyValuePair,list_iter,series_list) {
		void* key = (KeyValuePair)list_iter->key;
		void* value = (KeyValuePair)list_iter->value;
		if(strcmp(prev_genre,seriesGetGenre((Series)value))==0){
			genre_count=0;
			prev_genre=seriesGetGenre((Series)value);
		}
		if(genre_count<seriesNum) {
			fprintf(outputStream, "%s",
					mtmPrintSeries((char *) key, seriesGetGenre((Series) value)));
		}
	}
	return MTMFLIX_SUCCESS;
}


MtmFlixResult mtmFlixReportUsers(MtmFlix mtmflix, FILE* outputStream){
	if(mtmflix==NULL){
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (mapGetSize(mtmflix->users)==0){
		return MTMFLIX_NO_USERS;
	}
    ListResult list_result;
    List users_list = mapKeyToList(mtmflix->users, &list_result);
    switch (list_result){
        case LIST_NULL_ARGUMENT:return MTMFLIX_NULL_ARGUMENT;
        case LIST_OUT_OF_MEMORY:return MTMFLIX_OUT_OF_MEMORY;
        default:break;
    }
    listSort(users_list,compareStrings);
    LIST_FOREACH(ListElement ,list_iter,users_list) {
        User user=mapGet(mtmflix->users,list_iter);
        List fav_series=mtmSetToList(userGetFavSeries(user),&list_result);
        switch (list_result){
            case LIST_NULL_ARGUMENT:return MTMFLIX_NULL_ARGUMENT;
            case LIST_OUT_OF_MEMORY:return MTMFLIX_OUT_OF_MEMORY;
            default:break;
        }
        List friends=mtmSetToList(userGetFriends(user),&list_result);
        switch (list_result){
            case LIST_NULL_ARGUMENT:return MTMFLIX_NULL_ARGUMENT;
            case LIST_OUT_OF_MEMORY:return MTMFLIX_OUT_OF_MEMORY;
            default:break;
        }
        int age=userGetAge(user);
        fprintf(outputStream, "%s",
                mtmPrintUser((char*)list_iter,age, friends,fav_series));
        //free functions are needed here(probably)
    }
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username, 
	const char* seriesName) {
	if (mtmflix == NULL || username == NULL || seriesName == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!mapContains(mtmflix->users, (MapKeyElement)username)) {
		return MTMFLIX_USER_DOES_NOT_EXIST;
	}
	if (!mapContains(mtmflix->series, (MapKeyElement)seriesName)) {
		return MTMFLIX_SERIES_DOES_NOT_EXIST;
	}
	if (userGetAge(mapGet(mtmflix->users, (MapKeyElement)username)) <= 
		seriesGetMinAge(mapGet(mtmflix->series, (MapKeyElement)seriesName)) ||
		userGetAge(mapGet(mtmflix->users, (MapKeyElement)username)) >= 
		seriesGetMaxAge(mapGet(mtmflix->series, (MapKeyElement)seriesName))) {
		return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
	}
 	userAddFavSeries(mapGet(mtmflix->users, (MapKeyElement)username), 
 		seriesName);
 	return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username, 
	const char* seriesName) {
	if (mtmflix == NULL || username == NULL || seriesName == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!mapContains(mtmflix->users, (MapKeyElement)username)) {
		return MTMFLIX_USER_DOES_NOT_EXIST;
	}
	if (!mapContains(mtmflix->series, (MapKeyElement)seriesName)) {
		return MTMFLIX_SERIES_DOES_NOT_EXIST;
	}
	userDeleteFavSeries(mapGet(mtmflix->users, (MapKeyElement)username), 
		seriesName);
	return MTMFLIX_SUCCESS;
}


MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1, 
	const char* username2) {
	if (mtmflix == NULL || username1 == NULL || username2 == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!mapContains(mtmflix->users, (MapKeyElement)username1) || 
		!mapContains(mtmflix->users, (MapKeyElement)username2)) {
		return MTMFLIX_USER_DOES_NOT_EXIST;
	}
	userAddFriend(mapGet(mtmflix->users, (MapKeyElement)username1), username2);
	return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1, 
	const char* username2) {
	if (mtmflix == NULL || username1 == NULL || username2 == NULL) {
		return MTMFLIX_NULL_ARGUMENT;
	}
	if (!mapContains(mtmflix->users, (MapKeyElement)username1) || 
		!mapContains(mtmflix->users, (MapKeyElement)username2)) {
		return MTMFLIX_USER_DOES_NOT_EXIST;
	}
	userRemoveFriend(mapGet(mtmflix->users, (MapKeyElement)username1), 
		username2);
	return MTMFLIX_SUCCESS;
}

//a comparator helper function that helps to sort series by genre;
//series with the same genre are ordered alphabetically 
static int seriesListCompare(ListElement list_element_a, 
	ListElement list_element_b) {
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


MtmFlixResult mtmFlixGetRecommendations(MtmFlix mtmflix, const char* username, 
	int count, FILE* outputStream){
    //checking params
	if(count==0){
		count=mapGetSize(mtmflix->series);
	}
    ListResult listResult;
    List series_list=mapToList(mtmflix->series,&listResult);
	User user=mapGet(mtmflix->users,(char*)username);
	LIST_FOREACH(KeyValuePair,iterator,series_list){
	    Series series=mapGet(mtmflix->series,listGetKey(iterator));
		int series_rank=getSeriesRank(series,user);
		listPutValue(iterator,&series_rank);
	}
	listSort(series_list, (CompareListElements) seriesRankCompare);
	int i=0;
    LIST_FOREACH(KeyValuePair,iterator,series_list) {
    	if(i>=count){
			return MTMFLIX_SUCCESS;
    	}
        Series series = mapGet(mtmflix->series, listGetKey(iterator));
        const char* series_string = mtmPrintSeries((char *) listGetKey(iterator),
         									seriesGetGenre(series));
        fprintf(outputStream, "%s", series_string);
        i++;
    }
    return MTMFLIX_SUCCESS;
}

static int seriesRankCompare(KeyValuePair series_1, KeyValuePair series_2){
    if(series_1==NULL||series_2==NULL){
        return 0;
    }
    int rank_series_1=*(int*)listGetValue(series_1);
    int rank_series_2=*(int*)listGetValue(series_2);
    if(rank_series_1==rank_series_2){
        return strcmp((char*)series_2,(char*)series_1);
    }
    return rank_series_2-rank_series_1;
}

static int rank_F_Count(Series series, User user){
    int F=0;
    Set user_friends=userGetFriends(user);
    SET_FOREACH(User,iterator,user_friends){
        Set friend_fav_series=userGetFavSeries(iterator);
        if(setIsIn(friend_fav_series,series)){
            F++;
        }
    }
    return F;
}

static int rank_G_Count(Series series,User user){
    int G=0;
    Set user_fav_series=userGetFavSeries(user);
    SET_FOREACH(Series,iterator,user_fav_series){
        if(compareSeriesByGenre(series,iterator)==0){
            G++;
        }
    }
    return G;
}

static int rank_L_Count(User user){
    double L=0;
    Set user_fav_series=userGetFavSeries(user);
    int num_of_fav_series=setGetSize(user_fav_series);
    SET_FOREACH(Series,iterator,user_fav_series){
        L+=seriesGetEpisodeDuration(iterator)/(double)num_of_fav_series;
    }
    return (int)L;
}

static int getSeriesRank(Series series, User user){
    int F=rank_F_Count(series,user);
    int G=rank_G_Count(series,user);
    int L=rank_L_Count(user);
	int rank=(int)((G*F)/(1.0+abs(seriesGetEpisodeDuration(series)-L)));
    return rank;
}

