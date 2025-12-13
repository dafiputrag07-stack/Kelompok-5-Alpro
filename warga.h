#ifndef WARGA_H
#define WARGA_H

// definisi struct. 

typedef struct {
    float total_nilai_aset; 
    int luas_tanah;         
    int punya_motor;        
    int punya_mobil;        
} Aset;

typedef struct {
    char nik[20];
    char nama[50];
    char alamat[100];
    float penghasilan;
    int jumlah_tanggungan;
    Aset data_aset;
    float skor_kelayakan;   
    int is_prioritas;       
} Warga;

// percobaan fungsi
void generateDataDummy(Warga daftarWarga[], int *jumlahData, int jumlahYgDibuat);

#endif
