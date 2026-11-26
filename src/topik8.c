#include <stdio.h>
#include <string.h>
#include "topik8.h"

void muat_graf(Graf *g, const char *file) {
    memset(g->adj, 0, sizeof(g->adj));
    g->jml_v = 5;
    FILE *f = fopen(file, "r");
    int e, u, v;
    if (f && fscanf(f, "%d %d", &g->jml_v, &e) == 2) {
        for (int i = 0; i < e && fscanf(f, "%d %d", &u, &v) == 2; i++) {
            if (u >= 1 && u <= g->jml_v && v >= 1 && v <= g->jml_v)
                g->adj[u][v] = g->adj[v][u] = 1;
        }
        fclose(f);
    }
}

static void dfs_bantu(const Graf *g, int u, int vis[]) {
    vis[u] = 1;
    printf("Z%d ", u);
    for (int w = 1; w <= g->jml_v; w++)
        if (g->adj[u][w] && !vis[w]) dfs_bantu(g, w, vis);
}

void dfs_zona(const Graf *g, int asal) {
    if (asal < 1 || asal > g->jml_v) { printf("[!] Zona asal tidak valid.\n"); return; }
    int vis[MAX_V + 1] = {0};
    printf("DFS: "); dfs_bantu(g, asal, vis); printf("\n");
}

void bfs_zona(const Graf *g, int asal) {
    if (asal < 1 || asal > g->jml_v) { printf("[!] Zona asal tidak valid.\n"); return; }
    int vis[MAX_V + 1] = {0}, q[MAX_V + 1], d = 0, b = 0;
    vis[asal] = 1; q[b++] = asal;
    printf("BFS: ");
    while (d < b) {
        int u = q[d++];
        printf("Z%d ", u);
        for (int w = 1; w <= g->jml_v; w++) {
            if (g->adj[u][w] && !vis[w]) { vis[w] = 1; q[b++] = w; }
        }
    }
    printf("\n");
}