#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 1 创建一个共享内存对象
    char *share;
    char shm_name[100] = {0};
    sprintf(shm_name, "/letter%d", getpid());
    int shm_fd;
    shm_fd = shm_open(shm_name, O_RDWR | O_CREAT, 0664);
    if (shm_fd < 0)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    // 2 设置共享内存大小
    ftruncate(shm_fd, 1024);

    // 3 内存映射 mmap
    share = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (share == MAP_FAILED)
    {
        perror("mmap");
    }

    // 映射完成后关闭, 但不是释放
    close(shm_fd);

    // 4 使用共享内存进行进程间通信
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fail to fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // 子进程
        strcpy(share, "你是个好人\n");
    }
    else
    {
        // 父进程
        waitpid(pid, NULL, 0);
        printf("我收到来信：%s", share);
        // 5 释放映射区
        int re = munmap(share, 1024);
        if (re == -1)
        {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
        
    }

    shm_unlink(shm_name);

    return 0;
}
