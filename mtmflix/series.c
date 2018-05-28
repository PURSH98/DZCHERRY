//ifndef include
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mtmflix.h"
#include "series.h"


struct series_t {
	//Name name;
	int episodesNum;
	Genre genre;
	int* ages;
	int episodesDuration;
};

Series seriesCreate (int episodesNum, Genre genre, int* ages, 
	int episodesDuration) {
	Series series = (Series)malloc(sizeof(*series));
	if (series == NULL) {
		return NULL;
	}
	//check parameters!
	series->episodesNum = episodesNum;
	series->genre = genre;
	if (ages == NULL) {
		series->ages = NULL; //specified in the pdf
	} else {
		// Don't know the length; use a constant
		series->ages = (int*)malloc(sizeof(*ages)*2);
		if (series->ages == NULL) {
			return NULL;
		}
		memcpy(series->ages, ages, sizeof(*ages)*2);
		if (series->ages[0] < MTM_MIN_AGE) {
			series->ages[0] = MTM_MIN_AGE; //where do those constants come from?
		}
		if (series->ages[1] > MTM_MAX_AGE) {
			series->ages[1] = MTM_MAX_AGE;
		}
	}
	series->episodesDuration = episodesDuration;
	return series;
}

void seriesFree (Series series) {
	free(series->ages);
	series->ages = NULL;
	free(series);
	series = NULL;
}

Series seriesCopy (Series series) {
	if (series == NULL) {
		return NULL;
	}
	Series new_series = seriesCreate(series->episodesNum, series->genre, 
		series->ages, series->episodesDuration);
	if (new_series == NULL) {
		return NULL;
	}
	return new_series;
}

int compareSeriesByGenre(Series series_a, Series series_b) {
	return strcmp(seriesGetGenre(series_a), seriesGetGenre(series_b));
}

//given a series instance returns its genre
char* seriesGetGenre (Series series) {
	if (series == NULL) {
		return NULL;
	}
	switch (series->genre) {
		case SCIENCE_FICTION: return "science fiction";
        case DRAMA : return "drama";
        case COMEDY : return "comedy";
        case CRIME : return "crime";
        case MYSTERY : return "mystery";
        case DOCUMENTARY : return "documentary";
        case ROMANCE : return "romance";
        case HORROR : return "horror";
	}
	// Unreachable
	assert(false);
	return NULL;
}

//given a series instance returns episode duration
int seriesGetEpisodeDuration(Series series){
    assert (series != NULL); //we check this before calling the function
    return series->episodesDuration;
}

//given a series instance returns the minimal age to watch the series
//when there are no age restrictions, returns MTM_MIN_AGE
int seriesGetMinAge (Series series) {
	assert (series != NULL); //we check this before calling the function
	if (series->ages == NULL) {
		return MTM_MIN_AGE;
	}
	return series->ages[0];
}

//given a series instance returns the maximal age to watch the series
//when there are no age restrictions, returns MTM_MAX_AGE
int seriesGetMaxAge (Series series) {
	assert (series != NULL); //we check this before calling the function
	if (series->ages == NULL) {
		return MTM_MAX_AGE;
	}
	return series->ages[1];
}
