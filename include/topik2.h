#ifndef TOPIK2_H
#define TOPIK2_H

#define MAX_ID 20
#define MAX_STR 50

typedef struct {
    char id[MAX_ID];
    char penerima[MAX_STR];
    char tujuan[MAX_STR];
    int rak;
    int status; // 0 = belum diantar, 1 = sudah diantar
} Paket;

Paket* muat_paket(int *jml, int *kap);
void simpan_paket(const Paket *arr, int jml);
void tambah_paket(Paket **arr, int *jml, int *kap, Paket p);
void lihat_belum_diantar(const Paket *arr, int jml);
void lihat_semua_paket(const Paket *arr, int jml);

#endif