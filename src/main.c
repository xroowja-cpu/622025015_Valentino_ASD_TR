#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#define BUAT_DIR(x) _mkdir(x)
#else
#include <sys/stat.h>
#define BUAT_DIR(x) mkdir(x, 0777)
#endif

#include "topik1.h"
#include "topik2.h"
#include "topik3.h"
#include "topik4.h"
#include "topik5.h"
#include "topik6.h"
#include "topik7.h"
#include "topik8.h"

static void menu_gudang(const char *user) {
    int jml = 0, kap = 0;
    Paket *arr = muat_paket(&jml, &kap);
    Antrean q; Riwayat s;
    HTNode *ht[UKURAN_HT];
    RakNode *akar = NULL;
    Graf g;

    init_q(&q); init_s(&s);
    ht_init(ht);
    muat_graf(&g, "data/zona.txt");

    for (int i = 0; i < jml; i++) {
        ht_insert(ht, arr[i]);
        akar = bst_insert(akar, arr[i].rak);
        if (arr[i].status == 0) enqueue(&q, arr[i].id);
    }

    int p;
    do {
        printf("\n=== GUDANG (%s) ===\n", user);
        printf("1. Tambah Paket\n2. Lihat Belum Diantar\n3. Lihat Semua Paket\n");
        printf("4. Urutkan (Bubble/Selection)\n5. Kirim Paket (Queue)\n6. Undo Kirim (Stack)\n");
        printf("7. Cari Paket (Seq/Bin)\n8. Hash Table\n9. BST Rak\n10. Graf Zona\n0. Logout\n");
        p = baca_angka("Pilih: ");

        if (p == 1) {
            Paket pk;
            baca_teks("ID: ", pk.id, MAX_ID);
            if (ht_search(ht, pk.id)) { printf("[!] ID sudah ada!\n"); continue; }
            baca_teks("Penerima: ", pk.penerima, MAX_STR);
            baca_teks("Tujuan: ", pk.tujuan, MAX_STR);
            pk.rak = baca_angka("Rak: ");
            if (pk.rak <= 0 || bst_search(akar, pk.rak)) { printf("[!] Rak tidak valid/sudah terisi!\n"); continue; }
            pk.status = 0;
            tambah_paket(&arr, &jml, &kap, pk);
            ht_insert(ht, pk);
            akar = bst_insert(akar, pk.rak);
            enqueue(&q, pk.id);
        } else if (p == 2) {
            lihat_belum_diantar(arr, jml);
        } else if (p == 3) {
            lihat_semua_paket(arr, jml);
        } else if (p == 4) {
            if (jml == 0) { printf("[!] Data kosong.\n"); continue; }
            int j = baca_angka("1. Bubble(ID)  2. Selection(Rak): ");
            int a = baca_angka("1. Asc  0. Desc: ");
            if (j == 1) bubble_sort_id(arr, jml, a == 1);
            else selection_sort_rak(arr, jml, a == 1);
            simpan_paket(arr, jml);
            lihat_semua_paket(arr, jml);
        } else if (p == 5) {
            tampil_q(&q);
            char id[MAX_ID];
            if (dequeue(&q, id)) {
                int idx = seq_search_id(arr, jml, id);
                if (idx != -1) {
                    push_undo(&s, id, arr[idx].status);
                    arr[idx].status = 1;
                    simpan_paket(arr, jml);
                    ht_rebuild(ht, arr, jml);
                }
                printf("[+] Dikirim: %s\n", id);
            } else printf("[!] Antrean kosong.\n");
        } else if (p == 6) {
            char id[MAX_ID]; int st;
            if (pop_undo(&s, id, &st)) {
                int idx = seq_search_id(arr, jml, id);
                if (idx != -1) {
                    arr[idx].status = st;
                    if (st == 0) enqueue(&q, id);
                    simpan_paket(arr, jml);
                    ht_rebuild(ht, arr, jml);
                }
                printf("[+] Undo: %s\n", id);
            } else printf("[!] Riwayat kosong.\n");
        } else if (p == 7) {
            int m = baca_angka("1. Nama(Seq)  2. ID(Bin): ");
            if (m == 1) {
                char nama[MAX_STR]; baca_teks("Nama: ", nama, MAX_STR);
                seq_search_penerima(arr, jml, nama);
            } else if (m == 2) {
                char id[MAX_ID]; baca_teks("ID: ", id, MAX_ID);
                bubble_sort_id(arr, jml, 1); simpan_paket(arr, jml);
                int idx = bin_search_id(arr, jml, id);
                if (idx != -1) printf("Ketemu: %s -> %s (Rak %d)\n", arr[idx].penerima, arr[idx].tujuan, arr[idx].rak);
                else printf("Tidak ada.\n");
            }
        } else if (p == 8) {
            char id[MAX_ID]; baca_teks("ID Hash: ", id, MAX_ID);
            Paket *res = ht_search(ht, id);
            if (res) printf("Ketemu: %s -> %s (Rak %d)\n", res->penerima, res->tujuan, res->rak);
            else printf("Tidak ada.\n");
            ht_tampil(ht);
        } else if (p == 9) {
            printf("Pre : "); preorder(akar);
            printf("\nIn  : "); inorder(akar);
            printf("\nPost: "); postorder(akar); printf("\n");
            int h = baca_angka("Hapus rak (0=batal): ");
            if (h > 0) {
                if (bst_search(akar, h)) { akar = bst_delete(akar, h); printf("[+] Rak %d dihapus.\n", h); }
                else printf("[!] Rak tidak ada.\n");
            }
        } else if (p == 10) {
            int asal = baca_angka("Zona asal: ");
            dfs_zona(&g, asal);
            bfs_zona(&g, asal);
        }
    } while (p != 0);

    ht_free(ht);
    bst_free(akar);
    free(arr);
}

int main(void) {
    BUAT_DIR("data");
    char user[MAX_STR];
    int m;
    do {
        printf("\n1. Login  2. Register  0. Keluar\n");
        m = baca_angka("Pilih: ");
        if (m == 1 && login_akun(user)) menu_gudang(user);
        else if (m == 2) register_akun();
    } while (m != 0);
    return 0;
}