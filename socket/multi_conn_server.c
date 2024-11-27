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

void *read_from_clinet_then_write(void *arg)
{
    int client_fd = *(int *)arg;
    char *read_buf = NULL;
    char *write_buf = NULL;
    ssize_t count = 0, send_count = 0;
    read_buf = malloc(sizeof(char) * 1024);
    write_buf = malloc(sizeof(char) * 1024);
    if (!read_buf)
    {
        close(client_fd);
        perror("read_buf");
        return NULL;
    }
    if (!write_buf)
    {
        close(client_fd);
        perror("write_buf");
        return NULL;
    }

    while (count = recv(client_fd, read_buf, 1024, 0))
    {
        if (count < 0)
        {
            perror("recv");
        }
        printf("从%d客户端收到数据%s\n", client_fd, read_buf);
        strcpy(write_buf, "收到\n");
        send_count = send(client_fd, write_buf, 1024, 0);
        if (send_count < 0)
        {
            perror("send");
        }
    }
    // shutdown(client_fd, SHUT_RD);
    close(client_fd);
    free(read_buf);
    free(write_buf);
}

int main(int argc, char const *argv[])
{
    int sockfd, tmp_result;
    struct sockaddr_in server_addr, client_addr;
    // 清空
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // 填写服务端地址
    server_addr.sin_family = AF_INET;
    // 填写ip地址, 因为是本机就填 0.0.0.0 表示不填
    //  inet_pton(AF_INET, "0.0.0.0", server_addr.sin_addr.s_addr);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(6666);
    // 网络编程流程
    //  创建socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    handle_error("socket", sockfd);
    // 绑定地址
    tmp_result = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    handle_error("bind", tmp_result);
    // 进行监听
    tmp_result = listen(sockfd, 128);
    handle_error("listen", tmp_result);
    // 接收多个客户端的连接
    socklen_t cliaddr_len = sizeof(client_addr);
    while (1)
    {
        pthread_t pid_read_write;
        int clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &cliaddr_len);
        handle_error("accept", clientfd);
        printf("与客户端%s %d 建立连接%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), clientfd);
        // 一个客户端使用一个线程交互
        if (pthread_create(&pid_read_write, NULL, read_from_clinet_then_write, (void *)&clientfd))
        {
            perror("pthread_create");
        }
        pthread_detach(pid_read_write);
    }

    printf("释放资源\n");
    close(sockfd);

    return 0;
}
