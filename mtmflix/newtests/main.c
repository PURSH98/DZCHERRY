#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "test_utilities.h"
#include "test_utilities_2.h"
#include "../mtmflix.h"
#include "../set.h"
#include "../mtm_ex3.h"
#include "../list.h"

void test1_again(FILE *f1);
void test2_again(FILE *f1);
void test3_again(FILE *f1);
void finalCheck();
char* readFile(char* path);
int mtmFlixCreateDestroyTest(int* tests_passed);
int addUserTest(MtmFlix m, int* tests_passed);
int removeUserTest(MtmFlix m, int* tests_passed);
int addSeriesTest(MtmFlix m, int* tests_passed);
int removeSeriesTest(MtmFlix m, int* tests_passed);
int reportSeriesTest(MtmFlix m, int* tests_passed);
int reportUsersTest(MtmFlix m, int* tests_passed);
int seriesJoinTest(MtmFlix m, int* tests_passed);
int seriesLeaveTest(MtmFlix m, int* tests_passed);
int addFriendTest(MtmFlix m, int* tests_passed);
int removeFriendTest(MtmFlix m, int* tests_passed);
int getRecommendationsTest(MtmFlix m, int* tests_passed);
bool mtmFlixUnitTest();
bool mtmFlixCreateTest();
bool mtmflixAddUserTest();
bool mtmFlixRemoveUserTest();
bool mtmFlixAddSeriesTest();
bool mtmFlixRemoveSeriesTest();
bool mtmFlixReportUsersTest();
bool mtmFlixReportSeriesTest();
bool mtmFlixSeriesJoinTest();
bool mtmFlixSeriesLeaveTest();
bool mtmFlixAddFriendTest();
bool mtmFlixRemoveFriendTest();
bool mtmFlixGetRecommendationsTest();
bool mtmFlixRemoveUserTestAdvanced();
bool mtmFlixRemoveSeriesTestAdvanced();

int main() {
    printf("\nWelcome to the homework 3 mtmflix tests, written by Vova Parakhin.\n\n---Passing those tests won't "
           "guarantee you a good grade---\nBut they might get you close to one "
           ",make some tests yourself to be sure.\n\n");
    printf("You can change w/e you want in the file itself but make sure \nto contact me if you want to upload");
    printf(" \'upgraded version\' of the file\n");
    printf("\nPress any button to start the tests:. \n\n");
    getchar();
    mtmFlixUnitTest();
    int tests_passed = 0;
    int tests_number = 0;
    MtmFlix m = mtmFlixCreate();
    tests_number += mtmFlixCreateDestroyTest(&tests_passed);
    tests_number += addUserTest(m, &tests_passed);
    tests_number += removeUserTest(m, &tests_passed);
    tests_number += addSeriesTest(m, &tests_passed);
    tests_number += removeSeriesTest(m, &tests_passed);
    tests_number += reportSeriesTest(m, &tests_passed);
    tests_number += reportUsersTest(m, &tests_passed);
    tests_number += seriesJoinTest(m, &tests_passed);
    tests_number += seriesLeaveTest(m, &tests_passed);
    tests_number += addFriendTest(m, &tests_passed);
    tests_number += removeFriendTest(m, &tests_passed);
    tests_number += getRecommendationsTest(m, &tests_passed);
    mtmFlixDestroy(m);
    print_grade(tests_number, tests_passed);
    printf("-\n");
    FILE *f1 = fopen("OutputFileFromTest", "w");
    assert(f1);
    /**
    * NOTICE
    * If you are about to change the test code,
    * the test won't work properly and you might get
    * additional fails at the finalCheck function.
    */
    test1_again(f1);
    test2_again(f1);
    test3_again(f1);
    fclose(f1);

    finalCheck();
    getchar();
    return 0;
}

int mtmFlixCreateDestroyTest(int* tests_passed){
    _print_mode_name("Testing Create&Destroy functions");
    int test_number = 0;
    MtmFlix m = mtmFlixCreate();
    test( !m , __LINE__, &test_number, "Couldn't create the Mtmflix series", tests_passed);
    _print_test_number(test_number, __LINE__+1);
    mtmFlixDestroy(NULL); // Silient test will crash if Destroy doesn't react properly on NULL input.
    _print_test_success(test_number);
    test_number += 1;
    mtmFlixDestroy(m); //Check for Memory leaks can't test that remotely
    *tests_passed += 1;
    return test_number;
}


int addUserTest(MtmFlix m, int* tests_passed){
    _print_mode_name("Testing addUser functions");
    int test_number = 0;
    test(mtmFlixAddUser(NULL,"user",10) != MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_NULL_ARGUMENT on NULL mtmflix input.", tests_passed);
    test(mtmFlixAddUser(m, NULL,10) != MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_NULL_ARGUMENT on NULL username input.", tests_passed);
    test(mtmFlixAddUser(m, "user",MTM_MAX_AGE+1) != MTMFLIX_ILLEGAL_AGE,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_ILLEGAL_AGE on age bigger than MAX_AGE input.", tests_passed);
    test(mtmFlixAddUser(m, "UserOne",MTM_MAX_AGE) == MTMFLIX_ILLEGAL_AGE,__LINE__, &test_number, "mtmFlixAddUser doesnt' allow MTM_MAX_AGE.", tests_passed);
    test(mtmFlixAddUser(m, "UserTwo",MTM_MIN_AGE-1) != MTMFLIX_ILLEGAL_AGE,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_ILLEGAL_AGE on age smaller than MIN_AGE input.", tests_passed);
    test(mtmFlixAddUser(m, "UserThree",MTM_MIN_AGE) == MTMFLIX_ILLEGAL_AGE,__LINE__, &test_number, "mtmFlixAddUser doesnt' allow MTM_MAX_AGE", tests_passed);
    test(mtmFlixAddUser(m,"!user",10) != MTMFLIX_ILLEGAL_USERNAME,__LINE__, &test_number, "mtmFlixAddUser allows invalid username (symbol)", tests_passed);
    test(mtmFlixAddUser(m,"u ser",10) != MTMFLIX_ILLEGAL_USERNAME,__LINE__, &test_number, "mtmFlixAddUser allows invalid username (space)", tests_passed);
    test(mtmFlixAddUser(m,"",10) != MTMFLIX_ILLEGAL_USERNAME,__LINE__, &test_number, "mtmFlixAddUser allows invalid username (empty)", tests_passed);
    test(mtmFlixAddUser(m, "user",MTM_MIN_AGE) != MTMFLIX_SUCCESS,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_SUCCESS on correct input (lowercase name).", tests_passed);
    test(mtmFlixAddUser(m, "USER",MTM_MIN_AGE) != MTMFLIX_SUCCESS,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_SUCCESS on correct input (uppercase name).", tests_passed);
    test(mtmFlixAddUser(m, "user",MTM_MIN_AGE+1) != MTMFLIX_USERNAME_ALREADY_USED,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_USERNAME_ALREADY_USED.", tests_passed);
    //Next block of  tests check for right order of error return status
    test(mtmFlixAddUser(NULL, NULL,MTM_MIN_AGE+1) != MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_NULL_ARGUMENT on two NULL inputs and invalid age", tests_passed);
    test(mtmFlixAddUser(m, NULL,MTM_MIN_AGE+1) != MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_NULL_ARGUMENT on NULL username and invalid age", tests_passed);
    test(mtmFlixAddUser(m, "",MTM_MIN_AGE+1) != MTMFLIX_ILLEGAL_USERNAME,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_NULL_ARGUMENT on wrong username and invalid age", tests_passed);
    test(mtmFlixAddUser(m, "user",MTM_MIN_AGE-1) != MTMFLIX_USERNAME_ALREADY_USED,__LINE__, &test_number, "mtmFlixAddUser doesn't return MTMFLIX_USERNAME_ALREADY_USED + incorrect age.", tests_passed);
    return test_number;
}

int removeUserTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing removeUser functions");
    int test_number = 0;
    test(mtmFlixRemoveUser(NULL,"user") != MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixRemoveUser doesn't return MTMFLIX_NULL_ARGUMENT on NULL input", tests_passed);
    test(mtmFlixRemoveUser(m, NULL) != MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixRemoveUser doesn't return MTMFLIX_NULL_ARGUMENT on NULL input", tests_passed);
    test(mtmFlixRemoveUser(m, "") != MTMFLIX_USER_DOES_NOT_EXIST,__LINE__, &test_number, "mtmFlixRemoveUser doesn't return MTMFLIX_USER_DOES_NOT_EXIST on wrong username", tests_passed);
    test(mtmFlixRemoveUser(m, "") != MTMFLIX_USER_DOES_NOT_EXIST,__LINE__, &test_number, "mtmFlixRemoveUser doesn't return MTMFLIX_USER_DOES_NOT_EXIST on" , tests_passed);     //this test checks if the function is case-sensitive
    test(mtmFlixRemoveUser(m, "User") != MTMFLIX_USER_DOES_NOT_EXIST,__LINE__, &test_number, "mtmFlixRemoveUser doesn't return USER_DOES_NOT_EXIST on uppercase of existing user", tests_passed);
    test(mtmFlixRemoveUser(m, "User") != MTMFLIX_USER_DOES_NOT_EXIST,__LINE__, &test_number, "mtmFlixRemoveUser doesn't return USER_DOES_NOT_EXIST on uppercase of existing user", tests_passed);
    test(mtmFlixRemoveUser(m, "user") != MTMFLIX_SUCCESS,__LINE__, &test_number, "mtmFlixRemoveUser doesn't return MTMFLIX_SUCCESS on successful remove", tests_passed);
    test(mtmFlixRemoveUser(m, "user") != MTMFLIX_USER_DOES_NOT_EXIST,__LINE__, &test_number, "mtmFlixRemoveUser doesn't return MTMFLIX_USER_DOES_NOT_EXIST when trying to remove already removed user.", tests_passed);
    return test_number;
}

int addSeriesTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing addSeries functions");
    int test_number = 0;
    int ages[2] = {MTM_MIN_AGE-1, MTM_MAX_AGE+1};
    int limits[2] = {MTM_MIN_AGE, MTM_MAX_AGE};
    test(mtmFlixAddSeries(NULL, "Series1",1,COMEDY,ages, 40) !=MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_NULL_ARGUMENT on NULL input.", tests_passed);
    test(mtmFlixAddSeries(m, NULL,1,COMEDY,ages, 40) !=MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_NULL_ARGUMENT on NULL series name input.", tests_passed);
    test(mtmFlixAddSeries(m, "Series#", 1, COMEDY, limits, 40) !=MTMFLIX_ILLEGAL_SERIES_NAME, __LINE__, &test_number, "mtmFlixAddSeries doesn't retujrn MTMFLIX_ILLEGAL_SERIES_NAME on wrong imput(symbol)", tests_passed);
    test(mtmFlixAddSeries(m, "Series 1", 1, COMEDY, limits, 40) !=MTMFLIX_ILLEGAL_SERIES_NAME, __LINE__, &test_number, "mtmFlixAddSeries doesn't retujrn MTMFLIX_ILLEGAL_SERIES_NAME on wrong imput(spaces)", tests_passed);
    test(mtmFlixAddSeries(m, "Series1",0,COMEDY,ages, 40) !=MTMFLIX_ILLEGAL_EPISODES_NUM,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_ILLEGAL_EPISODES_NUM on 0 input.", tests_passed);
    test(mtmFlixAddSeries(m, "Series1",-1,COMEDY,ages, 40) !=MTMFLIX_ILLEGAL_EPISODES_NUM,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_ILLEGAL_EPISODES_NUM on negative input.", tests_passed);
    test(mtmFlixAddSeries(m, "Series1",1,COMEDY,ages, 0) !=MTMFLIX_ILLEGAL_EPISODES_DURATION,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_ILLEGAL_EPISODES_DURATION on 0 input.", tests_passed);
    test(mtmFlixAddSeries(m, "Series1",1,COMEDY,ages, -1) !=MTMFLIX_ILLEGAL_EPISODES_DURATION,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_ILLEGAL_EPISODES_DURATION on negative input.", tests_passed);
    test(mtmFlixAddSeries(m, "Series1",1,COMEDY,NULL, 40) !=MTMFLIX_SUCCESS,__LINE__, &test_number, "mtmFlixAddSeries doesn't allow NULL as age input.", tests_passed);
    test(mtmFlixAddSeries(m, "Series1",1,COMEDY,NULL, 40) !=MTMFLIX_SERIES_ALREADY_EXISTS,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_SERIES_ALREADY_EXISTS.", tests_passed);
    test(mtmFlixAddSeries(m, "Series2", 1, COMEDY, limits, 40) !=MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixAddSeries doesn't add series with ages set as MAX/MIN age.", tests_passed);
    //Next block of  tests check for right order of error return status
    test(mtmFlixAddSeries(NULL, NULL,0,COMEDY,ages, 0) !=MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_NULL_ARGUMENT on all wrong input", tests_passed);
    test(mtmFlixAddSeries(m, NULL,0,COMEDY,ages, 0) !=MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_NULL_ARGUMENT on all wrong input", tests_passed);
    test(mtmFlixAddSeries(m, "Series1",0,COMEDY,ages, 0) !=MTMFLIX_SERIES_ALREADY_EXISTS,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_SERIES_ALREADY_EXISTS on serie which exists and wrong episode number/duration", tests_passed);
    test(mtmFlixAddSeries(m, "Series3",0,COMEDY,ages, 0) !=MTMFLIX_ILLEGAL_EPISODES_NUM,__LINE__, &test_number, "mtmFlixAddSeries doesn't return MTMFLIX_ILLEGAL_EPISODES_NUM  on wrong episode number/duration", tests_passed);
    return test_number;
}


int removeSeriesTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing removeSeries functions");
    int test_number = 0;
    test(mtmFlixRemoveSeries(NULL, "Series1") != MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixRemoveSeries doesn't return MTMFLIX_NULL_ARGUMENT on NULL mtmflix input.", tests_passed);
    test(mtmFlixRemoveSeries(m, NULL) != MTMFLIX_NULL_ARGUMENT,__LINE__, &test_number, "mtmFlixRemoveSeries doesn't return MTMFLIX_NULL_ARGUMENT on NULL name input.", tests_passed);
    test(mtmFlixRemoveSeries(m, "1seireS") != MTMFLIX_SERIES_DOES_NOT_EXIST,__LINE__, &test_number, "mtmFlixRemoveSeries doesn't return MTMFLIX_SERIES_DOES_NOT_EXIST.", tests_passed);
    test(mtmFlixRemoveSeries(m, "Series1") != MTMFLIX_SUCCESS,__LINE__, &test_number, "mtmFlixRemoveSeries doesn't return MTMFLIX_SUCCESS on successful remove.", tests_passed);
    test(mtmFlixRemoveSeries(m, "Series1") == MTMFLIX_SUCCESS,__LINE__, &test_number, "mtmFlixRemoveSeries return MTMFLIX_SUCCESS on already removed series.", tests_passed);
    return test_number;
}

int reportSeriesTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing reportSeries functions");
    int test_number = 0;
    //Those test aren't testing the output, output tests will be in separate test_input.exe file
    test(mtmFlixReportSeries(NULL, 1, stdout) != MTMFLIX_NULL_ARGUMENT ,__LINE__, &test_number, "mtmFlixReportSeries doesn't return MTMFLIX_NULL_ARGUMENT on null mtmflix input.", tests_passed);
    test(mtmFlixReportSeries(m, 1, NULL) != MTMFLIX_NULL_ARGUMENT ,__LINE__, &test_number, "mtmFlixReportSeries doesn't return MTMFLIX_NULL_ARGUMENT on null FPTR input.", tests_passed);
    MtmFlix m_temp = mtmFlixCreate();
    test(mtmFlixReportSeries(m_temp, 1, stdout) != MTMFLIX_NO_SERIES, __LINE__, &test_number, "mtmFlixReportSeries doesn't return MTMFLIX_NO_SERIES on empty mtmflix input.", tests_passed);
    mtmFlixDestroy(m_temp);
    // in the next test i chose stderr so it won't appear in the console
    FILE* fptr = fopen("garbage.txt", "w");
    test(mtmFlixReportSeries(m, 1, fptr) != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixReportSeries doesn't return MTMFLIX_SUCCESS on valid input.", tests_passed);
    fclose(fptr);
    return test_number;
}

int reportUsersTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing reportUsers functions");
    int test_number = 0;
    //Those test aren't testing the output, output tests will be in separate test_input.exe file
    test(mtmFlixReportUsers(NULL,  stdout) != MTMFLIX_NULL_ARGUMENT ,__LINE__, &test_number, "mtmFlixReportUsers doesn't return MTMFLIX_NULL_ARGUMENT on null mtmflix input.", tests_passed);
    test(mtmFlixReportUsers(m,  NULL) != MTMFLIX_NULL_ARGUMENT ,__LINE__, &test_number, "mtmFlixReportUsers doesn't return MTMFLIX_NULL_ARGUMENT on null FPTR input.", tests_passed);
    MtmFlix m_temp = mtmFlixCreate();
    test(mtmFlixReportUsers(m_temp,  stdout) != MTMFLIX_NO_USERS, __LINE__, &test_number, "mtmFlixReportUsers doesn't return MTMFLIX_NO_USERS on empty mtmflix input.", tests_passed);
    mtmFlixDestroy(m_temp);
    // in the next test i chose stderr so it won't appear in the console
    FILE* fptr = fopen("garbage.txt", "w");
    test(mtmFlixReportUsers(m,  fptr) != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixReportUsers doesn't return MTMFLIX_SUCCESS on valid input.", tests_passed);
    fclose(fptr);
    return test_number;
}

int seriesJoinTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing seriesJoin functions");
    int test_number = 0;
    mtmFlixAddUser(m, "UserTwo", MTM_MIN_AGE+1); //Assuming u've passed previous tests this should work
    test(mtmFlixSeriesJoin(NULL,"UserTwo", "Series2") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_NULL_ARGUMENT on NULL mtmflix input.", tests_passed);
    test(mtmFlixSeriesJoin(m, NULL, "Series2") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_NULL_ARGUMENT on NULL user name input.", tests_passed);
    test(mtmFlixSeriesJoin(m,"UserTwo", NULL) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_NULL_ARGUMENT on NULL series name input.", tests_passed);
//    test(mtmFlixSeriesJoin(m,"UserT", "Series2") != MTMFLIX_USER_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_USER_DOES_NOT_EXIST on not existing series name input.", tests_passed);
    test(mtmFlixSeriesJoin(m,"UserTwo", "2Series") != MTMFLIX_SERIES_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_SERIES_DOES_NOT_EXIST on not existing user input.", tests_passed);
    int ages[2] = {MTM_MAX_AGE-1, MTM_MAX_AGE};
    mtmFlixAddSeries(m, "MaxAge", 1, COMEDY, ages,40);
    int ages1[2] = {MTM_MIN_AGE+1, MTM_MIN_AGE+2};
    mtmFlixAddSeries(m, "MinAge", 1, COMEDY, ages1,40);
    test(mtmFlixSeriesJoin(m, "UserTwo", "MaxAge") != MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE on user who doesn't fit into series age limit.", tests_passed);
    test(mtmFlixSeriesJoin(m, "UserTwo", "MinAge") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_SUCCESS on valid input.", tests_passed);
    //Next block of  tests check for right order of error return status
    test(mtmFlixSeriesJoin(NULL, "User15", "Series15") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_NULL_ARGUMENT when everything is wrong", tests_passed);
    test(mtmFlixSeriesJoin(m, "User15", "Series15") != MTMFLIX_USER_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixSeriesJoin doesn't return MTMFLIX_SERIES_DOES_NOT_EXIST on series/user doesn't exist ", tests_passed);
    return test_number;
}

int seriesLeaveTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing seriesLeave functions");
    int test_number = 0;
    test( mtmFlixSeriesLeave(NULL, "UserTwo", "MinAge") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixSeriesLeave doesn't return MTMFLIX_NULL_ARGUMENT on NULL mtmflix input.", tests_passed);
    test( mtmFlixSeriesLeave(m, NULL, "MinAge") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixSeriesLeave doesn't return MTMFLIX_NULL_ARGUMENT on NULL user name input.", tests_passed);
    test( mtmFlixSeriesLeave(m, "UserTwo", NULL) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixSeriesLeave doesn't return MTMFLIX_NULL_ARGUMENT on NULL series name input.", tests_passed);
    test( mtmFlixSeriesLeave(m, "UserTo", "MinAge") != MTMFLIX_USER_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixSeriesLeave doesn't return MTMFLIX_USER_DOES_NOT_EXIST on non existing user input.", tests_passed);
    test( mtmFlixSeriesLeave(m, "UserTwo", "MiAge") != MTMFLIX_SERIES_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixSeriesLeave doesn't return MTMFLIX_SERIES_DOES_NOT_EXIST on on non existing series input.", tests_passed);
    test( mtmFlixSeriesLeave(m, "UserTwo", "MinAge") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixSeriesLeave doesn't return MTMFLIX_SUCCESS on valid input.", tests_passed);
    test( mtmFlixSeriesLeave(m, "UserTwo", "MinAge") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixSeriesLeave doesn't return MTMFLIX_SUCCESS on leaving series.", tests_passed);
    test( mtmFlixSeriesLeave(m, "UserTwo", "MinAge") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixSeriesLeave doesn't return MTMFLIX_SUCCESS on leaving series which is not in his list.", tests_passed);
    return test_number;
}

int addFriendTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing addFriend functions");
    int test_number = 0;
    test(mtmFlixAddFriend(NULL,"UserTwo", "UserThree") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixAddFriend doesn't return MTMFLIX_NULL_ARGUMENT on NULL mtmflix input.", tests_passed);
    test(mtmFlixAddFriend(m, NULL, "UserThree") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixAddFriend doesn't return MTMFLIX_NULL_ARGUMENT on NULL username1 input.", tests_passed);
    test(mtmFlixAddFriend(m,"UserTwo", NULL) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixAddFriend doesn't return MTMFLIX_NULL_ARGUMENT on NULL username2 input.", tests_passed);
    test(mtmFlixAddFriend(m,"UserTo", "UserTwo") != MTMFLIX_USER_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixAddFriend doesn't return MTMFLIX_USER_DOES_NOT_EXIST on non existing username1 input.", tests_passed);
    test(mtmFlixAddFriend(m,"UserTwo", "UserTo") != MTMFLIX_USER_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixAddFriend doesn't return MTMFLIX_USER_DOES_NOT_EXIST on non existing username1 input.", tests_passed);
    mtmFlixAddUser(m, "NewUser", 25);
    test(mtmFlixAddFriend(m, "NewUser", "NewUser") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixAddFriends doesn't return MTMFLIX_SUCCESS when the user adds himself as a friend(nothing should happend but the status should be MTMFLIX_SUCCESS)", tests_passed);
    test(mtmFlixAddFriend(m, "UserTwo", "NewUser") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixAddFriend doesn't return MTMFLIX_SUCCESS on valid input.", tests_passed);
    test(mtmFlixAddFriend(m, "UserTwo", "NewUser") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixAddFriend doesn't return MTMFLIX_SUCCESS on when adding a friends which already exists.", tests_passed);
    return test_number;
}

int removeFriendTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing removeFriend functions");
    int test_number = 0;
    test(mtmFlixRemoveFriend(NULL, "UserTwo", "NewUser") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixRemoveFriend doesn't return MTMFLIX_NULL_ARGUMENT on NULL mtmflix input.", tests_passed);
    test(mtmFlixRemoveFriend(m, NULL, "NewUser") != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixRemoveFriend doesn't return MTMFLIX_NULL_ARGUMENT on NULL username1 input.", tests_passed);
    test(mtmFlixRemoveFriend(m, "UserTwo", NULL) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixRemoveFriend doesn't return MTMFLIX_NULL_ARGUMENT on NULL username2 input.", tests_passed);
    test(mtmFlixRemoveFriend(m, "UserTwo", "NewUser") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixRemoveFriend doesn't return MTMFLIX_SUCCESS on valid input.", tests_passed);
    test(mtmFlixRemoveFriend(m, "UserTwo", "NewUser") != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixRemoveFriend doesn't return MTMFLIX_SUCCESS on when removing a friend which already had been removed.", tests_passed);
    return test_number;
}

int getRecommendationsTest(MtmFlix m,int* tests_passed){
    _print_mode_name("Testing getRecommendations functions");
    int test_number = 0;
    test(mtmFlixGetRecommendations(NULL, "UserTwo", 1, stdout) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_NULL_ARGUMENT on NULL mtmflix input.", tests_passed);
    test(mtmFlixGetRecommendations(m, NULL, 1, stdout) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_NULL_ARGUMENT on NULL username input.", tests_passed);
    test(mtmFlixGetRecommendations(m, "UserTwo", 1, NULL) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_NULL_ARGUMENT on NULL FPTR input.", tests_passed);
    test(mtmFlixGetRecommendations(m, "UserTo", 1, stdout) != MTMFLIX_USER_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_USER_DOES_NOT_EXIST on non existing user.", tests_passed);
    test(mtmFlixGetRecommendations(m, "UserTwo", -1, stdout) != MTMFLIX_ILLEGAL_NUMBER, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_ILLEGAL_NUMBER on negative count input.", tests_passed);
    //Next block of  tests check for right order of error return status
    test(mtmFlixGetRecommendations(NULL, "UserTo", -1, stdout) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_NULL_ARGUMENT on NULL mtmflix ,not existing user and illegal count", tests_passed);
    test(mtmFlixGetRecommendations(m, "UserTo", -1, NULL) != MTMFLIX_NULL_ARGUMENT, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_NULL_ARGUMENT on NULL FPTR ,not existing user and illegal count", tests_passed);
    test(mtmFlixGetRecommendations(m, "UserTo", -1, stdout) != MTMFLIX_USER_DOES_NOT_EXIST, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_USER_DOES_NOT_EXIST on none existing user and illegal count", tests_passed);
    FILE* fptr = fopen("garbage.txt", "w");
    test(mtmFlixGetRecommendations(m, "UserTwo", 0, fptr) != MTMFLIX_SUCCESS, __LINE__, &test_number, "mtmFlixGetRecommendations doesn't return MTMFLIX_SUCCESS on valid input.", tests_passed);
    fclose(fptr);
    return test_number;
}

/* Target: Wonderful. */

void test1_again(FILE *f1) {
    fprintf(f1, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Test 1..\n");
    MtmFlix a = mtmFlixCreate();
    int ages1[2] = {20, 80};
    printf("Using ages %d %d\n", ages1[0], ages1[0]);
    assert(a);
    assert(mtmFlixAddSeries(a, "s 1", 5, DRAMA, ages1, 20) == MTMFLIX_ILLEGAL_SERIES_NAME);
    assert(mtmFlixAddSeries(a, "s1", 0, DRAMA, ages1, 20) == MTMFLIX_ILLEGAL_EPISODES_NUM);
    assert(mtmFlixAddSeries(a, "s1", 5, DRAMA, ages1, 0) == MTMFLIX_ILLEGAL_EPISODES_DURATION);
    assert(mtmFlixAddSeries(a, "s 1", -5, DRAMA, ages1, -5) == MTMFLIX_ILLEGAL_SERIES_NAME);
    assert(mtmFlixAddSeries(a, "s1", 5, SCIENCE_FICTION, ages1, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s1", 5, DRAMA, NULL, 20) == MTMFLIX_SERIES_ALREADY_EXISTS);

    assert(mtmFlixAddUser(a, "u1", MTM_MIN_AGE - 1) == MTMFLIX_ILLEGAL_AGE);
    assert(mtmFlixAddUser(a, "u1", MTM_MAX_AGE + 1) == MTMFLIX_ILLEGAL_AGE);
    assert(mtmFlixAddUser(a, "u1", 25) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u1", 33) == MTMFLIX_USERNAME_ALREADY_USED);
    assert(mtmFlixAddFriend(a, "u1", "b") == MTMFLIX_USER_DOES_NOT_EXIST);
    assert(mtmFlixAddFriend(a, "b", "u1") == MTMFLIX_USER_DOES_NOT_EXIST);
    assert(mtmFlixAddUser(a, "u2", 6) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixRemoveFriend(a, "u1", "b") == MTMFLIX_USER_DOES_NOT_EXIST);
    assert(mtmFlixRemoveFriend(a, "b", "u1") == MTMFLIX_USER_DOES_NOT_EXIST);
    assert(mtmFlixRemoveFriend(a, "u1", "u2") == MTMFLIX_SUCCESS);

    assert(mtmFlixSeriesJoin(a, "u1", "b") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    assert(mtmFlixSeriesJoin(a, "b", "s1") == MTMFLIX_USER_DOES_NOT_EXIST);
    assert(mtmFlixSeriesJoin(a, "b", "b") == MTMFLIX_USER_DOES_NOT_EXIST);
    assert(mtmFlixSeriesJoin(a, "u2", "s1") == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE);
    assert(mtmFlixSeriesJoin(a, "u1", "s1") == MTMFLIX_SUCCESS);

    assert(mtmFlixAddSeries(a, "s0", 5, SCIENCE_FICTION, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s4", 5, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s3", 5, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s2", 5, COMEDY, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s5", 5, HORROR, NULL, 20) == MTMFLIX_SUCCESS);

    assert(mtmFlixReportSeries(a, 2, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-\n");
    assert(mtmFlixReportSeries(a, 1, f1) == MTMFLIX_SUCCESS);

    assert(mtmFlixSeriesJoin(a, "u2", "s4") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s3") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s2") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s5") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u2", "u1") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s2") == MTMFLIX_SUCCESS);

    assert(mtmFlixReportUsers(a, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 1:\n");
    assert(mtmFlixGetRecommendations(a, "u1", 8, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 2:\n");
    assert(mtmFlixGetRecommendations(a, "u2", 8, f1) == MTMFLIX_SUCCESS);

    assert(mtmFlixSeriesLeave(a, "u1", "s1") == MTMFLIX_SUCCESS);
    assert(mtmFlixRemoveSeries(a, "s1") == MTMFLIX_SUCCESS);
    assert(mtmFlixRemoveSeries(a, "s1") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    assert(mtmFlixRemoveUser(a, "u1") == MTMFLIX_SUCCESS);
    assert(mtmFlixRemoveUser(a, "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixRemoveUser(a, "u1") == MTMFLIX_USER_DOES_NOT_EXIST);

    assert(mtmFlixReportUsers(a, f1) == MTMFLIX_NO_USERS);
    mtmFlixDestroy(a);
}

void test2_again(FILE *f1) {
    fprintf(f1, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Test 2..\n");
    MtmFlix a = mtmFlixCreate();
    assert(a);

    assert(mtmFlixAddUser(a, "u1", 25) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u2", 6) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u3", 6) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u4", 6) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u2", "u1") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u3") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u4") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u3", "u4") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u3", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u3", "u1") == MTMFLIX_SUCCESS);

    assert(mtmFlixAddSeries(a, "s1", 5, SCIENCE_FICTION, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s0", 5, SCIENCE_FICTION, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s4", 5, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s6", 5, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s2", 5, COMEDY, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s5", 5, HORROR, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s3", 5, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s7", 5, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s8", 5, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s9", 5, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);

    assert(mtmFlixSeriesJoin(a, "u1", "s1") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s4") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s6") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s2") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s9") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s8") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s0") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s3") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s5") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s4") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s6") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s2") == MTMFLIX_SUCCESS);

    assert(mtmFlixReportUsers(a, f1) == MTMFLIX_SUCCESS);
    assert(mtmFlixGetRecommendations(a, "u1", -2, f1) == MTMFLIX_ILLEGAL_NUMBER);
    assert(mtmFlixGetRecommendations(a, "u0", 0, f1) == MTMFLIX_USER_DOES_NOT_EXIST);
    assert(mtmFlixGetRecommendations(NULL, "u1", 0, f1) == MTMFLIX_NULL_ARGUMENT);
    assert(mtmFlixGetRecommendations(a, "u1", 0, NULL) == MTMFLIX_NULL_ARGUMENT);
    fprintf(f1, "-User 1:\n");
    assert(mtmFlixGetRecommendations(a, "u1", 0, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 2:\n");
    assert(mtmFlixGetRecommendations(a, "u2", 0, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 3:\n");
    assert(mtmFlixGetRecommendations(a, "u3", 0, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 4:\n");
    assert(mtmFlixGetRecommendations(a, "u4", 0, f1) == MTMFLIX_SUCCESS);

    mtmFlixDestroy(a);
}

void test3_again(FILE *f1) {
    fprintf(f1, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Test 3..\n");
    MtmFlix a = mtmFlixCreate();
    assert(a);
    int ages[2] = {22, 55};
    printf("Using ages: %d %d\n", ages[0], ages[1]);
    assert(mtmFlixAddUser(a, "u1", 25) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u2", 6) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u3", 6) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u4", 6) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u5", 6) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddUser(a, "u6", 70) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u2", "u1") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u3") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u4") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u3", "u4") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u5", "u4") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u5", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u5", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u3", "u6") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u6", "u1") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u6", "u4") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u3", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u5", "u1") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u6", "u2") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u1", "u6") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u3", "u1") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u6", "u5") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u6", "u3") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u3", "u5") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u5", "u3") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u5", "u6") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u2", "u4") == MTMFLIX_SUCCESS);
    assert(mtmFlixAddFriend(a, "u2", "u6") == MTMFLIX_SUCCESS);

    assert(mtmFlixAddSeries(a, "s1", 13, ROMANCE, NULL, 28) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s0", 25, ROMANCE, NULL, 30) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s4", 5, ROMANCE, ages, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s3", 15, ROMANCE, NULL, 30) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s2", 15, COMEDY, NULL, 29) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s5", 5, HORROR, NULL, 30) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s6", 15, ROMANCE, NULL, 28) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s7", 5, ROMANCE, NULL, 39) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s8", 15, ROMANCE, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s9", 5, ROMANCE, NULL, 42) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s10", 14, COMEDY, NULL, 25) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s12", 12, COMEDY, NULL, 45) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s13", 11, DRAMA, NULL, 34) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s14", 66, DRAMA, NULL, 37) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s15", 44, DOCUMENTARY, NULL, 37) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s16", 68, DOCUMENTARY, NULL, 29) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s17", 13, DOCUMENTARY, NULL, 24) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s21", 10, DOCUMENTARY, NULL, 21) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s22", 12, DOCUMENTARY, NULL, 43) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s23", 16, DOCUMENTARY, NULL, 45) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s24", 18, DOCUMENTARY, NULL, 29) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s25", 125, HORROR, NULL, 40) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s26", 1, HORROR, NULL, 21) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s27", 16, HORROR, NULL, 41) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s28", 18, HORROR, NULL, 43) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s29", 164, HORROR, NULL, 25) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s20", 44, HORROR, NULL, 20) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s18", 34, COMEDY, NULL, 33) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s19", 13, COMEDY, NULL, 25) == MTMFLIX_SUCCESS);
    assert(mtmFlixAddSeries(a, "s11", 22, COMEDY, NULL, 32) == MTMFLIX_SUCCESS);

    assert(mtmFlixSeriesJoin(a, "u2", "s19") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s11") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s19") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s18") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s4") == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE);
    assert(mtmFlixSeriesJoin(a, "u2", "s3") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s2") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s9") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s8") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s7") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s6") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s5") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s4") == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE);
    assert(mtmFlixSeriesJoin(a, "u4", "s3") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s2") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u5", "s10") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s10") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u5", "s12") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s13") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s14") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u5", "s15") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s16") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s17") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s15") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s13") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s12") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u5", "s17") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s14") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s12") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s10") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u5", "s10") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s12") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u5", "s13") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s14") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s15") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s16") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s17") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s15") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s13") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u5", "s12") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s17") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s14") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s12") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s20") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s20") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s21") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s22") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s22") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s23") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s23") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u5", "s24") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s24") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s25") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s25") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s26") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s26") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s27") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u2", "s28") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s29") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s27") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s28") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s29") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s1") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s2") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s5") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s8") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s9") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s25") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s13") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s11") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s28") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s5") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s14") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s18") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s19") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u4", "s20") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s5") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u6", "s8") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u3", "s12") == MTMFLIX_SUCCESS);
    assert(mtmFlixSeriesJoin(a, "u1", "s7") == MTMFLIX_SUCCESS);

    assert(mtmFlixRemoveSeries(a, "s18") == MTMFLIX_SUCCESS);
    assert(mtmFlixRemoveUser(a, "u1") == MTMFLIX_SUCCESS);

    //Use this while Debugging
    //assert(mtmFlixReportUsers(a, stdout) == MTMFLIX_SUCCESS);

    assert(mtmFlixGetRecommendations(a, "u1", 0, f1) == MTMFLIX_USER_DOES_NOT_EXIST);
    fprintf(f1, "-User 2:\n");
    assert(mtmFlixGetRecommendations(a, "u2", 0, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 3:\n");
    assert(mtmFlixGetRecommendations(a, "u3", 0, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 4:\n");
    assert(mtmFlixGetRecommendations(a, "u4", 0, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 5:\n");
    assert(mtmFlixGetRecommendations(a, "u5", 1, f1) == MTMFLIX_SUCCESS);
    fprintf(f1, "-User 6:\n");
    assert(mtmFlixGetRecommendations(a, "u6", 4, f1) == MTMFLIX_SUCCESS);

    mtmFlixDestroy(a);
}

void finalCheck() {
    printf("Final Check..\n--\n");
    char *string = "\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "Series 's2', Genre: COMEDY.\n"
                   "Series 's5', Genre: HORROR.\n"
                   "Series 's3', Genre: ROMANCE.\n"
                   "Series 's4', Genre: ROMANCE.\n"
                   "Series 's0', Genre: SCIENCE_FICTION.\n"
                   "Series 's1', Genre: SCIENCE_FICTION.\n"
                   "-\n"
                   "Series 's2', Genre: COMEDY.\n"
                   "Series 's5', Genre: HORROR.\n"
                   "Series 's3', Genre: ROMANCE.\n"
                   "Series 's0', Genre: SCIENCE_FICTION.\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "The user u1 is 25 years old\n"
                   "Friend: u2\n"
                   "Series: s1\n"
                   "Series: s2\n"
                   "Series: s5\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "The user u2 is 6 years old\n"
                   "Friend: u1\n"
                   "Series: s2\n"
                   "Series: s3\n"
                   "Series: s4\n"
                   "-User 1:\n"
                   "-User 2:\n"
                   "\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST 2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "The user u1 is 25 years old\n"
                   "Friend: u2\n"
                   "Friend: u3\n"
                   "Friend: u4\n"
                   "Series: s1\n"
                   "Series: s2\n"
                   "Series: s5\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "The user u2 is 6 years old\n"
                   "Friend: u1\n"
                   "Series: s2\n"
                   "Series: s3\n"
                   "Series: s4\n"
                   "Series: s6\n"
                   "Series: s9\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "The user u3 is 6 years old\n"
                   "Friend: u1\n"
                   "Friend: u2\n"
                   "Friend: u4\n"
                   "Series: s4\n"
                   "Series: s8\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "The user u4 is 6 years old\n"
                   "Series: s0\n"
                   "Series: s6\n"
                   "-User 1:\n"
                   "Series 's0', Genre: SCIENCE_FICTION.\n"
                   "-User 2:\n"
                   "-User 3:\n"
                   "Series 's6', Genre: ROMANCE.\n"
                   "Series 's3', Genre: ROMANCE.\n"
                   "Series 's9', Genre: ROMANCE.\n"
                   "-User 4:\n"
                   "\n"
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                   "-User 2:\n"
                   "Series 's5', Genre: HORROR.\n"
                   "-User 3:\n"
                   "Series 's5', Genre: HORROR.\n"
                   "Series 's11', Genre: COMEDY.\n"
                   "Series 's15', Genre: DOCUMENTARY.\n"
                   "Series 's24', Genre: DOCUMENTARY.\n"
                   "-User 4:\n"
                   "-User 5:\n"
                   "Series 's11', Genre: COMEDY.\n"
                   "-User 6:\n"
                   "Series 's11', Genre: COMEDY.\n"
                   "Series 's16', Genre: DOCUMENTARY.\n"
                   "Series 's17', Genre: DOCUMENTARY.\n"
                   "Series 's2', Genre: COMEDY.";
    FILE *f1 = fopen("OutputFileFromTest", "r");
    assert(f1);

    int line = 1, ch1 = getc(f1);
    char *error = string;
    while (*string != '\0') {
        if ((ch1 != *string)) {
            printf("Fail in OutputFileFromTest line %d. Details:\n", line);
            printf("Mismatch with the string at line: %d:\n\"", (__LINE__ - 89 + line));
            while (*error != '\n') {
                printf("%c", *error);
                ++error;
            }
            printf("\"\nIn file: -(%s)-\n", __FILE__);
            return;
        }
        ch1 = getc(f1);
        ++string;
        if (ch1 == '\n') {
            error = 1 + string;
            ++line;
        }
    }
    ch1 = getc(f1);
    fclose(f1);
    if (ch1 != EOF) {
        printf("Your OutputFileFromTest is too long?\n");
        return;
    }
    printf("Wonderful(:\n");
}

bool mtmFlixUnitTest() {
    printf("\n");
    RUN_TEST(mtmFlixCreateTest);
    RUN_TEST(mtmflixAddUserTest);
    RUN_TEST(mtmFlixRemoveUserTest);
    RUN_TEST(mtmFlixAddSeriesTest);
    RUN_TEST(mtmFlixRemoveSeriesTest);
    RUN_TEST(mtmFlixReportSeriesTest);
    RUN_TEST(mtmFlixReportUsersTest);
    RUN_TEST(mtmFlixSeriesJoinTest);
    RUN_TEST(mtmFlixSeriesLeaveTest);
    RUN_TEST(mtmFlixAddFriendTest);
    RUN_TEST(mtmFlixRemoveFriendTest);
    RUN_TEST(mtmFlixGetRecommendationsTest);
    RUN_TEST(mtmFlixRemoveUserTestAdvanced);
    RUN_TEST(mtmFlixRemoveSeriesTestAdvanced);

//    MessageBox(NULL, "I don't know about the code, but are you sure your style is good?\n\n"
//                     "https://xkcd.com/1695/", "Real Windows dialogue", 4);
    return true;
}

bool mtmFlixCreateTest() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixDestroy(system);
    return true;
}

bool mtmflixAddUserTest() {
    MtmFlix system = mtmFlixCreate();
    // Null values
    ASSERT_TEST(mtmFlixAddUser(NULL, "Chandler", 23) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddUser(system, NULL, 23) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddUser(NULL, "@lon", 23) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddUser(system, NULL, -3) == MTMFLIX_NULL_ARGUMENT);
    // Name tests
    ASSERT_TEST(mtmFlixAddUser(system, "Chandler", 23) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Chandler123", 23) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "321Chandler09", 23) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Chandler!", 23) == MTMFLIX_ILLEGAL_USERNAME);
    ASSERT_TEST(mtmFlixAddUser(system, "Al~n", 23) == MTMFLIX_ILLEGAL_USERNAME);
    ASSERT_TEST(mtmFlixAddUser(system, "", 23) == MTMFLIX_ILLEGAL_USERNAME);
    ASSERT_TEST(mtmFlixAddUser(system, "Chandler!", -8) == MTMFLIX_ILLEGAL_USERNAME);
    // User already exists
    mtmFlixAddUser(system, "Monica", 30);
    ASSERT_TEST(mtmFlixAddUser(system, "Monica", 31) == MTMFLIX_USERNAME_ALREADY_USED);
    ASSERT_TEST(mtmFlixAddUser(system, "Monica", -6) == MTMFLIX_USERNAME_ALREADY_USED);
    // Age tests
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel", 22) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel2", MTM_MAX_AGE) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel3", MTM_MIN_AGE) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel4", MTM_MAX_AGE + 1) == MTMFLIX_ILLEGAL_AGE);
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel5", MTM_MIN_AGE - 1) == MTMFLIX_ILLEGAL_AGE);
    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixRemoveUserTest() {
    MtmFlix system = mtmFlixCreate();
    // Null values
    ASSERT_TEST(mtmFlixRemoveUser(NULL, "Chandler") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveUser(system, NULL) == MTMFLIX_NULL_ARGUMENT);
    // User tests
    ASSERT_TEST(mtmFlixRemoveUser(system, "Joey") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveUser(system, "") == MTMFLIX_USER_DOES_NOT_EXIST);
    mtmFlixAddUser(system, "Chandler", 23);
    ASSERT_TEST(mtmFlixRemoveUser(system, "Chandler") == MTMFLIX_SUCCESS);
    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixAddSeriesTest() {
    MtmFlix system = mtmFlixCreate();
    // Null values
    ASSERT_TEST(mtmFlixAddSeries(NULL, "Friends", 9000, COMEDY, NULL, 25) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddSeries(system, NULL, 9000, COMEDY, NULL, 25) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddSeries(NULL, "#Blessed", 10, DRAMA, NULL, 25) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddSeries(NULL, "Firefly", -1, SCIENCE_FICTION, NULL, 25) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddSeries(system, NULL, 10, COMEDY, NULL, -1) == MTMFLIX_NULL_ARGUMENT);
    // Name tests
    ASSERT_TEST(mtmFlixAddSeries(system, "Friends", 9000, COMEDY, NULL, 25) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddSeries(system, "21JumpStreet", 20, COMEDY, NULL, 25) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddSeries(system, "2 And 1/2 Men", 20, COMEDY, NULL, 25) == MTMFLIX_ILLEGAL_SERIES_NAME);
    ASSERT_TEST(mtmFlixAddSeries(system, "", 20, COMEDY, NULL, 25) == MTMFLIX_ILLEGAL_SERIES_NAME);
    ASSERT_TEST(mtmFlixAddSeries(system, "", -1, COMEDY, NULL, 25) == MTMFLIX_ILLEGAL_SERIES_NAME);
    ASSERT_TEST(mtmFlixAddSeries(system, "", 20, COMEDY, NULL, -1) == MTMFLIX_ILLEGAL_SERIES_NAME);
    // Series already exists
    mtmFlixAddSeries(system, "Scrubs", 160, COMEDY, NULL, 25);
    ASSERT_TEST(mtmFlixAddSeries(system, "Scrubs", 160, COMEDY, NULL, 25) == MTMFLIX_SERIES_ALREADY_EXISTS);
    ASSERT_TEST(mtmFlixAddSeries(system, "Scrubs", -1, COMEDY, NULL, 25) == MTMFLIX_SERIES_ALREADY_EXISTS);
    ASSERT_TEST(mtmFlixAddSeries(system, "Scrubs", 160, COMEDY, NULL, -1) == MTMFLIX_SERIES_ALREADY_EXISTS);
    // Age tests
    int ages1[2] = { MTM_MIN_AGE, MTM_MAX_AGE };
    ASSERT_TEST(mtmFlixAddSeries(system, "Community", 60, COMEDY, ages1, 25) == MTMFLIX_SUCCESS);
    int ages2[2] = { MTM_MIN_AGE - 1, MTM_MAX_AGE };
    ASSERT_TEST(mtmFlixAddSeries(system, "BreakingBad", 50, DRAMA, ages2, 60) == MTMFLIX_SUCCESS);
    int ages3[2] = { MTM_MIN_AGE, MTM_MAX_AGE + 1 };
    ASSERT_TEST(mtmFlixAddSeries(system, "Westworld", 20, DRAMA, ages3, 60) == MTMFLIX_SUCCESS);
    // EpisodesNum tests
    ASSERT_TEST(mtmFlixAddSeries(system, "Firefly", 0, SCIENCE_FICTION, NULL, 45) == MTMFLIX_ILLEGAL_EPISODES_NUM);
    ASSERT_TEST(mtmFlixAddSeries(system, "Halo", -1, SCIENCE_FICTION, NULL, 45) == MTMFLIX_ILLEGAL_EPISODES_NUM);
    ASSERT_TEST(mtmFlixAddSeries(system, "Halo", -1, SCIENCE_FICTION, NULL, -1) == MTMFLIX_ILLEGAL_EPISODES_NUM);
    // EpisodeDuration tests
    ASSERT_TEST(mtmFlixAddSeries(system, "DoctorWho", 500, SCIENCE_FICTION, NULL, 0) == MTMFLIX_ILLEGAL_EPISODES_DURATION);
    ASSERT_TEST(mtmFlixAddSeries(system, "Suits", 500, DRAMA, NULL, -1) == MTMFLIX_ILLEGAL_EPISODES_DURATION);
    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixRemoveSeriesTest() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddSeries(system, "Homeland", 30, CRIME, NULL, 60);
    // Null values
    ASSERT_TEST(mtmFlixRemoveSeries(NULL, "Friends") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveSeries(system, NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveSeries(NULL, "Skins") == MTMFLIX_NULL_ARGUMENT);
    // Series tests
    ASSERT_TEST(mtmFlixRemoveSeries(system, "13ReasonsWhy") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveSeries(system, "") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveSeries(system, "Homeland") == MTMFLIX_SUCCESS);
    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixReportSeriesTest() {
    MtmFlix system = mtmFlixCreate();
    FILE* fp = fopen("./mtmFlixReportSeries_test.out", "w");
    ASSERT_TEST(mtmFlixReportSeries(NULL, 0, fp) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixReportSeries(system, 0, NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixReportSeries(system, 0, fp) == MTMFLIX_NO_SERIES);
    ASSERT_TEST(mtmFlixReportSeries(system, 5, fp) == MTMFLIX_NO_SERIES);

    // Report with no amount limitations
    int ages[2] = { 18, 25 };
    mtmFlixAddSeries(system, "Friends", 9000, COMEDY, NULL, 25);
    mtmFlixAddSeries(system, "Westworld", 20, DOCUMENTARY, NULL, 60);
    mtmFlixAddSeries(system, "GameOfThrones", 70, DOCUMENTARY, ages, 60);

    MtmFlixResult result = mtmFlixReportSeries(system, 0, fp);
    fclose(fp);
    char* output = readFile("./mtmFlixReportSeries_test.out");
    const char* test1_valid = "Series 'Friends', Genre: COMEDY.\n"
                              "Series 'GameOfThrones', Genre: DOCUMENTARY.\n"
                              "Series 'Westworld', Genre: DOCUMENTARY.\n";
    ASSERT_TEST(result == MTMFLIX_SUCCESS && strcmp(output, test1_valid) == 0);

    // Report with amount limitation
    fp = fopen("./mtmFlixReportSeries_test.out", "w");
    result = mtmFlixReportSeries(system, 1, fp);
    fclose(fp);
    output = readFile("./mtmFlixReportSeries_test.out");
    const char* test2_valid = "Series 'Friends', Genre: COMEDY.\n"
                              "Series 'GameOfThrones', Genre: DOCUMENTARY.\n";
    ASSERT_TEST(result == MTMFLIX_SUCCESS && strcmp(output, test2_valid) == 0);

    // Report with series below, at, and above amount limitation
    mtmFlixAddSeries(system, "24", 24, ROMANCE, ages, 24);
    mtmFlixAddSeries(system, "Scrubs", 300, COMEDY, ages, 25);
    mtmFlixAddSeries(system, "PlanetEarth", 10, DOCUMENTARY, NULL, 45);
    mtmFlixAddSeries(system, "TheCrown", 10, DOCUMENTARY, ages, 50);

    fp = fopen("./mtmFlixReportSeries_test.out", "w");
    result = mtmFlixReportSeries(system, 2, fp);
    fclose(fp);
    output = readFile("./mtmFlixReportSeries_test.out");
    const char* test3_valid = "Series 'Friends', Genre: COMEDY.\n"
                              "Series 'Scrubs', Genre: COMEDY.\n"
                              "Series 'GameOfThrones', Genre: DOCUMENTARY.\n"
                              "Series 'PlanetEarth', Genre: DOCUMENTARY.\n"
                              "Series '24', Genre: ROMANCE.\n";
    ASSERT_TEST(result == MTMFLIX_SUCCESS && strcmp(output, test3_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixReportUsersTest() {
    MtmFlix system = mtmFlixCreate();

    FILE* fp = fopen("./mtmFlixReportUsers_test.out", "w");
    ASSERT_TEST(mtmFlixReportUsers(NULL, fp) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixReportUsers(system, NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixReportUsers(system, fp) == MTMFLIX_NO_USERS);

    // Report with people
    mtmFlixAddUser(system, "Rachel", 18);
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Monica", 30);
    MtmFlixResult result = mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Chandler is 23 years old\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Monica is 30 years old\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Rachel is 18 years old\n";
    char* output = readFile("./mtmFlixReportUsers_test.out");

    ASSERT_TEST(result == MTMFLIX_SUCCESS && strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixSeriesJoinTest() {
    MtmFlix system = mtmFlixCreate();
    // Null values
    ASSERT_TEST(mtmFlixSeriesJoin(NULL, "Chandler", "House") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixSeriesJoin(system, NULL, "House") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", NULL) == MTMFLIX_NULL_ARGUMENT);

    int ages1[2] = { 25, 90 };
    int ages2[2] = { 7, 50 };
    mtmFlixAddSeries(system, "House", 30, DRAMA, NULL, 60);
    mtmFlixAddSeries(system, "Homeland", 30, CRIME, ages1, 60);
    mtmFlixAddSeries(system, "Shameless", 50, COMEDY, ages2, 45);
    mtmFlixAddUser(system, "Chandler", 23);

    // Nonexistent elements
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Rachel", "House") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "", "House") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Rachel", "FullHouse") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "FullHouse") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "") == MTMFLIX_SERIES_DOES_NOT_EXIST);

    // Invalid age
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "Homeland") == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE);

    // Valid input
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "Shameless") == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "House") == MTMFLIX_SUCCESS);

    mtmFlixAddUser(system, "Rachel", 22);
    mtmFlixSeriesJoin(system, "Rachel", "House");
    FILE* fp = fopen("./mtmFlixSeriesJoin_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Chandler is 23 years old\n"
                              "Series: House\n"
                              "Series: Shameless\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Rachel is 22 years old\n"
                              "Series: House\n";
    char* output = readFile("./mtmFlixSeriesJoin_test.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixSeriesLeaveTest() {
    MtmFlix system = mtmFlixCreate();
    ASSERT_TEST(mtmFlixSeriesLeave(NULL, "Chandler", "Argo") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixSeriesLeave(system, NULL, "Argo") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Chandler", NULL) == MTMFLIX_NULL_ARGUMENT);

    mtmFlixAddSeries(system, "Argo", 30, DRAMA, NULL, 60);
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixSeriesJoin(system, "Chandler", "Argo");

    // Nonexistent elements
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Rachel", "Argo") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "", "Argo") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Rachel", "TheBrink") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Chandler", "TheBrink") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Chandler", "") == MTMFLIX_SERIES_DOES_NOT_EXIST);

    // Valid input
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Chandler", "Argo") == MTMFLIX_SUCCESS);
    FILE* fp = fopen("./mtmFlixSeriesLeave_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Chandler is 23 years old\n";
    char* output = readFile("./mtmFlixSeriesLeave_test.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixAddFriendTest() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Rachel", 22);

    // Null values
    ASSERT_TEST(mtmFlixAddFriend(system, NULL, "Rachel") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddFriend(system, "Rachel", NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddFriend(system, "Joey", NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddFriend(system, NULL, "Joey") == MTMFLIX_NULL_ARGUMENT);

    // Nonexistent elements
    ASSERT_TEST(mtmFlixAddFriend(system, "Rachel", "Joey") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixAddFriend(system, "Joey", "Rachel") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixAddFriend(system, "Monica", "Joey") == MTMFLIX_USER_DOES_NOT_EXIST);

    // One-sided friendship
    ASSERT_TEST(mtmFlixAddFriend(system, "Chandler", "Rachel") == MTMFLIX_SUCCESS);
    FILE* fp = fopen("./mtmFlixAddFriend_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Chandler is 23 years old\n"
                              "Friend: Rachel\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Rachel is 22 years old\n";
    char* output = readFile("./mtmFlixAddFriend_test.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    // Two-sided friendship
    mtmFlixAddFriend(system, "Rachel", "Chandler");
    fp = fopen("./mtmFlixAddFriend_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test2_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Chandler is 23 years old\n"
                              "Friend: Rachel\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Rachel is 22 years old\n"
                              "Friend: Chandler\n";
    output = readFile("./mtmFlixAddFriend_test.out");
    ASSERT_TEST(strcmp(output, test2_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixRemoveFriendTest() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Rachel", 22);
    mtmFlixAddUser(system, "Phoebe", 24);

    // Null values
    ASSERT_TEST(mtmFlixRemoveFriend(system, NULL, "Rachel") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Rachel", NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Ross", NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveFriend(system, NULL, "Ross") == MTMFLIX_NULL_ARGUMENT);

    // Nonexistent elements
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Ross", "Chandler") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Chandler", "Ross") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Ross", "Tamar") == MTMFLIX_USER_DOES_NOT_EXIST);

    mtmFlixAddFriend(system, "Rachel", "Chandler");
    mtmFlixAddFriend(system, "Rachel", "Phoebe");
    mtmFlixAddFriend(system, "Phoebe", "Rachel");
    mtmFlixAddFriend(system, "Phoebe", "Chandler");

    // Valid input
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Rachel", "Chandler") == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Rachel", "Chandler") == MTMFLIX_SUCCESS);

    FILE* fp = fopen("./mtmFlixRemoveFriend_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Chandler is 23 years old\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Phoebe is 24 years old\n"
                              "Friend: Chandler\n"
                              "Friend: Rachel\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Rachel is 22 years old\n"
                              "Friend: Phoebe\n";
    char* output = readFile("./mtmFlixRemoveFriend_test.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixGetRecommendationsTest() {
    MtmFlix system = mtmFlixCreate();
    FILE* fp = fopen("./mtmFlixGetRecommendations_test.out", "w");

    // Illegal arguments
    ASSERT_TEST(mtmFlixGetRecommendations(NULL, "Chandler", 0, fp) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixGetRecommendations(system, NULL, 0, fp) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixGetRecommendations(system, "Chandler", 0, NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixGetRecommendations(system, "Chandler", -1, fp) == MTMFLIX_USER_DOES_NOT_EXIST);
    mtmFlixAddUser(system, "Chandler", 23);
    ASSERT_TEST(mtmFlixGetRecommendations(system, "Chandler", -1, fp) == MTMFLIX_ILLEGAL_NUMBER);

    // Users
    mtmFlixAddUser(system, "Rachel", 22);
    mtmFlixAddUser(system, "Phoebe", 24);
    mtmFlixAddUser(system, "Monica", 30);
    mtmFlixAddUser(system, "Ross", 26);

    // Shows
    int ages[2] = { 25, 120 };
    mtmFlixAddSeries(system, "Friends", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "21JumpStreet", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "Community", 1, COMEDY, NULL, 25);
    mtmFlixAddSeries(system, "TheOffice", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "Brooklyn99", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "30Rock", 1, COMEDY, ages, 33);
    mtmFlixAddSeries(system, "DoctorWho", 1, SCIENCE_FICTION, NULL, 33);
    mtmFlixAddSeries(system, "Firefly", 1, SCIENCE_FICTION, NULL, 45);

    // Chandler
    mtmFlixSeriesJoin(system, "Chandler", "Friends");
    mtmFlixSeriesJoin(system, "Chandler", "21JumpStreet");
    mtmFlixSeriesJoin(system, "Chandler", "Community");
    mtmFlixSeriesJoin(system, "Chandler", "Firefly");
    mtmFlixAddFriend(system, "Chandler", "Rachel");
    mtmFlixAddFriend(system, "Chandler", "Phoebe");
    mtmFlixAddFriend(system, "Chandler", "Monica");

    // Rachel
    mtmFlixSeriesJoin(system, "Rachel", "TheOffice");

    // Phoebe
    mtmFlixSeriesJoin(system, "Phoebe", "TheOffice");

    // Ross
    mtmFlixSeriesJoin(system, "Ross", "30Rock");

    // Monica
    mtmFlixSeriesJoin(system, "Monica", "30Rock");

    // 1 series recommended, others not in liked genre or have no friend likes.
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 0, fp);
    fclose(fp);
    const char* test1_valid = "Series 'TheOffice', Genre: COMEDY.\n";
    char* output = readFile("./mtmFlixGetRecommendations_test.out");
    printf("\nOur:\n-->%s<--", output);
    printf("\nExpected:\n-->%s<--", test1_valid);
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    // 1 series recommended, 1 should be but not age appropriate
    mtmFlixAddFriend(system, "Chandler", "Ross");
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 0, fp);
    fclose(fp);
    const char* test2_valid = "Series 'TheOffice', Genre: COMEDY.\n";
    output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test2_valid) == 0);

    // 2 series recommended, same ranks
    mtmFlixSeriesJoin(system, "Rachel", "DoctorWho");
    mtmFlixSeriesJoin(system, "Phoebe", "DoctorWho");
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 0, fp);
    fclose(fp);
    const char* test3_valid = "Series 'DoctorWho', Genre: SCIENCE_FICTION.\n"
                              "Series 'TheOffice', Genre: COMEDY.\n";
    output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test3_valid) == 0);

    // 2 series recommended, different ranks
    mtmFlixSeriesJoin(system, "Chandler", "Brooklyn99");
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 0, fp);
    fclose(fp);
    const char* test4_valid = "Series 'TheOffice', Genre: COMEDY.\n"
                              "Series 'DoctorWho', Genre: SCIENCE_FICTION.\n";
    output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test4_valid) == 0);

    // 2 series recommended, but limit is 1
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 1, fp);
    fclose(fp);
    const char* test5_valid = "Series 'TheOffice', Genre: COMEDY.\n";
    output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test5_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixRemoveUserTestAdvanced() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Rachel", 22);
    mtmFlixAddUser(system, "Phoebe", 24);
    mtmFlixAddUser(system, "Shalev", 16);

    mtmFlixAddFriend(system, "Chandler", "Rachel");
    mtmFlixAddFriend(system, "Chandler", "Phoebe");
    mtmFlixAddFriend(system, "Rachel", "Chandler");
    mtmFlixAddFriend(system, "Rachel", "Phoebe");
    mtmFlixAddFriend(system, "Shalev", "Rachel");

    mtmFlixRemoveUser(system, "Rachel");

    FILE* fp = fopen("./mtmflixRemoveUser_testAdvanced.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);

    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Chandler is 23 years old\n"
                              "Friend: Phoebe\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Phoebe is 24 years old\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Shalev is 16 years old\n";
    char* output = readFile("./mtmflixRemoveUser_testAdvanced.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixRemoveSeriesTestAdvanced() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Rachel", 22);

    mtmFlixAddSeries(system, "Friends", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "21JumpStreet", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "Community", 1, COMEDY, NULL, 25);
    mtmFlixAddSeries(system, "TheOffice", 1, COMEDY, NULL, 30);

    mtmFlixSeriesJoin(system, "Chandler", "Community");
    mtmFlixSeriesJoin(system, "Chandler", "TheOffice");
    mtmFlixSeriesJoin(system, "Rachel", "TheOffice");

    mtmFlixRemoveSeries(system, "TheOffice");

    FILE* fp = fopen("./mtmflixRemoveSeries_testAdvanced.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);

    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Chandler is 23 years old\n"
                              "Series: Community\n"
                              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                              "The user Rachel is 22 years old\n";
    char* output = readFile("./mtmflixRemoveSeries_testAdvanced.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

char* readFile(char* path) {
    FILE* fp = fopen(path, "r");
    char* output = malloc(0);
    int ch = getc(fp), i = 1;
    while (ch != EOF) {
        output = realloc(output, i);
        *(output + i - 1) = ch;
        ch = getc(fp);
        i++;
    }
    output = realloc(output, i);
    *(output + i - 1) = '\0';
    fclose(fp);
    return output;
}
