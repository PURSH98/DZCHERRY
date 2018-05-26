//ifndef include

struct series_t {
	//Name name;
	int episodesNum;
	Genre genre;
	int* ages;
	int episodesDuration;
};

Series seriesCreate (int episodesNum, Genre genre, int* ages, int episodesDuration) {
	Series series = malloc(sizeof(Series));
	if (series == NULL) {
		return NULL;
	}
	//check parameters!
	series->episodesNum = episodesNum;
	series->genre = genre;
	if (ages == NULL) {
		series->ages = NULL; //specified in the pdf
	} else {
		series->ages = malloc(sizeof(ages));
		if (series->ages == NULL) {
			return NULL;
		}
		memcpy(series->ages, ages, sizeof(ages));
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
	Series new_series = seriesCreate(series->episodesNum, series->genre, series->ages, series->episodesDuration);
	if (new_series == NULL) {
		return NULL;
	}
	return new_series;
}

int compareSeriesByGenre(Series series_a, Series series_b) {
	return strcmp(series_a->genre, series_b->genre);
}

Genre seriesGetGenre (Series series) {
	if (series == NULL) {
		return NULL;
	}
	return series->genre;
}