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
        char c = fgetc();
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
            fputc(buf[i], stdout);
            fputc('\n', stdout);
            buf[i++];
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

    return 0;
}
