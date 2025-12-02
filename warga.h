#ifndef WARGA_H
#define WARGA_H

// === DEFINISI STRUCT (Blueprint Data) ===
// Dibuat oleh: Anggota 02 (System Analyst)

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

// Prototype Fungsi (Hanya judul fungsinya saja)
void generateDataDummy(Warga daftarWarga[], int *jumlahData, int jumlahYgDibuat);

#endif
