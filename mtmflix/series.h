//ifndef include

typedef struct series_t* Series;

void seriesFree (Series series);
Series seriesCopy (Series series);
int compareSeriesByGenre(Series series_a, Series series_b);