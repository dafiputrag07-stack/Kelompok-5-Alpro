#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struktur.h"
#include "helper.h"
#include "logika.h"
#include "fiturAdmin.h"


void tambahWarga() {
    if (jumlahWarga >= 100) { printf("Database Penuh!\n"); return; }

    Warga b = {0};
    printf("\n--- INPUT DATA WARGA BARU ---\n");
    b.nik = inputAngka("Pendapatan (Rp): "); getchar();
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
    printf("\n--- EDIT DATA WARGA ---\n");
    cariData();
        for (int i = 0; i < jumlahWarga; i++) {
        printf("\nData: %s (Skor: %.1f)\n", db[i].nama, db[i].skorAkhir);
        printf("--- Masukkan Data Baru ---\n");
        printf("Nama Baru: "); fgets(db[i].nama, 50, stdin);
        db[i].nama[strcspn(db[i].nama, "\n")] = 0;
        db[i].pendapatan = inputAngka("Pendapatan Baru: ");
        db[i].tanggungan = inputAngka("Tanggungan Baru: ");
        db[i].kondisiRumah = inputAngka("Kondisi Rumah (1.Layak 2.Sedang 3.Rusak): ");
        db[i].statusKerja = inputAngka("Status Kerja (1.Tetap 2.Kontrak 3.Tidak): ");
        db[i].totalAset = inputAngka("Total Aset Baru (Rp): ");

        hitungSkor(i);
        simpanFile();
        printf("[v] Data Update! Tekan Enter..."); getchar();
    }
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
