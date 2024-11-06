#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    //调用fork之前，运行的代码都是父进程的
    printf("老学员id: %d\n", getpid());
    
    //-1：出错
    //在子进程中显示的是 0
    //在父进程中显示的是子进程的 pid
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("fail to fork\n");
        return 1;
    } else if (pid == 0) {
        //子进程
        printf("新学员id: %d\n", getpid());
        printf("推荐新学员的老学员id: %d\n", getppid());
    } else {
        //父进程
        printf("老学员引进的新学员id: %d\n", pid);

    }
    
    //从fork调用完成之后，代码就分开了
    //fork 之后的代码是在父子进程中各自执行了一遍


    return 0;
}
