#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "topik6.h"

static int hash_fn(const char *s) {
    unsigned int h = 0;
    for (int i = 0; s[i]; i++) h = h * 31 + (unsigned char)s[i];
    return (int)(h % UKURAN_HT);
}

void ht_init(HTNode *ht[]) {
    for (int i = 0; i < UKURAN_HT; i++) ht[i] = NULL;
}

void ht_insert(HTNode *ht[], Paket p) {
    int idx = hash_fn(p.id);
    HTNode *n = (HTNode *)malloc(sizeof(HTNode));
    if (!n) return;
    n->p = p;
    n->next = ht[idx];
    ht[idx] = n;
}

Paket* ht_search(HTNode *ht[], const char *id) {
    HTNode *cur = ht[hash_fn(id)];
    while (cur) {
        if (strcmp(cur->p.id, id) == 0) return &cur->p;
        cur = cur->next;
    }
    return NULL;
}

void ht_tampil(HTNode *ht[]) {
    for (int i = 0; i < UKURAN_HT; i++) {
        printf("Slot %2d: ", i);
        HTNode *cur = ht[i];
        while (cur) { printf("[%s] -> ", cur->p.id); cur = cur->next; }
        printf("NULL\n");
    }
}

void ht_free(HTNode *ht[]) {
    for (int i = 0; i < UKURAN_HT; i++) {
        HTNode *cur = ht[i];
        while (cur) { HTNode *tmp = cur; cur = cur->next; free(tmp); }
        ht[i] = NULL;
    }
}

void ht_rebuild(HTNode *ht[], const Paket *arr, int jml) {
    ht_free(ht);
    for (int i = 0; i < jml; i++) ht_insert(ht, arr[i]);
}