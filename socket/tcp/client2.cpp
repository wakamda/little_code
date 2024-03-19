#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>//linux下特有的头文件，主要包含了read，write等函数
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096

int main(int argc , char ** argv)
{
    
    int sock;
    int conn;
    

    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        printf("Create client_Socket Failed!\n");
        exit(1);
    }

        
    struct sockaddr_in serverAddr;
    bzero(&serverAddr,sizeof(serverAddr));//各位清零
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=inet_addr(argv[1]);  //服务器ip，inet_addr用于IPv4的IP转换（十进制转换为二进制）
    serverAddr.sin_port=htons(atoi(argv[2]));

    conn=connect(sock,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if(conn<0)
    {
        perror("connect");
        exit(1);
    }


    char sendbuf[20]="hello";
    char recvline[2048];
    
    char recvbuf[100];//如果接收缓存太小，会导致通信失败

    write(sock , sendbuf , strlen(sendbuf));
    printf("send msg:%s\n",&sendbuf);

    int r= recv(sock,recvline,sizeof(recvline),0);
    if(r < 0){
        perror("recv");
        exit(1);
    }
    printf("recv msg:%s\n",&recvline);


    close(sock); 

    return 0;

}