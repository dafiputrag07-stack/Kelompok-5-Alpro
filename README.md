#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struktur.h"
#include "helper.h"
#include "pengguna.h"

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
