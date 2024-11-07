#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int fd;
    char *pipe_path = "/tmp/myfifo";
    // if (mkfifo(pipe_path, 0664) != 0)
    // {
    //     perror("mkfifo");
    //     exit(EXIT_FAILURE);
    // }

    fd = open(pipe_path, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[100];
    ssize_t read_num;
    while ((read_num = read(fd, buf, 100)) > 0)
    {
        write(STDOUT_FILENO, buf, read_num);
    }
    

    if (read_num < 0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("从fifo管道接受数据完成\n");
    close(fd);

    return 0;
}
