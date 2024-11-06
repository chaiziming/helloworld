#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *filename = "io.txt";
    FILE *ioFile = fopen(filename, "a+");
    if (ioFile == NULL) {
        printf("failed to open\n");
    } else {
        printf("success to open\n");
    }

    int puts_result = fputs(" love letter\n", ioFile);
    if (puts_result == EOF)
    {
        printf("failed to write\n");
    } else {
        printf("'%d' success to write\n", puts_result);
    }
    

    int result = fclose(ioFile);
    if (result == EOF) {
        printf("failed to close\n");
    } else {
        printf("success to close\n");
    }

    return 0;
}
