#ifndef TOPIK7_H
#define TOPIK7_H

typedef struct RakNode {
    int rak;
    struct RakNode *kiri, *kanan;
} RakNode;

RakNode* bst_insert(RakNode *akar, int rak);
RakNode* bst_search(RakNode *akar, int rak);
RakNode* bst_delete(RakNode *akar, int rak);
void preorder(const RakNode *a);
void inorder(const RakNode *a);
void postorder(const RakNode *a);
void bst_free(RakNode *akar);

#endif