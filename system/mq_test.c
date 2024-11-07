#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    // 下面两个属性在创建队列时用不到
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    char *mq_name = "/father_son_mq";
    mqd_t mqdes = mq_open(mq_name, O_RDWR | O_CREAT, 0664, &attr);

    if (mqdes == (mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // subprocess recive message
        char read_buf[100];
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            memset(read_buf, 0, 100);
            clock_gettime(CLOCK_REALTIME, &time_info);
            time_info.tv_sec += 15;
            if (mq_timedreceive(qdes, read_buf, 100, NULL, &time_info) == -1)
            {
                perror("mq_timedreceive");
            }
            printf("子进程接受到数据：%s\n", read_buf);
        }
        
    }
    else
    {
        // main process send message
        char send_buf[100];
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            memset(send_buf, 0, 100);
            sprintf(send_buf, "第%d发送消息\n", (int)i+1);
            //获取当前具体时间
            clock_gettime(CLOCK_REALTIME, &time_info);
            time_info.tv_sec += 5;
            if (mq_timedsend(mqdes, send_buf, strlen(send_buf), 0, &time_info) == -1)
            {
                perror("mq_timedsend");
            }
            printf("父进程发送一条消息休眠1s");
            sleep(1);
            
        }
    }

    // release mq
    close(mqdes);

    if (pid > 0)
    {
        mq_unlink(mq_name);
    }

    return 0;
}
