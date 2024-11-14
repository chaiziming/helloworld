#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void * task(void *arg) {
    printf("线程启动\n");
    sleep(1);
    printf("线程结束\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, task, NULL);

    //回收，detach 与 exit 不同的就是，detach的主线程不用等待子线程的完成
    pthread_detach(tid);

    //主线程比子线程慢
    printf("main thread continue\n");
    //因为主线程不等待子线程，如果主线程先结束的话，会杀掉子进程
    sleep(2);

    printf("main thread complated\n");
    
    return 0;
}
