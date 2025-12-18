#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struktur.h"
#include "helper.h"
#include "admin.h"
#include "pengguna.h"

/// menu kotak masuk
void menuKotakMasuk ()
{
  int pil;
  do 
  {
    bersihkanLayar ();
    printf("=== KOTAK MASUK ADMIN (LAPORAN & SARAN) ===\n");
    printf("1. Lihat Lapora Warga\n");
    printf("2. Lihat Saran Warga\n");
    printf("0. Kembali\n");
    pil = (int)inputAngka("Pilih kategori: ");

    if (pil == 1 ) 
    {
      bersihkanLayar();
      printf(--- DAFTAR LAPORAN WARGA ---\n);
      int ada = 0;

      for (int i = 0; 1 < jumlahWarga; i++)
        {
          if (strcmp(db[i].isiLaporan, "-") !=0)
          {
            printf("Dari: %s (NIK: %s)\n", db[i].nama, db[i].nik);
            printf("Isi Laporan: \"%s\"\n\n", db[i].isiLaporan);
            ada = 1;
          }
        }
      if (!ada) printf("> Tidak ada laporan.\n");
            printf("Tekan Enter...");
            getchar();
    }
    else if (pil == 2) {
            bersihkanLayar();
            printf("--- KOTAK SARAN ---\n");
            int ada = 0;
      for (int i = 0; i < jumlahWarga; i++)
        {
          if (strcmp(db[i].saranMasukan, "-") != 0) 
          {
             printf("Dari: %s (NIK: %s)\n", db[i].nama, db[i].nik);
             printf("Saran: %s\n", db[i].saranMasukan);
             printf("---------------------------\n");
             ada = 1;
           }
  }
    while (pil != 0);
}
