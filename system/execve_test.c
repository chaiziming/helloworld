#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char *name = "班长";
    printf("我是%s 编号: %d\n", name, getpid());

    char *args[] = {"/home/czm/work/c/system/erlou", name, NULL};
    char *envs[] = {NULL};
    int re = execve("/home/czm/work/c/system/erlou", args, envs);
    if (re == -1)
    {
        printf("file to execve");
        return 1;
    }
    //此处的代码执行不到，已经跳转到execve 执行的程序里了
    

    return 0;
}
