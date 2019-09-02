#ifndef CLIENT_SEND_H
#define CLIENT_SEND_H
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
 void client_send(int argc, const char * argv[]);
#endif