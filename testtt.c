#include <stdio.h>
#include <stdlib.h>

void inputData() {
    char nama[50];
    float penghasilan, aset;
    int tanggungan;

    FILE *fp = fopen("data_warga.txt", "a"); // mode append (tambah data)
    if (!fp) {
        printf("Gagal membuka file!\n");
        return;
    }

    getchar(); // membersihkan buffer sebelum fgets

    printf("\n=== Input Data Warga ===\n");

    printf("Masukkan nama warga        : ");
    fgets(nama, sizeof(nama), stdin);

    printf("Masukkan penghasilan (Rp) : ");
    scanf("%f", &penghasilan);

    printf("Masukkan total aset (Rp)  : ");
    scanf("%f", &aset);

    printf("Masukkan jumlah tanggungan: ");
    scanf("%d", &tanggungan);

    // Simpan ke file
    fprintf(fp, "%s %.2f %.2f %d\n", nama, penghasilan, aset, tanggungan);
    fclose(fp);

    printf("\nData berhasil disimpan!\n");
}

void lihatData() {
    FILE *fp = fopen("data_warga.txt", "r");
    if (!fp) {
        printf("Belum ada data tersimpan.\n");
        return;
    }

    char nama[50];
    float penghasilan, aset;
    int tanggungan;

    printf("\n=== Daftar Warga ===\n");

    int nomor = 1;
    while (fscanf(fp, " %[^\n] %f %f %d", nama, &penghasilan, &aset, &tanggungan) != EOF) {
        printf("\nWarga #%d\n", nomor++);
        printf("Nama        : %s\n", nama);
        printf("Penghasilan : Rp %.2f\n", penghasilan);
        printf("Aset        : Rp %.2f\n", aset);
        printf("Tanggungan  : %d orang\n", tanggungan);
    }

    fclose(fp);
}

int main() {
    int pilihan;

    do {
        printf("\n=== Menu Utama ===\n");
        printf("1. Input Data Warga\n");
        printf("2. Lihat Daftar Warga\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: inputData(); break;
            case 2: lihatData(); break;
            case 3: printf("Keluar program.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }

    } while (pilihan != 3);

    return 0;
}
