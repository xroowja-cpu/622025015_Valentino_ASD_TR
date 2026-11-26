#ifndef TOPIK5_H
#define TOPIK5_H

#include "topik2.h"

void seq_search_penerima(const Paket *arr, int jml, const char *nama);
int seq_search_id(const Paket *arr, int jml, const char *id);
int bin_search_id(const Paket *arr, int jml, const char *id);

#endif