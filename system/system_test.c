#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    //使用标准库创建子进程
    int sysR = system("ping -c 100 www.baidu.com");
    if (sysR != 0)
    {
        perror("system");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
