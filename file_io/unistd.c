#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    //https://www.man7.org/linux/man-pages/man2/open.2.html
    int fd = open("io1.txt", O_RDONLY | O_CREAT, 0664);
    if (fd == -1)
    {
        printf("fail to open");
    }
    
    return 0;
}
