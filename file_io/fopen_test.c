#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *filename = "io.txt";
    FILE *ioFile = fopen(filename, "a");
    if (ioFile == NULL) {
        printf("failed to open\n");
    } else {
        printf("success to open\n");
    }
    return 0;
}
