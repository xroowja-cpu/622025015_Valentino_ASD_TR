#include <stdio.h>
#include <string.h>
#include "topik4.h"

void init_q(Antrean *q) { q->depan = 0; q->belakang = -1; q->jml = 0; }
void init_s(Riwayat *s) { s->top = -1; }

void enqueue(Antrean *q, const char *id) {
    if (q->jml >= MAX_Q) return;
    q->belakang = (q->belakang + 1) % MAX_Q;
    strcpy(q->id[q->belakang], id);
    q->jml++;
}

int dequeue(Antrean *q, char *out_id) {
    if (q->jml == 0) return 0;
    strcpy(out_id, q->id[q->depan]);
    q->depan = (q->depan + 1) % MAX_Q;
    q->jml--;
    return 1;
}

void tampil_q(const Antrean *q) {
    printf("Antrean (%d): ", q->jml);
    if (q->jml == 0) { printf("kosong\n"); return; }
    for (int i = 0; i < q->jml; i++) {
        printf("[%s] ", q->id[(q->depan + i) % MAX_Q]);
    }
    printf("\n");
}

void push_undo(Riwayat *s, const char *id, int st) {
    if (s->top >= MAX_Q - 1) return;
    s->top++;
    strcpy(s->id[s->top], id);
    s->status_lama[s->top] = st;
}

int pop_undo(Riwayat *s, char *out_id, int *out_st) {
    if (s->top < 0) return 0;
    strcpy(out_id, s->id[s->top]);
    *out_st = s->status_lama[s->top];
    s->top--;
    return 1;
}