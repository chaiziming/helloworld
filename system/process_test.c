#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int num = 0;

int main(int argc, char const *argv[])
{
    int subprocess_status;
    __pid_t pid = fork();
    if (pid < 0)
    {
        perror("fail to fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        //子进程
        num = 1;
        printf("子进程的 num:%d\n", num);
    } else {
        //父进程
        waitpid(pid, &subprocess_status, 0);
        printf("父进程的 num:%d\n", num);
    }
    
    
    return 0;
}
