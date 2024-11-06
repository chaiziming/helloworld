#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    
    int fd = open("io.txt", O_CREAT | O_WRONLY | O_APPEND, 0664);
    return 0;
}
