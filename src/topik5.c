#include <stdio.h>
#include <string.h>
#include "topik5.h"

void seq_search_penerima(const Paket *arr, int jml, const char *nama) {
    int ketemu = 0;
    for (int i = 0; i < jml; i++) {
        if (strstr(arr[i].penerima, nama) != NULL) {
            printf("Ketemu: [%s] %s -> %s (Rak %d)\n",
                   arr[i].id, arr[i].penerima, arr[i].tujuan, arr[i].rak);
            ketemu = 1;
        }
    }
    if (!ketemu) printf("Tidak ditemukan.\n");
}

int seq_search_id(const Paket *arr, int jml, const char *id) {
    for (int i = 0; i < jml; i++) {
        if (strcmp(arr[i].id, id) == 0) return i;
    }
    return -1;
}

int bin_search_id(const Paket *arr, int jml, const char *id) {
    int ki = 0, ka = jml - 1;
    while (ki <= ka) {
        int mid = ki + (ka - ki) / 2;
        int c = strcmp(arr[mid].id, id);
        if (c == 0) return mid;
        if (c < 0) ki = mid + 1;
        else ka = mid - 1;
    }
    return -1;
}