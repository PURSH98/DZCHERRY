//ifndef include
#include "set.h"

typedef struct user_t* User;

User userCreate(int age, Series fav_series, Set friends);
User userCopy (User user);
void userFree(User user);
MtmFlixResult userAddFavSeries (User user, char* series_name);