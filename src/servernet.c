#include "../include/includes.h"

unsigned char server_port[] = "6349";
unsigned char client_name[] = "client";
unsigned char raspbe_name[] = "raspbe";
unsigned char reply_yes[] = "yes";
unsigned char reply_no[] = "non";

int servernet_init()
{
    int sockfd;
    struct sockaddr_in serveraddr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0)
    {
        perror("creat server socket fail");
        exit(1);
    }
	memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family =  AF_INET;
    serveraddr.sin_port = htons(atoi(server_port));
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
    {
        perror("bind error");
        exit(1);
    }
    if(listen(sockfd,10) < 0)
    {
        perror("Listen error");
        exit(1);
    }
    return sockfd;
}



void out_addr(struct sockaddr_in *clientaddr)
{
    unsigned short port = ntohs(clientaddr->sin_port);
    char ip[16];
    memset(ip,0,sizeof(ip));
    inet_ntop(AF_INET,&clientaddr->sin_addr.s_addr,ip,sizeof(ip));
    printf("client:%s(%d) connected\n",ip,port);
}

int get_client(int server_sockfd)
{
    int sockfd;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    sockfd = accept(server_sockfd,(struct sockaddr *)&clientaddr,&clientaddr_len);
    if(sockfd < 0)
    {
        perror("accept error");
        return -1;
    }
    out_addr(&clientaddr);
    return sockfd;
}

void servernet_send(unsigned char *data,int sockfd)
{
    write(sockfd,data,(4 * sizeof(unsigned char)));
}

void servernet_close(int sockfd)
{
    close(sockfd);
}

int handshake(int sockfd)
{
    unsigned char buf[6];
    read(sockfd,buf,sizeof(buf));
    if(strcmp(buf,client_name) == 0)
    {
        write(sockfd,reply_yes,sizeof(reply_yes));
        return 1;
    }
    else if(strcmp(buf,raspbe_name) == 0)
    {
        write(sockfd,reply_yes,sizeof(reply_yes));
        return 2;
    }
    else
    {
        write(sockfd,reply_no,sizeof(reply_no));
        printf("Unknow drive has tryed to connecte!\n");
        return 0;
    }
}
