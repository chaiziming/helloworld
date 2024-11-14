#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 20000

void * add_thread(void *arg) {
    
}

int main(int argc, char const *argv[])
{
    int num = 0;
    pthread_t pid[THREAD_COUNT];
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(pid + i, NULL, add_thread, &num);
        /* code */
    }
    
    return 0;
}
