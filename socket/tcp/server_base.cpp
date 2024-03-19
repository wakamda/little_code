#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>//linux下特有的头文件，主要包含了read，write等函数
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MAXLINE 1024
#define PORT 6000

//server的动作：创建socket，绑定端口地址(先设置端口地址)，监听，开始接受accept，然后接收数据，关闭

//明确需求：回复一次后，直接退出（不会报错）
//回复一次后，继续等待回复,需要正确写while循环

int main()
{
    //buff
    char recvbuff[MAXLINE];
    char reply[MAXLINE] = "reply";
    int sock;
    int conn;

    //create
    if((sock=socket(AF_INET,SOCK_STREAM,0)) < 0){
        std::perror("Create socket failed!\n");
        return 1;
    }

    //bind
    struct sockaddr_in  sockAddr;
    memset(&sockAddr,0,sizeof(sockAddr));// 各位清零
    sockAddr.sin_family=AF_INET;
    sockAddr.sin_addr.s_addr=INADDR_ANY;
    sockAddr.sin_port=htons(PORT);
    if((bind(sock,(struct sockaddr*)&sockAddr,sizeof(sockAddr)) < 0)){
        std::perror("bind failed!\n");
        return 1;
    }

    //listen
    if((listen(sock,10)) < 0){
        std::perror("listen failed!\n");
        return 1;
    }

    printf("======listening......======\n");

    //accept
    conn=accept(sock,(struct sockaddr*)NULL,NULL);
    if(conn < 0)
    {
        std::perror("accept failed!\n");
        return 1;
    }
    printf("======accepted!!!!Ready to receive...======\n");
    char r[10];

#if 1
    while(1){
        //receive
        //使用的socket是连接socket
        int n=recv(conn,recvbuff,MAXLINE,0);
        if(n == 0){
            std::cout << "close" << std::endl;
            break;
        }
        else if(n > 0){
            recvbuff[n] = '\0';
            std::cout << "receive:" << recvbuff << std::endl;

            send(conn,reply,sizeof(reply),0);
        }else{
            if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN){
                
            }else if(errno == ECONNRESET){
                std::cout << "ECONNRESET" << std::endl;
                break;
            }else{
                perror("recv");
                break;
            }
        }
        //reply
            
            
    }
    
#endif

    close(conn);
    close(sock);
}