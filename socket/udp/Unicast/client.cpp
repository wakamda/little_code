#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
 
int main()
{

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1)
    {
        perror("socket");
        exit(0);
    }

    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr("10.43.54.4");
    cliaddr.sin_port = htons(5150); 

     while(1)
    {
        // 发送数据:0x0002
        unsigned char a[14] ={0x02,0xFD,0x00,0x02,0x00,0x00,0x00,0x06,0x01,0x02,0x03,0x04,0x05,0x06};
        unsigned char c[10] = {0xaa,0x55,0x03,0x00,0x00,0x00,0x14,0x59,0xa5,0x5a};

        // 发送数据:0x0003
        unsigned char b[25] ={0x02,0xFD,0x00,0x03,0x00,0x00,0x00,0x11,0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11};

        sendto(fd, c, sizeof(c), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
        
        printf("send:");
        for(int i = 0;i < sizeof(c); i++){
            printf("%x",c[i]);
        }
        printf("\n");
        
        sleep(3);

       
        // 接收数据
        char buf[128];
        recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("server say: %s\n", buf);
 
    close(fd);

    }
 
    close(fd);
 
    return 0;
}