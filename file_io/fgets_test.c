#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *ioFile = fopen("io.txt", "r");
    if (ioFile == NULL)
    {
        printf("not found the file.\n");
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), ioFile))
    {
        printf("%s", buffer);
    }
    
    int closeR = fclose(ioFile);
    if (closeR == EOF)
    {
        printf("faile to close.\n");
    }
    
    return 0;
}
