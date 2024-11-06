#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd = open("io22.txt", O_RDONLY);
    if (fd == -1)
    {
        // printf("fail to open\n");
        perror("open22");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1)
    {
        printf("fail to read\n");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
     

    return 0;
}
