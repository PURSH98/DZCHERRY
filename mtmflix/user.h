//ifndef include
#include "set.h"
#include "series.h"

typedef struct user_t* User;

User userCreate(int age);
User userCopy (User user);
void userFree(User user);
MtmFlixResult userAddFavSeries (User user, char* series_name);
Set userGetFriends(User user);
int userGetAge(User user);
Set userGetFavSeries(User user);