#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){


#ifndef struktur
#define struktur

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
    char isiLaporan[200];
    char saranMasukan[200];
} Warga;

extern Warga db[100];
extern int jumlahWarga;
extern const char *FILE_NAME;

#endif

Warga db[100];
int jumlahWarga = 0;
const char *FILE_NAME = "dataWarga.txt";




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
        angka = strtol (buffer, &endptr, 10);
        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
            printf("[!] Error: Harap masukkan angka yang valid!\n");
        } else valid = 1;
    }
    return angka;
}

void cariData() {
    char cariDataWarga[50];
        printf("Nama/NIK: ");
        fgets(cariDataWarga, 50, stdin);
        cariDataWarga[strcspn(cariDataWarga, "\n")] = 0;
    int ditemukan = -1;
        for (int i = 0; i < jumlahWarga; i++) {
            if (strstr(db[i].nama, cariDataWarga) != NULL || strcmp(db[i].nik, cariDataWarga) == 0){
            ditemukan = i;
            }
        }
    }


    #ifndef helper
#define helper

void bersihkanLayar();
long inputAngka(char *pesan);
void cariData();

#endif



void hitungSkor(int i) {
    double skor = 0;
    if (db[i].pendapatan <= 1000000) skor += 40;
    else if (db[i].pendapatan <= 3000000) skor += 20;
    else skor += 10;

    skor += (db[i].tanggungan * 10);

    if (db[i].kondisiRumah == 3) skor += 30;
    else if (db[i].kondisiRumah == 2) skor += 10;

    if (db[i].statusKerja == 3) skor += 20;
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

    fprintf(fp, "%d\n", jumlahWarga);

    for (int i = 0; i < jumlahWarga; i++) {
        fprintf(fp, "%s;%s;%ld;%d;%d;%d;%ld;%d;%s;%s\n",
            db[i].nik,
            db[i].nama,
            db[i].pendapatan,
            db[i].tanggungan,
            db[i].kondisiRumah,
            db[i].statusKerja,
            db[i].totalAset,
            db[i].isiLaporan,
            db[i].saranMasukan
        );
    }
    fclose(fp);
}


void muatFile() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Database belum ada atau gagal dibuka.\n");
        return;
    }

    fscanf(fp, "%d\n", &jumlahWarga);

    for (int i = 0; i < jumlahWarga; i++) {
        fscanf(fp, "%[^;];%[^;];%ld;%d;%d;%d;%ld;%[^;];%[^\n]\n",
            db[i].nik,
            db[i].nama,
            &db[i].pendapatan,
            &db[i].tanggungan,
            &db[i].kondisiRumah,
            &db[i].statusKerja,
            &db[i].totalAset,
            db[i].isiLaporan,
            db[i].saranMasukan
        );

        strcpy(db[i].password, "12345");

        hitungSkor(i);
    }
    fclose(fp);
}


#ifndef logika
#define logika

void hitungSkor(int i);
void simpanFile();
void muatFile();

#endif



void tambahWarga() {
    if (jumlahWarga >= 100) { printf("Database Penuh!\n"); return; }

    Warga b = {0};
    printf("\n--- INPUT DATA WARGA BARU ---\n");
    printf("NIK: "); scanf("%s", b.nik); getchar();
    printf("Nama Lengkap: "); fgets(b.nama, 50, stdin); b.nama[strcspn(b.nama, "\n")] = 0;
    b.pendapatan = inputAngka("Pendapatan (Rp): ");
    b.tanggungan = (int)inputAngka("Jumlah Tanggungan: ");
    b.kondisiRumah = (int)inputAngka("Kondisi Rumah (1.Layak 2.Sedang 3.Rusak): ");
    b.statusKerja = (int)inputAngka("Status Kerja (1.Tetap 2.Kontrak 3.Tidak): ");
    b.totalAset = inputAngka("Total Aset (Rp): ");

    strcpy(b.password, "12345");
    strcpy(b.isiLaporan, "-");
    strcpy(b.saranMasukan, "-");

    db[jumlahWarga] = b;
    hitungSkor(jumlahWarga);
    jumlahWarga++;
    simpanFile();
    printf(">>> Data berhasil disimpan! Tekan Enter..."); getchar();
}

void editWarga() {
    char cariDataWarga[50];
    int ditemukan = -1;
    printf("\n--- EDIT DATA WARGA ---\n");
    printf("Nama/NIK: ");
    fgets(cariDataWarga, 50, stdin);
    cariDataWarga[strcspn(cariDataWarga, "\n")] = 0;
    for (int i = 0; i < jumlahWarga; i++) {
        if (strstr(db[i].nama, cariDataWarga) != NULL ||strcmp(db[i].nik, cariDataWarga) == 0) { ditemukan = i; break; }
    }
        if (ditemukan != -1) {
            printf("\nData: %s (Skor: %.1f)\n", db[ditemukan].nama, db[ditemukan].skorAkhir);
            printf("--- Masukkan Data Baru ---\n");
            printf("Nama Baru: "); fgets(db[ditemukan].nama, 50, stdin);
            db[ditemukan].nama[strcspn(db[ditemukan].nama, "\n")] = 0;
            db[ditemukan].pendapatan = inputAngka("Pendapatan Baru: ");
            db[ditemukan].tanggungan = inputAngka("Tanggungan Baru: ");
            db[ditemukan].kondisiRumah = inputAngka("Kondisi Rumah (1.Layak 2.Sedang 3.Rusak): ");
            db[ditemukan].statusKerja = inputAngka("Status Kerja (1.Tetap 2.Kontrak 3.Tidak): ");
            db[ditemukan].totalAset = inputAngka("Total Aset Baru (Rp): ");

            hitungSkor(ditemukan);
            simpanFile();
            printf("[v] Data Update! Tekan Enter...");
            getchar();
        } else printf("[!] Tidak Ditemukan.\n");

        printf("Tekan Enter..."); getchar();
    }



void hapusWarga() {
    char cariDataWarga[50];
    int ditemukan = -1;
    printf("\n--- HAPUS DATA WARGA ---\n");
    printf("Nama/NIK: ");
    fgets(cariDataWarga, 50, stdin);
    cariDataWarga[strcspn(cariDataWarga, "\n")] = 0;
    for (int i = 0; i < jumlahWarga; i++) {
        if (strstr(db[i].nama, cariDataWarga) != NULL ||strcmp(db[i].nik, cariDataWarga) == 0) { ditemukan = i; break; }
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


#ifndef fitur_admin
#define fitur_admin

void tambahWarga();
void editWarga();
void hapusWarga();

#endif


Warga db[100];
int jumlahWarga = 0;
const char *FILE_NAME = "dataWarga.txt";

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


#ifndef pengguna
#define pengguna

void lihatDataPribadi(int idx);

#endif




void menuKotakMasuk() {
    int pil;
    do {
        bersihkanLayar();
        printf("=== KOTAK MASUK ADMIN (LAPORAN & SARAN) ===\n");
        printf("1. Lihat Laporan Warga\n");
        printf("2. Lihat Saran Warga\n");
        printf("0. Kembali\n");
        pil = (int)inputAngka("Pilih Kategori: ");

        if (pil == 1) {
            bersihkanLayar();
            printf("--- DAFTAR LAPORAN WARGA %d ---\n", pil);
            int ada = 0;
            for (int i = 0; i < jumlahWarga; i++) {
                if (strcmp(db[i].isiLaporan, "-") != 0) {
                    printf("Dari: %s (NIK: %s)\n", db[i].nama, db[i].nik);
                    printf("Isi Laporan: \"%s\"\n\n", db[i].isiLaporan);
                    ada = 1;
                }
            }
            if (!ada) printf("> Tidak ada laporan.\n");
            printf("Tekan Enter..."); getchar();
        }
        else if (pil == 2) {
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
        printf("=== DATA BANSOS WARGA ===\n");
        printf("1. Data Prioritas Bansos\n2. Data Non Prioritas Bansos\n0. Kembali\n");
        pil = inputAngka("Pilih: ");

        if (pil == 1) {
            do {
                bersihkanLayar();
                printf("=== DATA PRIORITAS BANSOS (GOL 1 & 2) ===\n");
                printf("1. Lihat Daftar\n2. Cari Warga\n0. Kembali\n");
                pil = inputAngka("Pilih: ");

                if (pil == 1) {
                    bersihkanLayar();
                    printf("| %-30s | %-5s | %-12s |\n", "NAMA", "GOL", "STATUS");
                    printf("-----------------------------------------------\n");
                    for (int i = 0; i < jumlahWarga; i++) {
                        if (db[i].golongan <= 2)
                            printf("| %-30s | %-5d | PRIORITAS |\n", db[i].nama, db[i].golongan);
                    }
                    getchar();
                }
                else if (pil == 2) {
                    char cariDataWarga[50];
                    int ditemukan = -1;
                    printf("\n--- CARI DATA WARGA PRIORITAS BANSOS ---\n");
                    printf("Nama/NIK: ");
                    fgets(cariDataWarga, 50, stdin);
                    cariDataWarga[strcspn(cariDataWarga, "\n")] = 0;
                    for (int i = 0; i < jumlahWarga; i++) {
                        if (strstr(db[i].nama, cariDataWarga) != NULL || strcmp(db[i].nik, cariDataWarga) == 0 && db[i].golongan <= 2) {
                            ditemukan = i;
                            printf(">> %s - Gol %d (Skor %.1f)\n", db[i].nama, db[i].golongan, db[i].skorAkhir);
                        break; }
                    }
                    getchar();
                }
            } while (pil != 0);
        }
        else if (pil == 2) {
            do {
                bersihkanLayar();
                printf("=== DATA NON PRIORITAS BANSOS (GOL 3 - 6) ===\n");
                printf("1. Lihat Daftar\n2. Cari Warga\n0. Kembali\n");
                pil = inputAngka("Pilih: ");

                if (pil == 1) {
                    bersihkanLayar();
                    printf("| %-30s | %-5s | %-12s |\n", "NAMA", "GOL", "STATUS");
                    printf("-----------------------------------------------\n");
                    for (int i = 0; i < jumlahWarga; i++) {
                        if (db[i].golongan >= 2)
                            printf("| %-30s | %-5d | NON PRIORITAS |\n", db[i].nama, db[i].golongan);
                    }
                    getchar();
                }
                else if (pil == 2) {
                    char cariDataWarga[50];
                    int ditemukan = -1;
                    printf("\n--- CARI DATA WARGA NON PRIORITAS BANSOS ---\n");
                    printf("Nama/NIK: ");
                    fgets(cariDataWarga, 50, stdin);
                    cariDataWarga[strcspn(cariDataWarga, "\n")] = 0;
                    for (int i = 0; i < jumlahWarga; i++) {
                        if (strstr(db[i].nama, cariDataWarga) != NULL || strcmp(db[i].nik, cariDataWarga) == 0 && db[i].golongan >= 2) {
                            ditemukan = i;
                            printf(">> %s - Gol %d (Skor %.1f)\n", db[i].nama, db[i].golongan, db[i].skorAkhir);
                            break; }
                    }
                    getchar();
                }
            } while (pil != 0);
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
void lihatDataPribadi();

void tampilkanSemua() {
    int pil;
    do {
        bersihkanLayar();
        printf("=== DATA WARGA ===\n");
        printf("1. Tampilkan Semua Data Warga \n2. Cari Data Warga \n0. Kembali\n");
        pil = inputAngka("Pilih: ");

        if (pil == 1) {
            bersihkanLayar();
            sortBySkor(db, jumlahWarga);
            printf("| %-18s | %-40s | %-6s | %-7s |\n", "NIK", "NAMA", "SKOR", "GOL");
            printf("----------------------------------------------------------\n");
            for (int i = 0; i < jumlahWarga; i++)
                printf("| %-18s | %-40s | %-6.1f | %-7d |\n", db[i].nik, db[i].nama, db[i].skorAkhir, db[i].golongan);
            printf("\n Enter..."); getchar();
        } else if (pil == 2) {
                char cariDataWarga[50];
                int ditemukan = -1;
                printf("\n--- CARI DATA WARGA ---\n");
                printf("Nama/NIK: ");
                fgets(cariDataWarga, 50, stdin);
                cariDataWarga[strcspn(cariDataWarga, "\n")] = 0;
                for (int i = 0; i < jumlahWarga; i++) {
                    if (strstr(db[i].nama, cariDataWarga) != NULL || strcmp(db[i].nik, cariDataWarga) == 0) {
                        ditemukan = i;
                        lihatDataPribadi(ditemukan);
                        break;
                    }
                }
                if (ditemukan == -1) {
                    printf("[!] Data warga tidak ditemukan.\n");
                }
                printf("\n Enter..."); getchar();
            }
        } while (pil != 0);
    }


    #ifndef admin
#define admin

void menuKotakMasuk();
void menuDataBansos();
void tampilkanSemua();

#endif




void menuAdmin() {
    int pil;
    do {
        bersihkanLayar();
        printf("=== ADMIN DASHBOARD ===\n");
        printf("1. Input Data Warga\n");
        printf("2. Edit Data \n");
        printf("3. Hapus Data\n");
        printf("4. Tampil Semua Data\n");
        printf("5. Data Bansos\n");
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



#ifndef menu_admin
#define menu_admin

void menuAdmin();

#endif


void menuUser(int idx) {
    int pil;
    do {
        bersihkanLayar();
        printf("=== HALAMAN WARGA: %s ===\n", db[idx].nama);
        printf("1. Cek Status Bansos Saya\n");
        printf("2. Lapor Kesalahan Data \n");
        printf("3. Kirim Masukan & Saran (Ke Admin)\n");
        printf("4. Lihat Data Pribadi Saya\n");
        printf("0. Logout\n");
        pil = (int)inputAngka("Pilih: ");

        if (pil == 1) {
            printf("\nSkor: %.1f | Golongan: %d\n", db[idx].skorAkhir, db[idx].golongan);
            printf("STATUS: %s\n", (db[idx].golongan <= 2 ? "BERHAK MENERIMA BANSOS" : "TIDAK MENERIMA BANSOS"));
            getchar();
        }
        else if (pil == 2) {
            printf("\n--- KOTAK LAPORAN ---\n");
            printf("Tulis Laporan: ");
            fgets(db[idx].isiLaporan, 200, stdin);
            db[idx].isiLaporan[strcspn(db[idx].isiLaporan, "\n")] = 0;
            simpanFile();
            printf("[v] Laporan terkirim!\n");
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




#ifndef menu_user
#define menu_user

void menuUser(int idx);

#endif




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
