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
    if (mkfifo(pipe_path, 0664) != 0)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    fd = open(pipe_path, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[100];
    ssize_t read_num;
    while ((read_num = read(STDIN_FILENO, buf, 100)) > 0)
    {
        write(fd, buf, read_num);
    }

    if (read_num < 0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("发送数据到fifo管道完成\n");
    close(fd);
    if (unlink(pipe_path) == -1)
    {
        perror("unlink");
    }
    

    return 0;
}
