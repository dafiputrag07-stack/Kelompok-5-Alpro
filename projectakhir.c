#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// ==========================================================
// BAGIAN 1: STRUKTUR DATA (UPDATED)
// ==========================================================

typedef struct {
    char nik[20];
    char nama[50];
    char password[20];
    long pendapatan;
    int tanggungan;
    int kondisiRumah;
    int statusKerja;
    long totalAset;

    double skorAkhir;
    int golongan;

    int kategoriLaporan;
    char isiLaporan[200];
    char saranMasukan[200];
} Warga;

Warga db[100];
int jumlahWarga = 0;
const char *FILE_NAME = "dataWarga.txt";


// ==========================================================
// BAGIAN 2: HELPER FUNCTIONS
// ==========================================================

void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

long inputAngka(char *pesan) {
    char buffer[100];
    long angka;
    int valid = 0;
    while(!valid) {
        printf("%s", pesan);
        fgets(buffer, 100, stdin);
        char *endptr;
        angka = strtol(buffer, &endptr, 10);
        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
            printf("[!] Error: Harap masukkan angka yang valid!\n");
        } else valid = 1;
    }
    return angka;
}


// ==========================================================
// BAGIAN 3: LOGIKA & FILE HANDLING (UPDATED)
// ==========================================================

void hitungSkor(int i) {
    double skor = 0;
    if (db[i].pendapatan <= 1000000) skor += 40;
    else if (db[i].pendapatan <= 3000000) skor += 20;
    else skor += 10;

    skor += (db[i].tanggungan * 10);

    if (db[i].kondisiRumah == 3) skor += 30;
    else if (db[i].kondisiRumah == 2) skor += 10;

    if (db[i].statusKerja == 0) skor += 20;
    else if (db[i].statusKerja == 2) skor += 10;

    if (db[i].totalAset <= 10000000) skor += 20;
    else if (db[i].totalAset <= 50000000) skor += 10;

    db[i].skorAkhir = skor;

    if (skor >= 90) db[i].golongan = 1;
    else if (skor >= 75) db[i].golongan = 2;
    else if (skor >= 60) db[i].golongan = 3;
    else if (skor >= 45) db[i].golongan = 4;
    else if (skor >= 30) db[i].golongan = 5;
    else db[i].golongan = 6;
}

void simpanFile() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) return;

    // header tabel
    fprintf(fp, "========================================================================================================================\n");
    fprintf(fp, "| %-14s | %-25s | %-11s | %-11s | %-13s | %-13s | %-11s |\n",
        "NIK", "NAMA LENGKAP", "PENDAPATAN", "TANGGUNGAN", "KONDISI RUMAH", "STATUS KERJA", "TOTAL ASET");
    fprintf(fp, "========================================================================================================================\n");

    // isi
    for (int i = 0; i < jumlahWarga; i++) {
        // kondisiRumah dan statusKerja ditulis sebagai teks sederhana
        char kondisiText[20];
        if (db[i].kondisiRumah == 1) strcpy(kondisiText, "Layak");
        else if (db[i].kondisiRumah == 2) strcpy(kondisiText, "Sedang");
        else strcpy(kondisiText, "Rusak");

        char statusText[20];
        if (db[i].statusKerja == 1) strcpy(statusText, "Tetap");
        else if (db[i].statusKerja == 2) strcpy(statusText, "Kontrak");
        else strcpy(statusText, "Tidak");

        fprintf(fp, "| %-14s | %-25s | %11ld | %11d | %-13s | %-13s | %11ld |\n",
            db[i].nik,
            db[i].nama,
            db[i].pendapatan,
            db[i].tanggungan,
            kondisiText,
            statusText,
            db[i].totalAset
        );
    }

    fprintf(fp, "========================================================================================================================\n");
    fclose(fp);
}


void muatFile() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return;

    fscanf(fp, "%d\n", &jumlahWarga);
    for (int i = 0; i < jumlahWarga; i++) {
        char bufferNama[50], bufferLapor[200], bufferSaran[200];

        fscanf(fp, "%[^;];%[^;];%ld;%d;%d;%d;%ld;%d;%[^;];%[^\n]\n",
            db[i].nik, bufferNama, &db[i].pendapatan,
            &db[i].tanggungan, &db[i].kondisiRumah,
            &db[i].statusKerja, &db[i].totalAset,
            &db[i].kategoriLaporan, bufferLapor, bufferSaran);

        strcpy(db[i].nama, bufferNama);
        strcpy(db[i].isiLaporan, bufferLapor);
        strcpy(db[i].saranMasukan, bufferSaran);
        strcpy(db[i].password, "12345");

        hitungSkor(i);
    }
    fclose(fp);
}


// ==========================================================
// BAGIAN 4: FITUR ADMIN (CRUD)
// ==========================================================

void tambahWarga() {
    if (jumlahWarga >= 100) { printf("Database Penuh!\n"); return; }

    Warga b = {0};
    printf("\n--- INPUT DATA WARGA BARU ---\n");
    printf("NIK: "); scanf("%s", b.nik); getchar();
    printf("Nama Lengkap: "); fgets(b.nama, 50, stdin); b.nama[strcspn(b.nama, "\n")] = 0;

    b.pendapatan = inputAngka("Pendapatan (Rp): ");
    b.tanggungan = (int)inputAngka("Jumlah Tanggungan: ");
    b.kondisiRumah = (int)inputAngka("Kondisi Rumah (1.Layak 2.Sedang 3.Rusak): ");
    b.statusKerja = (int)inputAngka("Status Kerja (1.Tetap 2.Kontrak 0.Tidak): ");
    b.totalAset = inputAngka("Total Aset (Rp): ");

    strcpy(b.password, "12345");
    b.kategoriLaporan = 0;
    strcpy(b.isiLaporan, "-");
    strcpy(b.saranMasukan, "-");

    db[jumlahWarga] = b;
    hitungSkor(jumlahWarga);
    jumlahWarga++;
    simpanFile();
    printf(">>> Data berhasil disimpan! Tekan Enter..."); getchar();
}

void editWarga() {
    char cariNIK[20];
    int ditemukan = -1;
    printf("\n--- EDIT DATA WARGA ---\nMasukkan NIK Target: "); scanf("%s", cariNIK); getchar();
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(db[i].nik, cariNIK) == 0) { ditemukan = i; break; }
    }

    if (ditemukan == -1) { printf("[!] Data Tidak Ditemukan.\nTekan Enter..."); getchar(); return; }

    printf("\nData: %s (Skor: %.1f)\n", db[ditemukan].nama, db[ditemukan].skorAkhir);
    printf("--- Masukkan Data Baru ---\n");
    printf("Nama Baru: "); fgets(db[ditemukan].nama, 50, stdin);
    db[ditemukan].nama[strcspn(db[ditemukan].nama, "\n")] = 0;

    db[ditemukan].pendapatan = inputAngka("Pendapatan Baru: ");
    db[ditemukan].tanggungan = inputAngka("Tanggungan Baru: ");
    db[ditemukan].kondisiRumah = inputAngka("Kondisi Rumah (1.Layak 2.Sedang 3.Rusak): ");
    db[ditemukan].statusKerja = inputAngka("Status Kerja (1.Tetap 2.Kontrak 0.Tidak): ");
    db[ditemukan].totalAset = inputAngka("Total Aset Baru (Rp): ");

    printf("Apakah masalah laporan warga sudah selesai? (1.Ya 0.Tidak): ");
    if (inputAngka("") == 1) {
        db[ditemukan].kategoriLaporan = 0;
        strcpy(db[ditemukan].isiLaporan, "-");
    }

    hitungSkor(ditemukan);
    simpanFile();
    printf("[v] Data Update! Tekan Enter..."); getchar();
}

void hapusWarga() {
    char cariNIK[20];
    int ditemukan = -1;
    printf("\n--- HAPUS DATA WARGA ---\nCari NIK: ");
    scanf("%s", cariNIK); getchar();

    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(db[i].nik, cariNIK) == 0) { ditemukan = i; break; }
    }

    if (ditemukan != -1) {
        printf("Hapus %s (Gol: %d)? (y/n): ", db[ditemukan].nama, db[ditemukan].golongan);
        char yakin; scanf("%c", &yakin); getchar();
        if (yakin == 'y' || yakin == 'Y') {
            for (int j = ditemukan; j < jumlahWarga - 1; j++) db[j] = db[j + 1];
            jumlahWarga--; simpanFile();
            printf("[v] Terhapus.\n");
        } else printf("[x] Batal.\n");
    } else printf("[!] Tidak Ditemukan.\n");

    printf("Tekan Enter..."); getchar();
}


// ==========================================================
// BAGIAN 5: ADMIN - KOTAK MASUK & LAPORAN (FITUR BARU)
// ==========================================================

void menuKotakMasuk() {
    int pil;
    do {
        bersihkanLayar();
        printf("=== KOTAK MASUK ADMIN (LAPORAN & SARAN) ===\n");
        printf("1. Cek Kesalahan NIK\n");
        printf("2. Cek Kesalahan Nama\n");
        printf("3. Protes Prioritas/Golongan\n");
        printf("4. Laporan Bebas\n");
        printf("5. Lihat Semua Saran Warga\n");
        printf("0. Kembali\n");
        pil = (int)inputAngka("Pilih Kategori: ");

        if (pil >= 1 && pil <= 4) {
            bersihkanLayar();
            printf("--- DAFTAR LAPORAN KATEGORI %d ---\n", pil);
            int ada = 0;
            for (int i = 0; i < jumlahWarga; i++) {
                if (db[i].kategoriLaporan == pil) {
                    printf("Dari: %s (NIK: %s)\n", db[i].nama, db[i].nik);
                    printf("Isi Laporan: \"%s\"\n\n", db[i].isiLaporan);
                    ada = 1;
                }
            }
            if (!ada) printf("> Tidak ada laporan.\n");
            printf("Tekan Enter..."); getchar();
        }
        else if (pil == 5) {
            bersihkanLayar();
            printf("--- KOTAK SARAN ---\n");
            int ada = 0;
            for (int i = 0; i < jumlahWarga; i++) {
                if (strcmp(db[i].saranMasukan, "-") != 0) {
                    printf("Dari: %s (NIK: %s)\n", db[i].nama, db[i].nik);
                    printf("Saran: %s\n", db[i].saranMasukan);
                    printf("---------------------------\n");
                    ada = 1;
                }
            }
            if (!ada) printf("Belum ada saran.\n");
            printf("Enter..."); getchar();
        }

    } while (pil != 0);
}

void menuDataBansos() {
    int pil;
    do {
        bersihkanLayar();
        printf("=== DATA PRIORITAS BANSOS (GOL 1 & 2) ===\n");
        printf("1. Lihat Daftar\n2. Cari Warga\n0. Kembali\n");
        pil = inputAngka("Pilih: ");

        if (pil == 1) {
            bersihkanLayar();
            printf("| %-20s | %-5s | %-12s |\n", "NAMA", "GOL", "STATUS");
            printf("-----------------------------------------------\n");
            for (int i = 0; i < jumlahWarga; i++) {
                if (db[i].golongan <= 2)
                    printf("| %-20s | %-5d | PRIORITAS |\n", db[i].nama, db[i].golongan);
            }
            getchar();
        }
        else if (pil == 2) {
            char kw[50];
            printf("Nama/NIK: ");
            fgets(kw, 50, stdin);
            kw[strcspn(kw, "\n")] = 0;

            for (int i = 0; i < jumlahWarga; i++) {
                if ((strstr(db[i].nama, kw) || strcmp(db[i].nik, kw) == 0) && db[i].golongan <= 2)
                    printf(">> %s - Gol %d (Skor %.1f)\n", db[i].nama, db[i].golongan, db[i].skorAkhir);
            }
            getchar();
        }

    } while (pil != 0);
}

void sortBySkor(Warga db[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            if (db[j].skorAkhir < db[j + 1].skorAkhir) {
                Warga temp = db[j];
                db[j] = db[j + 1];
                db[j + 1] = temp;
            }
        }
    }
}

void tampilkanSemua() {
    bersihkanLayar();
    sortBySkor(db, jumlahWarga);
    printf("| %-14s | %-20s | %-6s | %-7s |\n", "NIK", "NAMA", "SKOR", "GOL");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < jumlahWarga; i++)
        printf("| %-14s | %-20s | %-6.1f | %-7d |\n", db[i].nik, db[i].nama, db[i].skorAkhir, db[i].golongan);
    printf("\n Enter..."); getchar();
}


// ==========================================================
// BAGIAN 6: FITUR USER BARU: LIHAT DATA PRIBADI
// ==========================================================

void lihatDataPribadi(int idx) {
    bersihkanLayar();
    printf("===== DATA PRIBADI WARGA =====\n");
    printf("NIK           : %s\n", db[idx].nik);
    printf("Nama          : %s\n", db[idx].nama);
    printf("Pendapatan    : %ld\n", db[idx].pendapatan);
    printf("Tanggungan    : %d\n", db[idx].tanggungan);

    printf("Kondisi Rumah : ");
    if (db[idx].kondisiRumah == 1) printf("Layak\n");
    else if (db[idx].kondisiRumah == 2) printf("Perlu Perbaikan\n");
    else printf("Tidak Layak\n");

    printf("Status Kerja  : ");
    if (db[idx].statusKerja == 1) printf("Tetap\n");
    else if (db[idx].statusKerja == 2) printf("Kontrak/Tidak Tetap\n");
    else printf("Tidak Bekerja\n");

    printf("Total Aset    : %ld\n", db[idx].totalAset);
    printf("Skor Akhir    : %.1f\n", db[idx].skorAkhir);
    printf("Golongan      : %d\n", db[idx].golongan);

    printf("\nTekan Enter untuk kembali...");
    getchar();
}


// ==========================================================
// BAGIAN 7: MENU USER (UPDATED)
// ==========================================================

void menuUser(int idx) {
    int pil;
    do {
        bersihkanLayar();
        printf("=== HALAMAN WARGA: %s ===\n", db[idx].nama);
        printf("1. Cek Status Bansos Saya\n");
        printf("2. Lapor Kesalahan Data (Klasifikasi)\n");
        printf("3. Kirim Masukan & Saran (Ke Admin)\n");
        printf("4. Lihat Data Pribadi Saya\n");   // FITUR BARU
        printf("0. Logout\n");
        pil = (int)inputAngka("Pilih: ");

        if (pil == 1) {
            printf("\nSkor: %.1f | Golongan: %d\n", db[idx].skorAkhir, db[idx].golongan);
            printf("STATUS: %s\n", (db[idx].golongan <= 2 ? "BERHAK MENERIMA BANSOS" : "TIDAK MENERIMA"));
            getchar();
        }
        else if (pil == 2) {
            printf("\n--- FORM PELAPORAN KESALAHAN ---\n");
            printf("1. Kesalahan NIK\n");
            printf("2. Kesalahan Nama\n");
            printf("3. Protes Prioritas\n");
            printf("4. Laporan Bebas\n");
            int kat = inputAngka("Kategori (1-4): ");

            if (kat >= 1 && kat <= 4) {
                db[idx].kategoriLaporan = kat;
                printf("Isi laporan: ");
                fgets(db[idx].isiLaporan, 200, stdin);
                db[idx].isiLaporan[strcspn(db[idx].isiLaporan, "\n")] = 0;
                simpanFile();
                printf("[v] Laporan terkirim!\n");
            }
            getchar();
        }
        else if (pil == 3) {
            printf("\n--- KOTAK SARAN ---\n");
            printf("Tulis saran: ");
            fgets(db[idx].saranMasukan, 200, stdin);
            db[idx].saranMasukan[strcspn(db[idx].saranMasukan, "\n")] = 0;
            simpanFile();
            printf("[v] Saran terkirim!\n");
            getchar();
        }
        else if (pil == 4) {
            lihatDataPribadi(idx);
        }

    } while (pil != 0);
}


// ==========================================================
// BAGIAN 8: MENU ADMIN
// ==========================================================

void menuAdmin() {
    int pil;
    do {
        bersihkanLayar();
        printf("=== ADMIN DASHBOARD ===\n");
        printf("1. Input Data Warga\n");
        printf("2. Edit Data (Search)\n");
        printf("3. Hapus Data\n");
        printf("4. Tampil Semua Data\n");
        printf("5. Data Penerima Bansos\n");
        printf("6. Cek Kotak Masuk (Laporan & Saran)\n");
        printf("0. Logout\n");
        pil = inputAngka("Pilih Menu: ");

        switch(pil) {
            case 1: tambahWarga(); break;
            case 2: editWarga(); break;
            case 3: hapusWarga(); break;
            case 4: tampilkanSemua(); break;
            case 5: menuDataBansos(); break;
            case 6: menuKotakMasuk(); break;
        }
    } while (pil != 0);
}


// ==========================================================
// MAIN PROGRAM
// ==========================================================

int main() {
    muatFile();

    char uName[20], pass[20];
    while (1) {
        bersihkanLayar();
        printf("=== SISTEM BANSOS GANDASARI ===\n");
        printf("Username: "); scanf("%s", uName);
        printf("Password: "); scanf("%s", pass); getchar();

        if (strcmp(uName, "admin") == 0 && strcmp(pass, "admin123") == 0)
            menuAdmin();
        else {
            int found = -1;
            for (int i = 0; i < jumlahWarga; i++) {
                if (strcmp(db[i].nik, uName) == 0 && strcmp(db[i].password, pass) == 0) {
                    found = i; break;
                }
            }
            if (found != -1) menuUser(found);
            else { printf("Login Gagal! Enter..."); getchar(); }
        }
    }
    return 0;
}
