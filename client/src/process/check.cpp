#include "../../include/check.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

#include <gtk/gtk.h>
#include <stdio.h>
#include <strings.h>
#include "../../include/data.h"
//#include"main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include "../util/util.h"
//#include "ui.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../json/cJSON.h"
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

int client_socket;

int send_function(char *message)
{
	char send_buffer[BUFFER_SIZE];
	memset(send_buffer, '\0', sizeof(send_buffer));
	strcpy(send_buffer, message);
	printf("sending message to server:\n%s\n", send_buffer);
	return send(client_socket, send_buffer, BUFFER_SIZE, 0);
}

int init_client(int port, char *addr)
{
	int cli_socket;
	int try_time;
	struct sockaddr_in server_addr;

	cli_socket = socket(AF_INET, SOCK_STREAM, 0); //创建客户端套接字
	if (cli_socket == -1)
	{
		return -1;
	}
	server_addr.sin_addr.s_addr = inet_addr(addr);
	server_addr.sin_port = htons(port);
	server_addr.sin_family = AF_INET;

	try_time = 0; //如果不成功每隔一秒连接一次，最多10次
	while (try_time < 10 && connect(cli_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		sleep(1);
		try_time++;
	}
	if (try_time >= 10)
		return -1;
	else
		return cli_socket;
}

int build_packet(Kind kind, void *arg1, void *arg2)
{
	cJSON *root = cJSON_CreateObject();
	printf("build_packet init==============\n");
	if (root == NULL)
	{
		printf("create json object failed\n");
		return 1;
	}
	switch (kind)
	{
		// regist, login,  logout, chat, modify,  friend_add,chat_together
		printf("build_packet  switch==============\n");
	 
	case login:
		cJSON_AddStringToObject(root, "type", "login-message");
		cJSON_AddStringToObject(root, "userid", (char *)arg1);
		cJSON_AddStringToObject(root, "password", (char *)arg2);
		send_function(cJSON_Print(root));
		break;
	case logout:
		cJSON_AddStringToObject(root, "type", "logout-message");
	//	cJSON_AddStringToObject(root, "username", current_username); //当前的名字
		send_function(cJSON_Print(root));
	//	logout_action();
		break;
	case regist:
		break;
	case chat:
		break;
	case modify:
		break;
	case chat_together:
		break;
	case friend_add:
		cJSON_AddStringToObject(root, "type", "add-to-contact-request");
//		cJSON_AddStringToObject(root, "username", current_username);
		cJSON_AddStringToObject(root, "contact", (char *)arg1);
		send_function(cJSON_Print(root));
	}
	return 1;
}
int parse_packet(Packet packet, Kind *kind, Data *data)
{
	*kind = packet.kind;
	*data = packet.data;
	return 0;
}
int loginAndRigistCheck(char *userid, char *password, Kind kind, char *c_ipAddr)
{
	int port = MYPORT;
	int MAXLINE = 4096;
	char buf[MAXLINE];
	Data data;

	printf("c_ip: %s\n", c_ipAddr);
//	client_socket = init_client(MYPORT, c_ipAddr);

//	printf("kkk:%d\n", client_socket);
//	if (client_socket < 0)
	{
 		printf("create socket error\n");
		exit(0);
	}

	build_packet(kind, userid, password);
	while (1)
	{
		char recvbuf[BUFFER_SIZE];
		long len;
		len = recv(client_socket, recvbuf, sizeof(recvbuf), 0);
		printf("%s", recvbuf);
		cJSON *root = cJSON_Parse(recvbuf);
		char *type = cJSON_GetObjectItem(root, "type")->valuestring;
		memset(recvbuf, 0, sizeof(recvbuf));
		if (strcmp(type, "login-receipt") == 0)
		{
			//received the login receipt from server
			int status = cJSON_GetObjectItem(root, "status")->valueint;
			printf("%d\n", status);
			break;
		}
		else
			printf("????");
	}
	return 1;
}
