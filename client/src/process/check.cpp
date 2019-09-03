#include"../../include/check.h" 
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> 
//#include"main.h"
/**************************************************/
/*名称： 检查部分
/*描述： 
/*作成日期： 
/*参数：
        参数1： 
        参数2： 
/*返回值： 
/*作者： 
/***************************************************/

extern char* str_ip;
int client_socket;

int init_client(int port,char *addr)
{
	int cli_socket;
	int try_time;
	struct sockaddr_in server_addr;
	
	cli_socket=socket(AF_INET,SOCK_STREAM,0);	//创建客户端套接字
	if(cli_socket==-1)return -1;

	server_addr.sin_addr.s_addr=inet_addr(addr);
	server_addr.sin_port=htons(port);
	server_addr.sin_family=AF_INET;

	try_time=0;			//如果不成功每隔一秒连接一次，最多10次
	while(try_time<10 && connect(cli_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
    {
		sleep(1);
        try_time++;
    }
	if(try_time >= 10)return -1;
	else return cli_socket;
}

int build_packet(Packet *packet,Kind kind,...){
	va_list ap;
	packet->kind=kind;
	va_start(ap,kind);
	switch(kind){
		case regist:
		case modify:
		case logout: 
                //UNDO
		case login:packet->data=(Data) va_arg(ap,User);break;
		case chat:packet->data=(Data) va_arg(ap,Message);break;
		//case login:packet->data=(Data)va_arg(ap,User);break;
		//case chat:packet->data=(Data)va_arg(ap,Message);break;
		//case friend:packet->data=(Data)va_arg(ap,Message);break;
		default:return -1;
	}
	va_end(ap);
	return 0;
}

int parse_packet(Packet packet,Kind *kind,Data *data){
	*kind=packet.kind;
	*data=packet.data;
	return 0;
}

int loginAndRigistCheck(int userid,char *password,Kind kind, char  *c_ipAddr)
{
    int port =MYPORT;
    int MAXLINE = 4096;
    char buf[MAXLINE];
    Data data;
    Packet packet;
    client_socket=init_client(MYPORT,c_ipAddr);
    printf("kkk:%d\n",client_socket);
    if(client_socket < 0)
    {
        printf("create socket error\n");
        exit(0);
    }

    data.userinfo.user_id=userid;
    strcpy(data.userinfo.user_password,password);
    //printf("%s\n%s",data.userinfo.account,data.userinfo.password);
    
    build_packet(&packet,kind,data);
    write(client_socket, &packet, sizeof(Packet));
    read(client_socket, &packet, sizeof(Packet));
    parse_packet(packet,&kind,&data);
    //printf("kkkk:\n%s\n%s\n",data.userinfo.account,data.userinfo.password);
    if(kind==regist&&data.userinfo.user_id)  return 1;
    else if(kind==login&&data.userinfo.user_id) return 1;
    else return 0;
}
