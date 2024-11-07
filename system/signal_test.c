#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("收到%d信号\n", signum);
    exit(signum);
}

int main(int argc, char const *argv[])
{


    while (1)
    {
        if (signal(SIGINT, sigint_handler) == SIG_ERR)
        {
            perror("signal");
            return 1;
        }
        
        printf("在吗？\n");
        sleep(1);
    }
    
    return 0;
}
