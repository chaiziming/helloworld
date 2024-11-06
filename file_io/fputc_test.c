#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *filename = "io.txt";
    FILE *ioFile = fopen(filename, "w");
    if (ioFile == NULL) {
        printf("failed to open\n");
    } else {
        printf("success to open\n");
    }

    int put_result = fputc(97, ioFile);
    if (put_result == EOF) {
        printf("failed to write\n");
    } else {
        printf("success to write\n");
    }

    int result = fclose(ioFile);
    if (result == EOF) {
        printf("failed to close\n");
    } else {
        printf("success to close\n");
    }

    return 0;
}
