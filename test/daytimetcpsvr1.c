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
    int listenfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    char buff[255];
    time_t ticks;
    

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        err_sys("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
    {
        err_sys("bind error");
    }

    if(listen(listenfd, 10)<0)
    {
        err_sys("listen error");
    }

    while(1)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
        printf("connnection from %s, port %d\n",
                inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff))
                ,ntohs(cliaddr.sin_port));
        ticks = time(NULL);

        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        write(connfd, buff, strlen(buff));
        close(connfd);
    }

    return 0;
}
