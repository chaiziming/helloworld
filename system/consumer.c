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

    char read_buf[100];
    struct timespec time_info;
    attr.mq_maxmsg = 10;
    while (1)
    {
        // 清空缓冲区
        memset(read_buf, 0, 100);
        clock_gettime(0, &time_info);
        time_info.tv_sec += 15;

        // 读取消息队列的一个数据
        if (mq_timedreceive(mqdes, read_buf, 100, NULL, &time_info) == -1)
        {
            perror("mq_timedreceive");
            continue;
        }
        // 判断是否是eof
        if (read_buf[0] == EOF)
        {
            printf("接受到生产者发送的EOF\n");
            break;
        }

        // 正常接受的可读信息
        printf("%s\n", read_buf);
    }

    close(mqdes);
    mq_unlink(mq_name);

    return 0;
}
