#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define handle_error(cmd, result) \
    if (result < 0)               \
    {                             \
        perror(cmd);              \
        return -1;                \
    }

void *read_from_client(void * arg){
    //用recv接受并打印
    int client_fd = *(int *)arg;
    char *read_buf = NULL;
    read_buf = malloc(sizeof(char) * 1024);
    ssize_t count = 0;

    if (!read_buf)
    {
        perror("malloc read_buf");
        return NULL;
    }
    //接收数据, 只要能接收数据就一直挂起
    while(count = recv(client_fd, read_buf, 1024, 0))
    {
        if (count < 0)
        {
            perror("recv");
        }
        
        fputs(read_buf, stdout);
    }

    printf("与客户端的连接关闭\n");
    free(read_buf);
    return NULL;
}

void *write_to_client(void * arg){
    //写出去
    int client_fd = *(int *)arg;
    char *write_buf = NULL;
    write_buf = malloc(sizeof(char) * 1024);
    ssize_t count = 0;

    if (!write_buf)
    {
        perror("malloc write_buf");
        return NULL;
    }

    while(fgets(write_buf, 1024, stdin) != NULL)
    {
        //发送出去
        count = send(client_fd, write_buf, 1024, 0);
        if (count < 0)
        {
            perror("send");
        }
    }
    printf("关闭连接\n");
    //可以具体关闭某一端
    shutdown(client_fd, SHUT_WR);
    free(write_buf);
    return NULL;
}

int main(int argc, char const *argv[])
{
    int sockfd, clientfd, tmp_result;
    struct sockaddr_in server_addr, client_addr;
    pthread_t pid_read, pid_write;
    // 清空
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // 填写服务端地址
    server_addr.sin_family = AF_INET;
    // 填写ip地址, 因为是本机就填 0.0.0.0 表示不填
    //  inet_pton(AF_INET, "0.0.0.0", server_addr.sin_addr.s_addr);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(6666);
    //网络编程流程
    // 创建socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);
    // 绑定地址
    tmp_result = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    handle_error("bind", tmp_result);
    // 进行监听
    tmp_result = listen(sockfd, 128);
    handle_error("listen", tmp_result);
    // 接收客户端的连接
    socklen_t client_len = sizeof(client_addr);
    // 这才是和客户端收发消息的描述符，没有则挂起等待
    clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    handle_error("accept", clientfd);

    printf(
        "与客户端%s %d建立连接 文件表述符 %d\n",
        inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port),
        clientfd
    );

    //创建线程来收消息
    pthread_create(&pid_read, NULL, read_from_client, (void *)&clientfd);
    //创建线程来发消息
    pthread_create(&pid_write, NULL, write_to_client, (void *)&clientfd);
    //阻塞主线程
    pthread_join(pid_read, NULL);
    pthread_join(pid_write, NULL);
    //释放资源
    printf("释放资源\n");
    close(clientfd);
    close(sockfd);

    return 0;
}
