//ifndef include

struct mtmFlix_t {
	//Name name;
	int episodesNum;
	Genre genre;
	int* ages;
	int episodesDuration;
};

Series SeriesCreate (int episodesNum, Genre genre, int* ages, int episodesDuration) {
	Series series = malloc(sizeof(Series));
	if (series == NULL) {
		return NULL;
	}
	//check parameters!
	series->episodesNum = episodesNum;
	series->genre = genre;
	series ages = ages;
	series->episodesDuration = episodesDuration;
	return series;
}

void SeriesFree (Series series) {
	free(series->ages);
	series->ages = NULL;
	free(series);
	series = NULL;
}

Series SeriesCopy (Series series) {
	Series new_series = SeriesCreate(series->episodesNum, series->genre, series->ages, series->episodesDuration);
	return new_series;
}