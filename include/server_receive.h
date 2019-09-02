#ifndef SERVER_RECEIVE_H
#define SERVER_RECEIVE_H
#include<stdio.h>  
#include<stdlib.h>  
#include<netinet/in.h>  
#include <sys/types.h> 
#include<sys/socket.h>  
#include<arpa/inet.h>  
#include<string.h>  
#include<unistd.h>  
#define BACKLOG 5     
#define MAX_CLIENT 10   //应用层同时可以处理的最大客户端数
#define MAX_SIZE 1024  
#define QUIT_CMD ".quit" 
void server_receive(mainint argc, const char * argv[])  ;
#endif