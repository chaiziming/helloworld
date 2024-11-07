#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    pid_t cpid;
    int pipefd[2];

    //将argv 的第一个参数用管道传递给子进程
    if (argc =! 2)
    {
        fprintf(stderr, "%s: 缺少参数", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    //创建管道
    if (pipe(pipefd) == -1)
    {
        perror("fail to create pipe");
        exit(EXIT_FAILURE);
    }
    

    cpid = fork();
    if (cpid == -1)
    {
        perror("fail to fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        //子进程读管道里的数据
        close(pipefd[1]);
        char *str = "接受信息\n";
        write(STDOUT_FILENO, str, strlen(str));
        char buf;
        while (read(pipefd[0], &buf, 1) > 0)
        {
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    } else {
        //父进程写入数据到管道里
        close(pipefd[0]);
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);
        waitpid(cpid, NULL, 0);
        exit(EXIT_SUCCESS);
    }
    
    

    return 0;
}
