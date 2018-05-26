//ifndef include

struct user_t {
	int age;
	Series fav_series; //set of pointers?
	Friends friends; //set of pointers?
};

User userCreate(int age, Series fav_series, Friends friends) {
	User user = malloc(sizeof(User));
	if (user == NULL) {
		return NULL;
	}
	user->age = age;
	user->fav_series = setCreate(copySeriesElement, freeSeriesElement, compareSeriesElements);
	user->friends = setCreate(copyFriendElement, freeFriendElement, compareFriendElements);
	return user;
}

User userCopy (User user) {
	if (user == NULL) {
		return NULL;
	}
	User new_user = malloc(User);
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

MtmFlixResult userAddFavSeries (User user, SeriesElement series_element) {
	//series must be a series element here
	setAdd(user->fav_series, series_element);
	//errors
}

MtmFlixResult userAddFriend(User user1, User user2) {

}

SeriesElement copySeriesElement {

}

void freeSeriesElement(SeriesElement series_element) {

}

int compareSeriesElements(SeriesElement series_element_a, SeriesElement series_element_b) {

}


SeriesElement copyFriendElement {

}

void freeFriendElement(SeriesElement series_element) {

}

int compareFriendElements(SeriesElement series_element_a, SeriesElement series_element_b) {

}

MtmFlixResult UserRemoveFriend(User user1, User user2) {

}