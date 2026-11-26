#ifndef TOPIK8_H
#define TOPIK8_H

#define MAX_V 20

typedef struct {
    int jml_v;
    int adj[MAX_V + 1][MAX_V + 1];
} Graf;

void muat_graf(Graf *g, const char *file);
void dfs_zona(const Graf *g, int asal);
void bfs_zona(const Graf *g, int asal);

#endif