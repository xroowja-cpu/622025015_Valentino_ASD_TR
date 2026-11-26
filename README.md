# Sistem Manajemen Gudang dan Pelacakan Paket Berbasis CLI

Repositori Tugas Rancang mata kuliah **Algoritma dan Struktur Data (ASD 2026)** berupa aplikasi berbasis *Command-Line Interface* (CLI) menggunakan bahasa C untuk mengelola data paket, status pengiriman, antrean kurir, riwayat pembatalan pengiriman, lokasi rak penyimpanan, dan penelusuran rute zona gudang secara terstruktur dan persisten.

---

## Identitas Mahasiswa
- **Nama:** Valentino Teas Monelyko Mantolas
- **NIM:** `622025015`
- **Program Studi:** Teknik Komputer
- **Fakultas:** Fakultas Teknik Elektronika dan Komputer (FTEK)
- **Universitas:** Universitas Kristen Satya Wacana (UKSW)
- **Mata Kuliah:** Algoritma dan Struktur Data (ASD 2026)
- **Judul Proyek:** Sistem Manajemen Gudang dan Pelacakan Paket Berbasis CLI Menggunakan Bahasa C

---

## Deskripsi

**Sistem Manajemen Gudang dan Pelacakan Paket** adalah aplikasi konsol berbasis bahasa C yang dirancang dengan arsitektur modular multi-file. Deklarasi *header* (`struct`, konstanta, dan prototipe fungsi) ditempatkan pada folder `include/`, implementasi logika program ditempatkan pada folder `src/`, sedangkan data persisten disimpan dalam bentuk berkas teks pada folder `data/`.

Saat program dijalankan, pengguna melewati proses autentikasi (*Register* atau *Login*) menggunakan berkas `data/akun.txt`. Setelah berhasil masuk ke menu utama gudang (`menu_gudang()`), program memuat data paket ke array dinamis (`malloc` dan `realloc`), memuat graf keterhubungan zona dari `data/zona.txt`, lalu menyinkronkan data ke *Hash Table*, *Binary Search Tree* (BST), dan *Queue*. Ketika pengguna melakukan *Logout* (`0`), seluruh memori dinamis yang dialokasikan dibebaskan kembali (`free`) agar tidak terjadi *memory leak*.

## Cara Kompilasi dan Menjalankan
Pastikan posisi terminal berada di folder root `622025015_Valentino_ASD_TR/`, lalu jalankan perintah sesuai sistem operasi:

### Linux / macOS / Git Bash
```bash
gcc -Wall -Wextra src/*.c -Iinclude -o gudang.exe
.\gudang.exe

### Rincian Modul & Struktur Data (Topik 1 – Topik 8)
1. **Topik 1 — Input Aman & Autentikasi (`include/topik1.h`, `src/topik1.c`)**
   - Mengatur tampilan dan input terminal melalui `bersihkan_layar()`, `jeda_layar()`, dan `bersihkan_buffer()`.
   - Memvalidasi input angka (`baca_angka()`) menggunakan `fgets()` dan `sscanf()` agar input non-angka tidak memicu *infinite loop*.
   - Memvalidasi input teks (`baca_teks()`) untuk menghapus karakter *newline* (`\n`) serta menolak input kosong atau karakter pembatas `|`.
   - Mengelola pendaftaran akun baru (`register_akun()`) dengan pengecekan *username* ganda dan verifikasi masuk (`login_akun()`) terhadap `data/akun.txt`.

2. **Topik 2 — Struct, Array Dinamis, Pointer, & File I/O (`include/topik2.h`, `src/topik2.c`)**
   - Mendefinisikan `struct Paket` yang menyimpan `id`, `penerima`, `tujuan`, `rak`, dan `status` (`0` = *Belum Diantar*, `1` = *Sudah Diantar*).
   - Memuat dan menyimpan data ke `data/paket.txt` secara dinamis memakai `malloc()`, `realloc()`, dan `free()`.
   - Menyediakan `tambah_paket()` (dengan validasi keunikan ID paket dan kevalidan/keunikan nomor rak), `lihat_belum_diantar()`, dan `lihat_semua_paket()`.

3. **Topik 3 — Sorting (`include/topik3.h`, `src/topik3.c`)**
   - Mengurutkan data paket berdasarkan `id` (`strcmp()`) menggunakan *Bubble Sort* (`bubble_sort_id()`) secara *Ascending* maupun *Descending*.
   - Mengurutkan data paket berdasarkan nomor `rak` menggunakan *Selection Sort* (`selection_sort_rak()`) secara *Ascending* maupun *Descending*, lalu menyimpan perubahannya ke `data/paket.txt`.

4. **Topik 4 — Queue & Stack (`include/topik4.h`, `src/topik4.c`)**
   - Menerapkan *Circular Queue* (`struct Antrean` dengan `init_q()`, `enqueue()`, `dequeue()`, `tampil_q()`) berprinsip FIFO untuk antrean pengiriman paket berstatus belum diantar (`status == 0`).
   - Menerapkan *Stack* (`struct Riwayat` dengan `init_s()`, `push_undo()`, `pop_undo()`) berprinsip LIFO untuk fitur *Undo* pengiriman terakhir, mengembalikan status paket ke `0` dan memasukkannya kembali ke antrean bila memenuhi syarat.

5. **Topik 5 — Searching (`include/topik5.h`, `src/topik5.c`)**
   - Melakukan *Sequential Search* berdasarkan nama penerima (`seq_search_penerima()` memakai `strstr()`) dan berdasarkan `id` (`seq_search_id()` memakai `strcmp()`).
   - Melakukan *Binary Search* (`bin_search_id()`) berdasarkan `id` paket pada array yang telah diurutkan secara *Ascending*.

6. **Topik 6 — Hash Table (`include/topik6.h`, `src/topik6.c`)**
   - Mengimplementasikan tabel hash berukuran `UKURAN_HT = 11` dengan fungsi hash polinomial (`h = h * 31 + s[i]` modulo `11`) dan *Chaining* (`struct HTNode`) untuk mengatasi *collision*.
   - Dilengkapi `ht_init()`, `ht_insert()`, `ht_search()`, `ht_tampil()`, `ht_rebuild()`, dan `ht_free()`.

7. **Topik 7 — Binary Search Tree / BST (`include/topik7.h`, `src/topik7.c`)**
   - Mengelola nomor rak unik dalam pohon biner pencarian (`struct RakNode`) melalui `bst_insert()`, `bst_search()`, dan `bst_delete()` (menggunakan *in-order successor* via `nilai_min()`).
   - Menyediakan penelusuran *Pre-Order* (`preorder()`), *In-Order* (`inorder()`), dan *Post-Order* (`postorder()`), serta pembebasan memori `bst_free()`.

8. **Topik 8 — Graph (`include/topik8.h`, `src/topik8.c`)**
   - Memodelkan graf tak berarah antar zona gudang menggunakan *Adjacency Matrix* dari `data/zona.txt` (`muat_graf()`).
   - Menyediakan penelusuran rute zona menggunakan *Depth-First Search* (`dfs_zona()`) dan *Breadth-First Search* (`bfs_zona()`).

### Struktur Direktori
```text
622025015_Valentino_ASD_TR/
├── include/
│   ├── topik1.h
│   ├── topik2.h
│   ├── topik3.h
│   ├── topik4.h
│   ├── topik5.h
│   ├── topik6.h
│   ├── topik7.h
│   └── topik8.h
├── src/
│   ├── main.c
│   ├── topik1.c
│   ├── topik2.c
│   ├── topik3.c
│   ├── topik4.c
│   ├── topik5.c
│   ├── topik6.c
│   ├── topik7.c
│   └── topik8.c
├── data/
│   ├── akun.txt
│   ├── paket.txt
│   └── zona.txt
├── docs/
│   └── 622025015_Valentino_ASD_TR.pdf
├── .gitignore
└── README.md