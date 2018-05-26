#include <stdlib.h>
#include <assert.h>
#include "utilities.h"
#include "mtmflix.h"
#include "user.h"

User userCreate(int age);
User userCopy (User user);
void userFree(User user);
MtmFlixResult userAddFavSeries(User user, char* series_name);
MtmFlixResult userDeleteFavSeries(User user, char* series_name);
MtmFlixResult userAddFriend(User user1, char* username);
MtmFlixResult userRemoveFriend(User user1, char* username);
Set userGetFriends(User user);
int userGetAge(User user);
Set userGetFavSeries(User user);
//ifndef include

struct user_t {
	int age;
	Set fav_series; //set of names
	Set friends; //set of names
};

User userCreate(int age) {
	User user = malloc(sizeof(User));
	if (user == NULL) {
		return NULL;
	}
	user->age = age;
	user->fav_series = setCreate((copySetElements)copyString, (freeSetElements)freeString, (compareSetElements)compareStrings);
	user->friends = setCreate((copySetElements)copyString, (freeSetElements)freeString, (compareSetElements)compareStrings);
	return user;
}

User userCopy (User user) {
	if (user == NULL) {
		return NULL;
	}
	User new_user = malloc(sizeof(User));
	new_user->age = user->age;
	//copy series or just pointer? the same about friends
	if (new_user == NULL) {
		return NULL;
	}
	return new_user;
}

void userFree(User user) {
	user->fav_series = NULL;
	free(user);
	user = NULL;
}

MtmFlixResult userAddFavSeries(User user, char* series_name) {
	//series must be a series element here
	switch(setAdd(user->fav_series, (SetElement)series_name)) {
		default : return MTMFLIX_SUCCESS;
	}
	// Unreachable
	assert(false);
	return MTMFLIX_NO_SERIES;
}

MtmFlixResult userDeleteFavSeries(User user, char* series_name) {
	setRemove(user->fav_series, series_name);
	return MTMFLIX_SUCCESS;
	//add errors
}


MtmFlixResult userAddFriend(User user1, char* username) {
	setAdd(user1->friends, username);
	return MTMFLIX_SUCCESS;
	//add errors
}

MtmFlixResult userRemoveFriend(User user1, char* username) {
	setRemove(user1->friends, username);
	return MTMFLIX_SUCCESS;
	//add errors
}

Set userGetFavSeries(User user){
    if(user==NULL){
        return NULL;
    }
    return user->fav_series;
}

int userGetAge(User user){
    if(user==NULL){
        return 0;
    }
    return user->age;
}

Set userGetFriends(User user){
    if(user==NULL){
        return NULL;
    }
    return user->friends;
}
