#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *ioFile = fopen("io.txt", "r");
    if (ioFile == NULL)
    {
        printf("not found the file.\n");
    }

    char c = fgetc(ioFile);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(ioFile);
    }
    printf("\n");
    
    int closeR = fclose(ioFile);
    if (closeR == EOF)
    {
        printf("faile to close.\n");
    }
    
    return 0;
}
