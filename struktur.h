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
