#pragma warning(disable:4996)

#include <cstdio>
#include <cstdlib>
#include <conio.h>

/*
    Source by CPPReference (https://en.cppreference.com)
    Modified For Learn by RK
    I.D.E : VS2022
*/

int main() {
    // Siapkan array nilai floating-point.
    const int SIZE = 5;
    double A[SIZE] = { 1., 2., 3., 4., 5. };
    // Tulis array ke file.
    std::FILE* fp = std::fopen("test.bin", "wb");
    std::fwrite(A, sizeof(double), SIZE, fp);
    std::fclose(fp);

    // Baca nilai ke dalam array B.
    double B[SIZE];
    fp = std::fopen("test.bin", "rb");
    std::fpos_t pos;
    
    if (std::fgetpos(fp, &pos) != 0) {     // posisi saat ini: awal file 
        std::perror("fgetpos()");
        std::fprintf(stderr, "fgetpos() failed in file %s at line # %d\n", __FILE__, __LINE__ - 3);
        std::exit(EXIT_FAILURE);
    }

    int ret_code = std::fread(B, sizeof(double), 1, fp);      // membaca satu nilai
    // posisi saat ini: setelah membaca satu nilai
    std::printf("%.1f; read count = %d\n", B[0], ret_code);   // cetak satu nilai dan ret_code

    if (std::fsetpos(fp, &pos) != 0) { // atur ulang posisi saat ini ke awal file
        if (std::ferror(fp)) {
            std::perror("fsetpos()");
            std::fprintf(stderr, "fsetpos() failed in file %s at line # %d\n",
                __FILE__, __LINE__ - 5);
            std::exit(EXIT_FAILURE);
        }
    }

    ret_code = std::fread(B, sizeof(double), 1, fp);         // baca ulang nilai pertama
    std::printf("%.1f; read count = %d\n", B[0], ret_code);  // cetak satu nilai dan ret_code
    std::fclose(fp);

    _getch();
    return EXIT_SUCCESS;
}