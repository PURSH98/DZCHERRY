//ifndef include

typedef struct series_t* Series;

Series seriesCreate (int episodesNum, Genre genre, int* ages, int episodesDuration);
void seriesFree (Series series);
Series seriesCopy (Series series);
char* seriesGetGenre (Series series);
int compareSeriesByGenre(Series series_a, Series series_b);
int seriesGetEpisodeDuration(Series series);
