#include "includes.h"

int client_fd1;
int client_fd2;
int server_fd;


void sig_hander(int signo)
{
	if(signo == SIGINT)
	{
		printf("server close\n");
		close(server_fd);
		exit(1);
	}
}

void all_init()
{
    server_fd = servernet_init();
	if(signal(SIGINT,sig_hander) == SIG_ERR)
	{
		perror("signal sigint error");
		exit(1);
	}
}

int main()
{
    unsigned char buffer[4];
    all_init();
    client_fd1 = get_client(server_fd);
    client_fd2 = get_client(server_fd);
    if(handshake(client_fd1) == 1 && handshake(client_fd2) == 2)
        while(1)
        {
            read(client_fd1,buffer,sizeof(buffer));
//            if(buffer[3] != buffer[2] ^ buffer[1])
//              continue;
            printf("%x %x %x %x\n",buffer[0],buffer[1],buffer[2],buffer[3]);
            write(client_fd2,buffer,sizeof(buffer));
        }
    else if(handshake(client_fd1) == 2 && handshake(client_fd2) == 1)
        while(1)
        {
            read(client_fd2,buffer,sizeof(buffer));
//            if(buffer[3] != buffer[2] ^ buffer[1])
//                continue;
            printf("%x %x %x %x\n",buffer[0],buffer[1],buffer[2],buffer[3]);
            write(client_fd1,buffer,sizeof(buffer));
        }
    close(server_fd);
    return 0;
}
