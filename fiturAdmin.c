#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struktur.h"
#include "helper.h"
#include "logika.h"
#include "fiturAdmin.h"


void tambahWarga() {
    if (jumlahWarga >= 100) { 
        printf("Database Penuh!\n"); 
        return; 
    }
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
    printf(">>> Data berhasil disimpan! Tekan Enter...");
    getchar();
}

void editWarga() {
    char cariDataWarga[50];
    int ditemukan = -1;
    printf("\n--- EDIT DATA WARGA ---\n");
    printf("Nama/NIK: ");
    fgets(cariDataWarga, 50, stdin);
    cariDataWarga[strcspn(cariDataWarga, "\n")] = 0;
    for (int i = 0; i < jumlahWarga; i++) {
        if (strstr(db[i].nama, cariDataWarga) != NULL ||strcmp(db[i].nik, cariDataWarga) == 0) { 
            ditemukan = i; 
            break;
        }
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
        } else 
            printf("[!] Tidak Ditemukan.\n");
            printf("Tekan Enter..."); 
            getchar();
    }

void hapusWarga() {
    char cariDataWarga[50];
    int ditemukan = -1;
    printf("\n--- HAPUS DATA WARGA ---\n");
    printf("Nama/NIK: ");
    fgets(cariDataWarga, 50, stdin);
    cariDataWarga[strcspn(cariDataWarga, "\n")] = 0;
    for (int i = 0; i < jumlahWarga; i++) {
        if (strstr(db[i].nama, cariDataWarga) != NULL ||strcmp(db[i].nik, cariDataWarga) == 0) { 
            ditemukan = i; 
            break; 
        }
    }
    if (ditemukan != -1) {
        printf("Hapus %s (Gol: %d)? (y/n): ", db[ditemukan].nama, db[ditemukan].golongan);
        char yakin; scanf("%c", &yakin); getchar();
        if (yakin == 'y' || yakin == 'Y') {
            for (int j = ditemukan; j < jumlahWarga - 1; j++) db[j] = db[j + 1];
            jumlahWarga--; simpanFile();
            printf("[v] Terhapus.\n");
        } else 
            printf("[x] Batal.\n");
    } else 
        printf("[!] Tidak Ditemukan.\n");
        printf("Tekan Enter..."); 
        getchar();
}
