#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *ioFile = fopen("user.txt", "r");
    if (ioFile == NULL)
    {
        printf("not found the file.\n");
    }

    char name[50];
    int age;
    char wife[50];
    int scanR;
    while ((scanR = fscanf(ioFile, "%s %d %s", name, &age, wife)) != EOF)
    {
        printf("%d\n", scanR);
        printf("%s在%d岁的时候爱上了%s\n", name, age, wife);
    }
    
    
    int closeR = fclose(ioFile);
    if (closeR == EOF)
    {
        printf("faile to close.\n");
    }
    
    return 0;
}
