#include <stdio.h>
#include <string.h>
#include "topik1.h"

int baca_angka(const char *pesan) {
    char buf[64], sisa;
    int x;
    while (1) {
        printf("%s", pesan);
        if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%d %c", &x, &sisa) == 1)
            return x;
        printf("[!] Input harus angka!\n");
    }
}

void baca_teks(const char *pesan, char *out, int maks) {
    while (1) {
        printf("%s", pesan);
        if (fgets(out, maks, stdin)) {
            out[strcspn(out, "\n")] = '\0';
            if (strlen(out) > 0 && strchr(out, '|') == NULL) return;
        }
        printf("[!] Input tidak boleh kosong atau pakai '|'.\n");
    }
}

void register_akun(void) {
    char u[50], p[50], fu[50], fp[50];
    baca_teks("Username baru: ", u, 50);
    baca_teks("Password baru: ", p, 50);

    FILE *f = fopen("data/akun.txt", "r");
    if (f) {
        while (fscanf(f, "%49[^|]|%49[^\n]\n", fu, fp) == 2) {
            if (strcmp(fu, u) == 0) {
                printf("[!] Username sudah terdaftar!\n");
                fclose(f);
                return;
            }
        }
        fclose(f);
    }

    f = fopen("data/akun.txt", "a");
    if (f) {
        fprintf(f, "%s|%s\n", u, p);
        fclose(f);
        printf("[+] Akun terdaftar.\n");
    }
}

int login_akun(char *user_aktif) {
    char u[50], p[50], fu[50], fp[50];
    baca_teks("Username: ", u, 50);
    baca_teks("Password: ", p, 50);

    FILE *f = fopen("data/akun.txt", "r");
    if (!f) { printf("[!] Belum ada akun.\n"); return 0; }

    while (fscanf(f, "%49[^|]|%49[^\n]\n", fu, fp) == 2) {
        if (strcmp(fu, u) == 0 && strcmp(fp, p) == 0) {
            strcpy(user_aktif, u);
            fclose(f);
            printf("[+] Login berhasil (%s).\n", user_aktif);
            return 1;
        }
    }
    fclose(f);
    printf("[!] Login gagal.\n");
    return 0;
}