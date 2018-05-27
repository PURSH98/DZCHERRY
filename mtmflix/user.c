#include <stdlib.h>
#include <assert.h>
#include "utilities.h"
#include "mtmflix.h"
#include "user.h"

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
	user->fav_series = setCreate((copySetElements)copyString, 
		(freeSetElements)freeString, (compareSetElements)compareStrings);
	user->friends = setCreate((copySetElements)copyString, 
		(freeSetElements)freeString, (compareSetElements)compareStrings);
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

MtmFlixResult userAddFavSeries(User user, const char* series_name) {
	assert(user != NULL && series_name != NULL); //we check those arguments before passing them to the function
	setAdd(user->fav_series, (SetElement)series_name);
	return MTMFLIX_SUCCESS;
}

MtmFlixResult userDeleteFavSeries(User user, const char* series_name) {
	assert(user != NULL && series_name != NULL); //we check those arguments before passing them to the function
	setRemove(user->fav_series, (SetElement)series_name);
	return MTMFLIX_SUCCESS;
}


MtmFlixResult userAddFriend(User user1, const char* username) {
	assert(user1 != NULL && username != NULL); //we check those arguments before passing them to the function
	setAdd(user1->friends, (SetElement)username);
	return MTMFLIX_SUCCESS;
}

MtmFlixResult userRemoveFriend(User user1, const char* username) {
	assert(user1 != NULL && username != NULL); //we check those arguments before passing them to the function
	setRemove(user1->friends, (SetElement)username);
	return MTMFLIX_SUCCESS;
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
