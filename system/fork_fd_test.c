#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    
    int fd = open("io.txt", O_CREAT | O_WRONLY | O_APPEND, 0664);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fail to fork");
    } else if (pid == 0) {
        //sub process
        strcpy(buffer, "这是子进程写的数据\n");
    } else {
        // parent process
        sleep(1);
        strcpy(buffer, "这是父进程写的数据\n");
    }
    // 父子进程都要执行的代码
    ssize_t bytes_write = write(fd, buffer, strlen(buffer));
    if (bytes_write == -1)
    {
        perror("fail to write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
    if (pid == 0)
    {
        printf("子进程写入完毕\n");
    } else {
        printf("父进程写入完毕\n");
    }
    
    
    
    return 0;
}
