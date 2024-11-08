#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_LEN 1024

char *buf;

// 1 读控制台信息写入缓存
// 2 将缓存信息读到控制台

// input
void *input_thread(void *argv)
{
    int i = 0;
    while (1)
    {
        char c = fgetc(stdin);
        if (c && c != '\n')
        {
            buf[i++] = c;
        }
        // buf 溢出
        if (i >= BUF_LEN)
        {
            i = 0;
        }
    }
}

void *output_thread(void *argv)
{
    int i = 0;
    while (1)
    {
        if (buf[i])
        {
            //读取一个字节写出到控制台
            fputc(buf[i], stdout);
            fputc('\n', stdout);
            buf[i++] = 0;
            if (i >= BUF_LEN)
            {
                i = 0;
            }
        } else {
            sleep(1);
        }
        
    }
}

int main(int argc, char const *argv[])
{
    buf = malloc(BUF_LEN);
    // 声明线程id
    pthread_t tid_input;
    pthread_t tid_output;

    pthread_create(&tid_input, NULL, input_thread, NULL);
    pthread_create(&tid_output, NULL, output_thread, NULL);

    //主线程等待读写线程结束
    pthread_join(tid_input, NULL);
    pthread_join(tid_output, NULL);

    free(buf);

    return 0;
}
