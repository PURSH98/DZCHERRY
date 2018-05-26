//ifndef include

struct user_t {
	int age;
	Series fav_series; //set of pointers?
	Friends friends; //set of pointers?
};

User UserCreate(int age, Series fav_series, Friends friends) {
	User user = malloc(sizeof(User));
	if (user == NULL) {
		return NULL;
	}
	user->age = age;
	user->fav_series = fav_series;
	user->friends = friends;
	return user;
}

User UserCopy (User user) {
	if (user == NULL) {
		return NULL;
	}
	User new_user = UserCreate(user->age, user->fav_series, user->friends);
	if (new_user == NULL) {
		return NULL;
	}
	return new_user;
}

void UserFree(User user) {
	user->fav_series = NULL; //we don't need to delete other users or series
	user->friends = NULL;
	free(user);
	user = NULL;
}

MtmFlixResult UserAddFavSeries (User user, Series series) {

}

MtmFlixResult UserAddFriend(User user1, User user2) {

}

MtmFlixResult UserRemoveFriend(User user1, User user2) {

}