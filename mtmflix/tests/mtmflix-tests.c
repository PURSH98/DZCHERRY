/* Target: Wonderful. */

// Change the includes in according to your code.
#include "../mtmflix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void test1(FILE *f1) {
    fprintf(f1, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Test 1..\n");
    int ages1[2] = {20, 80};
    MtmFlix a = mtmFlixCreate();
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

void test2(FILE *f1) {
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

void test3(FILE *f1) {
    fprintf(f1, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST 3 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Test 3..\n");
    MtmFlix a = mtmFlixCreate();
    assert(a);

    int ages[2] = {22, 55};
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

int main() {
    printf("-\n");
    FILE *f1 = fopen("OutputFileFromTest", "w");
    assert(f1);
    /**
     * NOTICE
     * If you are about to change the test code,
     * the test won't work properly and you might get
     * additional fails at the finalCheck function.
     */
    test1(f1);
    test2(f1);
    test3(f1);
    fclose(f1);

    finalCheck();
    return 0;
}
