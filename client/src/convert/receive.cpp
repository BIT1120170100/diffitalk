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
/**************************************************/
/*名称：向服务器/别的用户 接收消息
/*描述：实现服务器监听多个客户端，服务器向客户端发送通知
/*作成日期：2019-09-02 
/*作者：王子嘉 
/***************************************************/ 
static void usage(const char* proc)
{
	printf("use help : %s [local_ip] [local_port]\n", proc);
}
int client_fds[MAX_CLIENT];  
void server_receive(mainint argc, const char * argv[])  
{
	if(argc != 3)
	{
		usage(argv[0]);
		return -1;
	}
	char input_msg[MAX_SIZE];  
    char recv_msg[MAX_SIZE];  
    //本地地址  
    struct sockaddr_in server_addr;  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_port = htons(atoi(argv[2]));  
    server_addr.sin_addr.s_addr = inet_addr(argv[1]); 
    bzero(&(server_addr.sin_zero), 8);  
    //创建socket  
    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);  
    if(server_sock_fd == -1)  
    {  
		perror("socket error");  
        return 1;  
    }  
    //绑定socket  
    int bind_result = bind(server_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));  
    if(bind_result == -1)  
    {  
        perror("bind error");  
        return 1;  
    }  
    //listen  
    if(listen(server_sock_fd, BACKLOG) == -1)  
    {  
        perror("listen error");  
        return 1;  
    }  
    //fd_set  
    fd_set server_fd_set;  
    int max_fd = -1;  
    struct timeval tv;  //超时时间设置  
    while(1)  
    {
		tv.tv_sec = 20;  
        tv.tv_usec = 0;  
        FD_ZERO(&server_fd_set);  
        FD_SET(STDIN_FILENO, &server_fd_set);  
        if(max_fd <STDIN_FILENO) 
        	max_fd = STDIN_FILENO;   
    	//服务器端socket  
        FD_SET(server_sock_fd, &server_fd_set);  
        if(max_fd < server_sock_fd)  
            max_fd = server_sock_fd;  
    	//客户端连接  
        for(int i =0; i < MAX_CLIENT; i++)  
            if(client_fds[i] != 0)  
            {  
                FD_SET(client_fds[i], &server_fd_set);  
                if(max_fd < client_fds[i])  
                    max_fd = client_fds[i];
            }  
        int ret = select(max_fd + 1, &server_fd_set, NULL, NULL, &tv);  
        if(ret <= 0)  
            continue;  
        else  
        {  
            //ret 为未状态发生变化的文件描述符的个数  
            if(FD_ISSET(STDIN_FILENO, &server_fd_set))  
            {  
                printf("发送消息：\n");  
                bzero(input_msg, MAX_SIZE);  
                fgets(input_msg, MAX_SIZE, stdin);  
                //输入".quit"则退出服务器  
                if(strcmp(input_msg, QUIT_CMD) == 0)  
                    exit(0); 
				char input_msg_new[MAX_SIZE];
				strcpy(input_msg_new,"服务器：");
				strcat(input_msg_new,input_msg);
				for(int i = 0; i < MAX_CLIENT; i++)
					if(client_fds[i] != 0)
						{
							printf("client_fds[%d]=%d\n", i, client_fds[i]);  
	                        send(client_fds[i], input_msg_new, MAX_SIZE, 0);  
	                    }  
	      	}  
	        if(FD_ISSET(server_sock_fd, &server_fd_set))  
	        {  
	            //有新的连接请求  
	            struct sockaddr_in client_address;  
	            socklen_t address_len;  
	            int client_sock_fd = accept(server_sock_fd, (struct sockaddr *)&client_address, &address_len);  
	            printf("新的连接建立client_sock_fd = %d\n", client_sock_fd);  
	            if(client_sock_fd > 0)  
	            {  
	                int index = -1;  
	                for(int i = 0; i < MAX_CLIENT; i++)  
	                    if(client_fds[i] == 0)  
	                    {  
	                        index = i;  
	                        client_fds[i] = client_sock_fd;  
	                        break;  
	                    }  
	                if(index >= 0)  
	                    printf("新客户端(%d)加入成功\n", index);  
						else  
	                {  
	                    bzero(input_msg, MAX_SIZE);  
	                    strcpy(input_msg, "服务器加入的客户端数达到最大值,无法加入!\n");  
	                    send(client_sock_fd, input_msg, MAX_SIZE, 0);  
	                    printf("客户端连接数达到最大值，新客户端加入失败 %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));  
	                }  
	            }  
	        }  
	        for(int i =0; i < MAX_CLIENT; i++)  
	            if(client_fds[i] !=0)  
	            {  
	                if(FD_ISSET(client_fds[i], &server_fd_set))  
	                {  
	                    //处理某个客户端过来的消息  
	                    bzero(recv_msg, MAX_SIZE);  
	                    long byte_num = recv(client_fds[i], recv_msg, MAX_SIZE, 0);  
	                    if (byte_num > 0)  
	                    {   
	                        recv_msg[byte_num > MAX_SIZE? MAX_SIZE:byte_num] = '\0'; 
						    char dest[10] = {""};
						    char new_recv_msg[MAX_SIZE];
						    strncpy(dest, recv_msg, 4);
						    if(strcmp(dest, "send") == 0)
						    { 
							    int now=recv_msg[4]-48;
							    strncpy(new_recv_msg, recv_msg+6, MAX_SIZE);
				                        	    printf("客户端(%d)向客户端(%d)发送私聊消息:%s\n", i,now,new_recv_msg); 
				
							    char message_pri[MAX_SIZE];
							    message_pri[0]='(';
							    message_pri[1]=i+48;
							    message_pri[2]=')';
							    message_pri[3]='\0';
							    char new_message[MAX_SIZE];
							    strcpy(new_message,"客户端");
							    strcat(new_message, message_pri);
							    strcat(new_message, "给你私发一条消息：");	
							    int status=0;	
							    strcat(new_message,new_recv_msg); 
							    for(int j = 0; j < MAX_CLIENT; j++) 
					                        if(client_fds[j] != 0&&j==now)
								{
							            send(client_fds[j], new_message, MAX_SIZE, 0);
								    status++;
								}
							    if(status==0)
								    send(client_fds[i], "你私聊的对象不存在\n", MAX_SIZE, 0);
						    }
else if(strcmp(dest, "show") == 0)
						    {
						    	int all=0; 
    							for(int i = 0; i < MAX_CLIENT; i++)
									if(client_fds[i] != 0)
										all++;
								printf("客户端(%d)查看当前在线人数\n",i);
								char new_message[MAX_SIZE];
								strcpy(new_message,"当前在线的客户端数量为");
								char number_all[10];
								number_all[0]=48+all;
								number_all[1]='\0';
								strcat(new_message, number_all);
								strcat(new_message, "个，分别是：客户端(");
	    							for(int j = 0; j < MAX_CLIENT; j++)
										if(client_fds[j] != 0)
											{												
												number_all[0]=48+j;
												strcat(new_message, number_all);
												strcat(new_message, ",");
											    } 
								
								strcat(new_message, ")\n");
	    							for(int k = 0; k < MAX_CLIENT; k++)
										if(client_fds[k] != 0&&k==i)
												send(client_fds[k], new_message, MAX_SIZE, 0);  
    						}
else{
		                    	printf("客户端(%d)的群聊消息:%s\n", i, recv_msg); 
							    char x=48+i;
							    char message[MAX_SIZE];
							    message[0]='(';
							    message[1]=x;
							    message[2]=')';
							    message[3]=':';
							    message[4]='\0';
							    char new_message[MAX_SIZE];
							    strcpy(new_message,"客户端");
							    strcat(new_message, message);		
							    strcat(new_message,recv_msg); 
					                    for(int j = 0; j < MAX_CLIENT; j++) 
					                        if(client_fds[j] != 0&&j!=i)  
							            send(client_fds[j], new_message, MAX_SIZE, 0);
						    }
						}
else if(byte_num < 0)  
		                    printf("从客户端(%d)接受消息出错.\n", i);  
else  
		                {  
		                    FD_CLR(client_fds[i], &server_fd_set);  
		                    client_fds[i] = 0;  
		                    printf("客户端(%d)退出了\n", i);  
		                }  
	            	}  
	       		}   
    	}  
    }  
}
