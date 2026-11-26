#include <stdio.h>
#include <stdlib.h>
#include "topik2.h"

Paket* muat_paket(int *jml, int *kap) {
    *jml = 0; *kap = 10;
    Paket *arr = (Paket *)malloc((size_t)(*kap) * sizeof(Paket));
    if (!arr) exit(1);

    FILE *f = fopen("data/paket.txt", "r");
    if (!f) return arr;

    Paket t;
    while (fscanf(f, "%19[^|]|%49[^|]|%49[^|]|%d|%d\n",
                  t.id, t.penerima, t.tujuan, &t.rak, &t.status) == 5) {
        if (*jml >= *kap) {
            *kap *= 2;
            arr = (Paket *)realloc(arr, (size_t)(*kap) * sizeof(Paket));
        }
        arr[(*jml)++] = t;
    }
    fclose(f);
    return arr;
}

void simpan_paket(const Paket *arr, int jml) {
    FILE *f = fopen("data/paket.txt", "w");
    if (!f) return;
    for (int i = 0; i < jml; i++) {
        fprintf(f, "%s|%s|%s|%d|%d\n",
                arr[i].id, arr[i].penerima, arr[i].tujuan, arr[i].rak, arr[i].status);
    }
    fclose(f);
}

void tambah_paket(Paket **arr, int *jml, int *kap, Paket p) {
    if (*jml >= *kap) {
        *kap *= 2;
        *arr = (Paket *)realloc(*arr, (size_t)(*kap) * sizeof(Paket));
    }
    (*arr)[(*jml)++] = p;
    simpan_paket(*arr, *jml);
    printf("[+] Paket %s ditambahkan.\n", p.id);
}

void lihat_belum_diantar(const Paket *arr, int jml) {
    int ada = 0;
    printf("\n--- BELUM DIANTAR ---\n");
    for (int i = 0; i < jml; i++) {
        if (arr[i].status == 0) {
            printf("[%s] %s -> %s | Rak %d\n", arr[i].id, arr[i].penerima, arr[i].tujuan, arr[i].rak);
            ada = 1;
        }
    }
    if (!ada) printf("Semua paket sudah diantar.\n");
}

void lihat_semua_paket(const Paket *arr, int jml) {
    printf("\n--- SEMUA PAKET ---\n");
    if (jml == 0) { printf("Kosong.\n"); return; }
    for (int i = 0; i < jml; i++) {
        printf("%d. [%s] %s -> %s | Rak %d | %s\n",
               i + 1, arr[i].id, arr[i].penerima, arr[i].tujuan, arr[i].rak,
               arr[i].status == 0 ? "BELUM DIANTAR" : "SUDAH DIANTAR");
    }
}