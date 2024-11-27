#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define handle_error(cmd, result) \
    if (result < 0)               \
    {                             \
        perror(cmd);              \
        return -1;                \
    }

int main(int argc, char const *argv[])
{
    //设计EOF作为关闭的信号
    int sockfd, tmp_result;
    char *buf = malloc(sizeof(char) * 1024);
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
    // UDP网络编程流程
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    handle_error("socket", sockfd);
    //绑定
    socklen_t server_len = sizeof(server_addr);
    socklen_t client_len = sizeof(client_addr);
    tmp_result = bind(sockfd, (struct sockaddr *)&server_addr, server_len);
    handle_error("bind", tmp_result);
    //收发数据
    do
    {
        memset(buf, 0, 1024);
        //接收数据到buf里
        tmp_result = recvfrom(sockfd, buf, 1024, 0, (struct sockaddr *)&client_addr, &client_len);
        handle_error("recvfrom", tmp_result);

        if (strncmp(buf, "EOF", 3) != 0)
        {
            printf("接收到客户端%s %d信息：%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);
            strcpy(buf, "OK\n");
        } else {
            printf("收到结束信息，准备关闭\n");
        }
        //回复
        tmp_result = sendto(sockfd, buf, 4, 0, (struct sockaddr *)&client_addr, client_len);
        handle_error("sendto", tmp_result);

    } while (strncmp(buf, "EOF", 3) != 0);
    
    free(buf);

    return 0;
}
