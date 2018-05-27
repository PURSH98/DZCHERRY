//ifndef include
#include "set.h"
#include "series.h"

typedef struct user_t* User;

User userCreate(int age);
User userCopy (User user);
void userFree(User user);

MtmFlixResult userAddFavSeries (User user, const char* series_name);
MtmFlixResult userAddFriend(User user1, const char* username);
MtmFlixResult userRemoveFriend(User user1, const char* username);
MtmFlixResult userAddFavSeries(User user, const char* series_name);
MtmFlixResult userDeleteFavSeries(User user, const char* series_name);
MtmFlixResult userAddFavSeries (User user, const char* series_name);

Set userGetFriends(User user);
int userGetAge(User user);
Set userGetFavSeries(User user);
