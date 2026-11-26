#ifndef TOPIK4_H
#define TOPIK4_H

#include "topik2.h"
#define MAX_Q 100

typedef struct {
    char id[MAX_Q][MAX_ID];
    int depan, belakang, jml;
} Antrean;

typedef struct {
    char id[MAX_Q][MAX_ID];
    int status_lama[MAX_Q];
    int top;
} Riwayat;

void init_q(Antrean *q);
void enqueue(Antrean *q, const char *id);
int dequeue(Antrean *q, char *out_id);
void tampil_q(const Antrean *q);

void init_s(Riwayat *s);
void push_undo(Riwayat *s, const char *id, int st);
int pop_undo(Riwayat *s, char *out_id, int *out_st);

#endif