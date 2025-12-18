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

/// DATA BANSOS
void menuDataBansos() 
{
    int pilMenu, pilSub;

    do 
    {
        bersihkanLayar();
        printf("=== DATA BANSOS WARGA ===\n");
        printf("1. Data Prioritas Bansos\n");
        printf("2. Data Non Prioritas Bansos\n");
        printf("0. Kembali\n");
        pilMenu = inputAngka("Pilih: ");

        if (pilMenu == 1 || pilMenu == 2) 
        {
            do 
            {
                bersihkanLayar();
                printf("1. Lihat Daftar\n");
                printf("2. Cari Warga\n");
                printf("0. Kembali\n");
                pilSub = inputAngka("Pilih: ");

                if (pilSub == 1) 
                {
                    bersihkanLayar();
                    printf("| %-20s | %-5s | %-12s |\n", "NAMA", "GOL", "STATUS");
                    printf("-----------------------------------------------\n");

                    for (int i = 0; i < jumlahWarga; i++) 
                    {
                        if ((pilMenu == 1 && db[i].golongan <= 2) ||
                            (pilMenu == 2 && db[i].golongan >= 3)) 
                        {

                            printf("| %-20s | %-5d | %s |\n",
                                   db[i].nama,
                                   db[i].golongan,
                                   (pilMenu == 1 ? "PRIORITAS" : "NON PRIORITAS"));
                        }
                    }
                    getchar();
                }
                else if (pilSub == 2) 
                {
                    cariData();
                    for (int i = 0; i < jumlahWarga; i++) 
                    {
                        if (db[i].golongan <= 2)
                            printf(">> %s - Gol %d (Skor %.1f)\n", db[i].nama, db[i].golongan, db[i].skorAkhir);
                    }
                    getchar();
                }
            } 
              while (pil != 0);
            }
        }
            else if (pil == 2) 
    {
            do 
            {
                bersihkanLayar();
                printf("=== DATA NON PRIORITAS BANSOS (GOL 3 - 6) ===\n");
                printf("1. Lihat Daftar\n2. Cari Warga\n0. Kembali\n");
                pil = inputAngka("Pilih: ");

                if (pil == 1) 
                {
                    bersihkanLayar();
                    printf("| %-20s | %-5s | %-12s |\n", "NAMA", "GOL", "STATUS");
                    printf("-----------------------------------------------\n");
                    for (int i = 0; i < jumlahWarga; i++) 
                    {
                        if (db[i].golongan >= 2)
                            printf("| %-20s | %-5d | NON PRIORITAS |\n", db[i].nama, db[i].golongan);
                    }
                    getchar();
                }
                else if (pil == 2) 
                {
                    cariData();
                    for (int i = 0; i < jumlahWarga; i++) 
                    {
                        if (db[i].golongan >= 2)
                            printf(">> %s - Gol %d (Skor %.1f)\n", db[i].nama, db[i].golongan, db[i].skorAkhir);
                    }
                    getchar();
                }
            }
              while (pil != 0);
        }
    } while (pil != 0);

