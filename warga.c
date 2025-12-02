#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "warga.h" // PENTING: Sambungkan ke file header di atas

// === IMPLEMENTASI FUNGSI ===
// Dibuat oleh: Anggota 02

void generateDataDummy(Warga daftarWarga[], int *jumlahData, int jumlahYgDibuat) {
    srand(time(NULL)); 
    char *namaDepan[] = {"Budi", "Siti", "Asep", "Dewi", "Joko"};
    char *namaBelakang[] = {"Santoso", "Aminah", "Kurnia", "Lestari", "Widodo"};

    printf(">> System: Menjana %d data dummy...\n", jumlahYgDibuat);

    for (int i = 0; i < jumlahYgDibuat; i++) {
        sprintf(daftarWarga[i].nik, "320101%04d", i + 1);
        sprintf(daftarWarga[i].nama, "%s %s", namaDepan[rand()%5], namaBelakang[rand()%5]);
        sprintf(daftarWarga[i].alamat, "Gandasari Blok %c", 'A' + (rand() % 5));
        
        daftarWarga[i].penghasilan = (rand() % 4500000) + 500000;
        daftarWarga[i].data_aset.total_nilai_aset = (rand() % 50000000);
        daftarWarga[i].data_aset.punya_motor = rand() % 2;
        daftarWarga[i].jumlah_tanggungan = rand() % 6;
        
        daftarWarga[i].skor_kelayakan = 0;
        daftarWarga[i].is_prioritas = 0;
    }
    *jumlahData = jumlahYgDibuat;
    //#include "warga.h" (Jangan lupa compile file warga.c juga saat menjalankan program)
}
