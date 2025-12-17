#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struktur.h"
#include "helper.h"
#include "menuAdmin.h"
#include "logika.h"
#include "menuUser.h"

int main() {

    muatFile();

    char uName[20], pass[20];
    while (1) {
        bersihkanLayar();
        printf("=== SISTEM BANSOS GANDASARI ===\n");
        printf("Username: "); scanf("%s", uName);
        printf("Password: "); scanf("%s", pass); getchar();

        if (strcmp(uName, "admin") == 0 && strcmp(pass, "admin123") == 0)
            menuAdmin();
        else {
            int found = -1;
            for (int i = 0; i < jumlahWarga; i++) {
                if (strcmp(db[i].nik, uName) == 0 && strcmp(db[i].password, pass) == 0) {
                    found = i; break;
                }
            }
            if (found != -1) menuUser(found);
            else { printf("Login Gagal! Enter..."); getchar(); }
        }
    }
    return 0;
}
