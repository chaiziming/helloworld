#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    //邀请之前
    char *name = "老学员";
    printf("%s %d在一楼\n", name, getpid());

    //
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("fail to fork\n");
        return 1;
    } else if (pid == 0) {
        //子进程
        char *new_name = "新学员";
        char *args[] = {"/home/czm/work/c/system/erlou", new_name, NULL};
        char *envs[] = {NULL};
        int exR = execve("/home/czm/work/c/system/erlou", args, envs);
        if (exR == -1)
        {
            printf("新学员失败了\n");
            return 1;
        }
        //这里不执行了
    } else {
        printf("老学员继续学习\n");
        //永久挂起，等待直到输入任意字符
        char byte = fgetc(stdin);
    }
    

    return 0;
}
