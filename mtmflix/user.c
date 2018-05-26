//ifndef include

struct user_t {
	Age age;
	Series fav_series; //set of pointers?
	Friends friends; //set of pointers?
};

MtmFlixResult UserAddFavSeries (User user, Series series) {
	//add to dict
}

MtmFlixResult UserAddFriend(User user1, User user2) {

}

MtmFlixResult UserRemoveFriend(User user1, User user2) {

}

User UserCopy (User user) {
	User new_user = malloc(sizeof(User));
	if (new_user == NULL) {
		return NULL;
	}
	new_user->age = user->age; //just passing indexes, not really copying, looks like that's what is needed
	new_user->fav_series = fav_series;
	new_user->friends = friends;
	return new_user;
}

void UserFree(User user) {
	user->fav_series = NULL; //we don't need to delete other users or series
	user->friends = NULL;
	free(user);
	user = NULL;
}