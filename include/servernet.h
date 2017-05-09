#ifndef SERVERNET_H
#define SERVERNET_H

extern unsigned char server_port[];
extern unsigned char client_name[];
extern unsigned char raspbe_name[];
extern unsigned char reply_yes[];
extern unsigned char reply_no[];

int servernet_init();
int get_client(int server_sockfd);
void servernet_send(unsigned char *data,int sockfd);
void servernet_close(int sockfd);
void out_addr(struct sockaddr_in *clientaddr);
int handshake(int sockfd);

#endif
