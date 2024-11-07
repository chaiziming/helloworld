#include <time.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    // 下面两个属性在创建队列时用不到
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    char *mq_name = "/p_c_mq";
    mqd_t mqdes = mq_open(mq_name, O_RDWR | O_CREAT, 0664, &attr);

    if (mqdes == (mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    char write_buf[100];
    struct timespec time_info;
    attr.mq_maxmsg = 10;
    while (1)
    {
        // 清空缓冲区
        memset(write_buf, 0, 100);
        ssize_t read_count = read(STDIN_FILENO, write_buf, 100);
        clock_gettime(0, &time_info);
        time_info.tv_sec += 5;

        if (read_count == -1)
        {
            perror("read");
            continue;
        }
        else if (read_count == 0)
        {
            // ctrl+d 关掉控制台的时候
            printf("退出\n");
            char eof = EOF;
            if (mq_timedsend(mqdes, &eof, 1, 0, &time_info) == -1)
            {
                perror("exit mq_timedsend");
            }
            break;
        }

        // 正常接受的可读信息
        if (mq_timedsend(mqdes, write_buf, strlen(write_buf), 0, &time_info) == -1)
        {
            perror("mq_timedsend");
        }
    }
    close(mqdes);

    return 0;
}
