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

//creates a user instance given user's age
//it will be used as a value in a key-value pair in a map of users
User userCreate(int age) {
	User user = malloc(sizeof(*user));
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

//creater a copy of a user instance, returns a new user
User userCopy (User user) {
	if (user == NULL) {
		return NULL;
	}
	User new_user = malloc(sizeof(User));
	new_user->age = user->age;
	if (new_user == NULL) {
		return NULL;
	}
	return new_user;
}

//deletes a user
void userFree(User user) {
	user->fav_series = NULL;
	user->friends = NULL;
	free(user);
	user = NULL;
}

//given a name of a series and a user, 
//adds the series to the list of the user's favorite series
MtmFlixResult userAddFavSeries(User user, const char* series_name) {
	//we check those arguments before passing them to the function
	assert(user != NULL && series_name != NULL);
	setAdd(user->fav_series, (SetElement)series_name);
	return MTMFLIX_SUCCESS;
}

//given a name of a series and a user, 
//removes the series from the list of the user's favorite series
MtmFlixResult userDeleteFavSeries(User user, const char* series_name) {
	//we check those arguments before passing them to the function
	assert(user != NULL && series_name != NULL);
	setRemove(user->fav_series, (SetElement)series_name);
	return MTMFLIX_SUCCESS;
}

//given a user instance (user1), and a name of another user
//adds the second user to the first user's friend list
MtmFlixResult userAddFriend(User user1, const char* username) {
	//we check those arguments before passing them to the function
	assert(user1 != NULL && username != NULL);
	setAdd(user1->friends, (SetElement)username);
	return MTMFLIX_SUCCESS;
}

//given a user instance (user1), and a name of another user,
//deletes the second user from the first user's friend list
MtmFlixResult userRemoveFriend(User user1, const char* username) {
	//we check those arguments before passing them to the function
	assert(user1 != NULL && username != NULL);
	setRemove(user1->friends, (SetElement)username);
	return MTMFLIX_SUCCESS;
}

//given a user instance, returns the user's favorite series
Set userGetFavSeries(User user){
    if(user==NULL){
        return NULL;
    }
    return user->fav_series;
}

//given a user instance, returns the user's age
int userGetAge(User user){
    if(user==NULL){
        return 0;
    }
    return user->age;
}

//given a user instance, returns the user's friends
Set userGetFriends(User user){
    if(user==NULL){
        return NULL;
    }
    return user->friends;
}
