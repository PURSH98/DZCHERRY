//ifndef include

struct mtmFlix_t {
	//Name name;
	int episodesNum;
	Genre genre;
	int* ages;
	int episodesDuration;
};

Series SeriesCreate (const char* name, int episodesNum, Genre genre, int* ages, int episodesDuration) {
	Series series = malloc(sizeof(Series));
	//series-> name = name; //apparently we can't have it here, as it is a key
	series->episodesNum = episodesNum;
	series->genre = genre;
	series ages = ages;
	series->episodesDuration = episodesDuration;
	return series;
}

void SeriesFree {
	
}

Series SeriesCopy {

}