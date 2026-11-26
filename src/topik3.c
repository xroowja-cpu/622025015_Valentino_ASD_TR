#include <string.h>
#include "topik3.h"

void bubble_sort_id(Paket *arr, int jml, int asc) {
    for (int i = 0; i < jml - 1; i++) {
        for (int j = 0; j < jml - i - 1; j++) {
            int c = strcmp(arr[j].id, arr[j + 1].id);
            if ((asc && c > 0) || (!asc && c < 0)) {
                Paket t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
    }
}

void selection_sort_rak(Paket *arr, int jml, int asc) {
    for (int i = 0; i < jml - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < jml; j++) {
            if ((asc && arr[j].rak < arr[idx].rak) || (!asc && arr[j].rak > arr[idx].rak))
                idx = j;
        }
        if (idx != i) {
            Paket t = arr[i]; arr[i] = arr[idx]; arr[idx] = t;
        }
    }
}