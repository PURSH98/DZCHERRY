#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

typedef int (*cmpFunction)(void *, void *);

void merge(void **a, int na, void **b, int nb, void **c,
           cmpFunction compare);

void mergeSort(void **a, int n, cmpFunction compare);

void internalMSort(void **a, int n, void **helper_array,
                   cmpFunction compare);

/*Merges two arrays to get the array sorted in ascending order
 * void **a - first array
 * int na - length of the array a
 * void **b - second array
 * int nb - length of the array b
 * void **c - array that will contain the result of merge operation
 * cmpFunction compare - pointer to a comparator*/
void merge(void **a, int na, void **b, int nb, void **c,
           cmpFunction compare) {
    assert(a && b && c && compare);
    int ia, ib, ic;
    for (ia = ib = ic = 0; (ia < na) && (ib < nb); ic++) {
        if (compare(a[ia], b[ib]) < 0) {
            c[ic] = a[ia];
            ia++;
        } else {
            c[ic] = b[ib];
            ib++;
        }
    }
    for (; ia < na; ia++, ic++) c[ic] = a[ia];
    for (; ib < nb; ib++, ic++) c[ic] = b[ib];
}

/*Sorts the array in ascending order
 * void **a - array to be sorted
 * int n - length of the array a
 * cmpFunction compare - pointer to a comparator*/
void mergeSort(void **a, int n, cmpFunction compare) {
    assert(a && compare);
    void **tmp_array = malloc(sizeof(*tmp_array) * n);
    internalMSort(a, n, tmp_array, compare);
    free(tmp_array);
}

/*Sorts the array using temporary copy of itself
 * void **a - array to be sorted
 * int n - length of the array
 * void **helper_array - temporary copy of the array a*/
void internalMSort(void **a, int n, void **helper_array,
                   cmpFunction compare) {
    assert(a && helper_array && compare);
    int left = n / 2;
    int right = n - left;
    if (n < 2)
        return;
    internalMSort(a, left, helper_array, compare);
    internalMSort(a + left, right, helper_array, compare);
    merge(a, left, a + left, right, helper_array, compare);
    memcpy(a, helper_array, n * sizeof(*helper_array));
}