#ifndef TOPIK6_H
#define TOPIK6_H

#include "topik2.h"
#define UKURAN_HT 11

typedef struct HTNode {
    Paket p;
    struct HTNode *next;
} HTNode;

void ht_init(HTNode *ht[]);
void ht_insert(HTNode *ht[], Paket p);
Paket* ht_search(HTNode *ht[], const char *id);
void ht_tampil(HTNode *ht[]);
void ht_free(HTNode *ht[]);
void ht_rebuild(HTNode *ht[], const Paket *arr, int jml);

#endif