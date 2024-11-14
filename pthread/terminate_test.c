#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

//定义结构体，接受线程结果
typedef struct Result {
    char *p;
    int len;
} Result;

// 如果一个进程的多个线程使用到标准输出，会造成冲突，导致只有一个线程使用到标准输出

void * red_thread(void * arg) {
    Result *result  = malloc(sizeof(Result));
    char code = *((char *)arg);
    char *ans = malloc(101);
    while (1)
    {
        fgets(ans, 100, stdin);
        if (ans[0] == code)
        {
            // 接到了回复的消息
            free(ans);
            printf("红玫瑰离开了\n");
            char *redans = strdup("红玫瑰去了纽约\n");
            result->p = redans;
            result->len = strlen(redans);
            //故事结束
            pthread_exit((void *)result);
        } else {
            printf("红玫瑰还在等你\n");
        }
        
    }
    
}

void * white_thread(void * arg) {
    Result *result  = malloc(sizeof(Result));
    char code = *((char *)arg);
    char *ans = malloc(101);
    while (1)
    {
        fgets(ans, 100, stdin);
        if (ans[0] == code)
        {
            // 接到了回复的消息
            free(ans);
            printf("白玫瑰离开了\n");
            char *redans = strdup("白玫瑰去了巴黎\n");
            result->p = redans;
            result->len = strlen(redans);
            //故事结束
            pthread_exit((void *)result);
        } else {
            printf("白玫瑰还在等你\n");
        }
        
    }
}

int main(int argc, char const *argv[])
{
    // 红码 白码
    char red_code = 'r';
    char white_code = 'w';
    pthread_t pid_red;
    pthread_t pid_white;
    Result *red_result = NULL;
    Result *white_result = NULL;

    pthread_create(&pid_red, NULL, red_thread, &red_code);
    pthread_create(&pid_white, NULL, white_thread, &white_code);
    
    pthread_join(pid_red, (void **)&red_result);
    printf("红玫瑰的结局%d是:%s\n", red_result->len, red_result->p);
    free(red_result->p);
    free(red_result);

    pthread_join(pid_white, (void **)&white_result);
    printf("白玫瑰的结局%d是:%s\n", white_result->len, white_result->p);
    free(white_result->p);
    free(white_result);

    return 0;
}
