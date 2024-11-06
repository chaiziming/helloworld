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

    char *name = "哈哈";
    int printf_result = fprintf(ioFile, "士大夫 %s", name);
    if (printf_result == EOF)
    {
        printf("failed to wraite\n");
    } else {
        printf("success to wraite\n");
    }
    

    int result = fclose(ioFile);
    if (result == EOF) {
        printf("failed to close\n");
    } else {
        printf("success to close\n");
    }

    return 0;
}
