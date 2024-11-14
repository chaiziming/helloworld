#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void * task(void *arg) {
    printf("线程启动\n");
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    printf("working\n");
    int i = 0;
    while (1)
    {
        printf("%d\n", i++);
    }
    
    printf("线程结束\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, task, NULL);

    // 取消子线程
    if (pthread_cancel(tid) != 0) //这个cancel只是发出一个停止的命令
    {
        perror("pthread_cancel");
    }

    void * res;
    //挂起等待
    pthread_join(tid, &res);
    
    if (res == PTHREAD_CANCELED)
    {
        printf("线程被取消\n");
    } else {
        printf("线程没被取消 exit code %ld\n", (long)res);
    }
    

    
    return 0;
}