#include<stdio.h>  
#include<stdlib.h>  
#include<netinet/in.h>  
#include<sys/socket.h>  
#include<arpa/inet.h>  
#include<string.h>  
#include<unistd.h> 
#include <sys/types.h> 
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#define MAX_SIZE 1024  
/**************************************************/
/*名称：client_send.c
/*描述：实现基于客户端向服务端发送信息，客户端群发消息，以及客户端之间私聊的功能
/*作成日期：2019-09-02
/*作者：王子嘉
/***************************************************/
/*需要手动配置ip与端口*/
static void usage(const char* proc)
{
	printf("%s [ip] [port]\n", proc);
}
/*发送信息主函数，直接输入信息可以群发消息，send+客户端号可以私发信息*/
void client_send(int argc, const char * argv[])  
{  
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}
    struct sockaddr_in server_addr;  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_port = htons(atoi(argv[2]));  
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);  
    bzero(&(server_addr.sin_zero), 8);  
  
    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);  
    if(server_sock_fd == -1)  
    {  
    	perror("socket error");  
    	return 1;  
    }  
    char recv_msg[MAX_SIZE];  
    char input_msg[MAX_SIZE];  
/*建立与指定socket的连接 
  int connect(SOCKET s, const struct sockaddr * name, int namelen);*/
    if(connect(server_sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == 0)  
    {  
		fd_set client_fd_set;  
		struct timeval tv;  
		while(1)  
		{  
			tv.tv_sec = 20;  
			tv.tv_usec = 0;  
/*当一个套接字或一组套接字有信号，select函数来实现多路复用输入/输出	*/
			FD_ZERO(&client_fd_set);  
			FD_SET(STDIN_FILENO, &client_fd_set);  
			FD_SET(server_sock_fd, &client_fd_set);  
			select(server_sock_fd + 1, &client_fd_set, NULL, NULL, &tv);  
			if(FD_ISSET(STDIN_FILENO, &client_fd_set))  
			{  
			    bzero(input_msg, MAX_SIZE);  
			    fgets(input_msg, MAX_SIZE, stdin);  
			    if(send(server_sock_fd, input_msg, MAX_SIZE, 0) == -1)  
				perror("发送消息出错!\n"); 
			}  
			if(FD_ISSET(server_sock_fd, &client_fd_set))  
			{  
			    bzero(recv_msg, MAX_SIZE);  
			    long byte_num = recv(server_sock_fd, recv_msg, MAX_SIZE, 0);  
			    if(byte_num > 0)  
			    {  
			    	if(byte_num > MAX_SIZE)  
					byte_num = MAX_SIZE;  
			    	recv_msg[byte_num] = '\0';  
			    	printf("%s\n", recv_msg);  
			    }  
			    else if(byte_num < 0)  
			    	printf("接受消息出错!\n");  
			    else  
			    {  
			    	printf("服务器端退出!\n");  
			    	exit(0);  
			    }  
			}  
        }  
    }    
}
