#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

void err_sys(const char* x) 
{ 
    perror(x); 
    exit(1); 
}

int main(int argc, char**argv)
{
    int sockfd ,n;
    char recvline[255];
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        printf("usage: a.out ip\n");
        return -1;
    }   

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        err_sys("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <=0 )
    {
        printf("inet_pton error\n");
        return -1;
    }

    if(connect(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        err_sys("connect error\n");
        return -1;
    }

    while((n = read(sockfd, recvline, 255))>0)
    {
        recvline[n] = 0;
        if(fputs(recvline, stdout) == EOF)
        {
            printf("fputs error\n");
            return -1;
        }
    }

    if(n<0)
    {
        printf("read error\n");
        return -1;
    }

    return 0;
}
