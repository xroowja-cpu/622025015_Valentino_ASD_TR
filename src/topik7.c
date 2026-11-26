#include <stdio.h>
#include <stdlib.h>
#include "topik7.h"

RakNode* bst_insert(RakNode *akar, int rak) {
    if (!akar) {
        RakNode *n = (RakNode *)malloc(sizeof(RakNode));
        if (!n) return NULL;
        n->rak = rak; n->kiri = n->kanan = NULL;
        return n;
    }
    if (rak < akar->rak) akar->kiri = bst_insert(akar->kiri, rak);
    else if (rak > akar->rak) akar->kanan = bst_insert(akar->kanan, rak);
    return akar;
}

RakNode* bst_search(RakNode *akar, int rak) {
    if (!akar || akar->rak == rak) return akar;
    return (rak < akar->rak) ? bst_search(akar->kiri, rak) : bst_search(akar->kanan, rak);
}

static RakNode* nilai_min(RakNode *n) {
    while (n && n->kiri) n = n->kiri;
    return n;
}

RakNode* bst_delete(RakNode *akar, int rak) {
    if (!akar) return NULL;
    if (rak < akar->rak) akar->kiri = bst_delete(akar->kiri, rak);
    else if (rak > akar->rak) akar->kanan = bst_delete(akar->kanan, rak);
    else {
        if (!akar->kiri) { RakNode *t = akar->kanan; free(akar); return t; }
        if (!akar->kanan) { RakNode *t = akar->kiri; free(akar); return t; }
        RakNode *m = nilai_min(akar->kanan);
        akar->rak = m->rak;
        akar->kanan = bst_delete(akar->kanan, m->rak);
    }
    return akar;
}

void preorder(const RakNode *a)  { if (a) { printf("%d ", a->rak); preorder(a->kiri); preorder(a->kanan); } }
void inorder(const RakNode *a)   { if (a) { inorder(a->kiri); printf("%d ", a->rak); inorder(a->kanan); } }
void postorder(const RakNode *a) { if (a) { postorder(a->kiri); postorder(a->kanan); printf("%d ", a->rak); } }

void bst_free(RakNode *akar) {
    if (!akar) return;
    bst_free(akar->kiri);
    bst_free(akar->kanan);
    free(akar);
}