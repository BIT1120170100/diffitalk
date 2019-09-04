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
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include "../util/util.h"
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
//MyUser currentUser;

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

int build_packet(Kind kind, void *arg1, void *arg2, void *arg3) //, void *arg3 = NULL
{
	cJSON *root = cJSON_CreateObject();
	printf("build_packet init==============\n");
	if (root == NULL)
	{
		printf("create json object failed\n");
		return 1;
	}
	printf("build_packet  switch==============\n");
	switch (kind)
	{
		// regist, login,  logout, chat, modify,  friend_add,chat_together

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
		cJSON_AddStringToObject(root, "type", "register-message");
		cJSON_AddStringToObject(root, "username", (char *)arg1);
		cJSON_AddStringToObject(root, "password", (char *)arg2);
		cJSON_AddStringToObject(root, "email", (char *)arg3);
		send_function(cJSON_Print(root));
		break;
	case chat:
		break;
	case modify:
		break;
	case chat_together:
		break;
	case friend_add:
		cJSON_AddStringToObject(root, "type", "add-friend-request");
		cJSON_AddStringToObject(root, "userid", currentUser.user_id);
		cJSON_AddStringToObject(root, "friendid", (char *)arg1);
		send_function(cJSON_Print(root));
		break;
	case list_update: //添加后更新好友列表
		cJSON_AddStringToObject(root, "type", "friend-list-request");
		cJSON_AddStringToObject(root, "username", currentUser.user_id);
		send_function(cJSON_Print(root));
		break;
	}
	return 1;
}
int parse_packet(Packet packet, Kind *kind, Data *data)
{
	*kind = packet.kind;
	*data = packet.data;
	return 0;
}
//登陆 的userid是id 注册的userid 是用户名
int loginAndRigistCheck(char *userid, char *password, Kind kind, char *c_ipAddr, char *email)
{
	int port = MYPORT;
	int MAXLINE = 4096;
	char buf[MAXLINE];
	Data data;

	//设置一个管理员权限
	if (!strcmp(userid, "diffitalk"))
	{
		return 1;
	}

	printf("c_ip: %s\n", c_ipAddr);
	client_socket = init_client(MYPORT, c_ipAddr);

	//连接成功后获取用户当前的ip

	printf("kkk:%d\n", client_socket);
	if (client_socket < 0)
	{
		printf("create socket error\n");
		exit(0);
	}
	switch (kind)
	{
	case login:
		build_packet(kind, userid, password, NULL);
		break;
	case regist:
		build_packet(kind, userid, password, email);
		break;
	default:
		perror("kind is error in bulid paclet！");
	}

	while (1)
	{
		char recvbuf[BUFFER_SIZE];
		memset(recvbuf, 0, sizeof(BUFFER_SIZE));
		long len;
		len = recv(client_socket, recvbuf, sizeof(recvbuf), 0);
		cJSON *root = cJSON_Parse(recvbuf);
		char *type = cJSON_GetObjectItem(root, "type")->valuestring;
		printf("%s", type);
		memset(recvbuf, 0, sizeof(recvbuf));
		if (strcmp(type, "login-receipt") == 0)
		{
			//received the login receipt from server
			int status = cJSON_GetObjectItem(root, "status")->valueint;
			if (status) //登陆成功 返回1
			{
				//返回用户信息 加载回去
				strcpy(currentUser.user_id, userid);
				strcpy(currentUser.user_password, password);
				//加载好友界面   需要发送好友信息

				// strcpy()
				return 1;
			}
			else
			{
				showDialog("密码输入错误或当前用户名不存在！");
				return 0;
			}
		}
		else if (strcmp(type, "register-receipt") == 0)
		{
			//received the login receipt from server
			int status = cJSON_GetObjectItem(root, "status")->valueint;
			char *user_id = cJSON_GetObjectItem(root, "userid")->valuestring;
			if (status)
			{
				showDialog(user_id);
				strcpy(currentUser.user_id, user_id);
				strcpy(currentUser.user_password, password);
				strcpy(currentUser.user_name, userid);
				//加载好友界面   需要发送好友信息

				return 1;
			}
			else
			{
				showDialog("注册失败！");
				return 0;
			}
			break;
		}
	}
	printf("????");
	return 1;
}

// 查找好友
//输入id 返回是否添加成功  可能已经是好友，可能不能是好友，也可能不存在这个用户
int addFriend(char *userid, char *c_ipAddr)
{
	int port = MYPORT;
	int MAXLINE = 4096;
	char buf[MAXLINE];
	Data data;

	// printf("c_ip: %s\n", c_ipAddr);
	// client_socket = init_client(MYPORT, c_ipAddr);

	printf("kkk:%d\n", client_socket);
	if (client_socket < 0)
	{
		printf("create socket error\n");
		exit(0);
	}

	build_packet(friend_add, userid, NULL, NULL);

	while (1)
	{
		char recvbuf[BUFFER_SIZE];
		memset(recvbuf, 0, sizeof(BUFFER_SIZE));
		long len;
		len = recv(client_socket, recvbuf, sizeof(recvbuf), 0);
		cJSON *root = cJSON_Parse(recvbuf);
		char *type = cJSON_GetObjectItem(root, "type")->valuestring;
		printf("%s", type);
		memset(recvbuf, 0, sizeof(recvbuf));
		//received the   receipt from server
		int status = cJSON_GetObjectItem(root, "status")->valueint;
		if (status == 1) // 成功 返回1
		{
			//返回用户信息 加载回去
			//strcpy(currentUser.user_id, userid);
			//strcpy(currentUser.user_password, password);
			// strcpy()
			//添加成功 在界面加载
			printf("success!");
			return 1;
		}
		else if (!status)
		{
			showDialog("已经是好友了");
			return 0;
		}
		else
		{
			showDialog("没有此用户");
			return 0;
		}
	}
	return 1;
}

//更新好友列表
//
int listUpdate(char *userid, char *c_ipAddr)
{
	int port = MYPORT;
	int MAXLINE = 4096;
	char buf[MAXLINE];
	Data data;

	// printf("c_ip: %s\n", c_ipAddr);
	// client_socket = init_client(MYPORT, c_ipAddr);

	printf("kkk:%d\n", client_socket);
	if (client_socket < 0)
	{
		printf("create socket error\n");
		exit(0);
	}

	build_packet(list_update, userid, NULL, NULL);

	while (1)
	{
		char recvbuf[BUFFER_SIZE];
		memset(recvbuf, 0, sizeof(BUFFER_SIZE));
		long len;
		len = recv(client_socket, recvbuf, sizeof(recvbuf), 0);
		cJSON *root = cJSON_Parse(recvbuf);
		char *type = cJSON_GetObjectItem(root, "type")->valuestring;
		printf("%s", type);
		memset(recvbuf, 0, sizeof(recvbuf));
		//received the   receipt from server
		int status = cJSON_GetObjectItem(root, "status")->valueint;
		if (status) // 成功 返回1
		{
			//返回用户信息 加载回去
			//strcpy(currentUser.user_id, userid);
			//strcpy(currentUser.user_password, password);
			// strcpy()
			//添加成功 在界面加载
			printf("success!");
			return 1;
		}
		else
		{
			showDialog("当前用户名不存在！");
			return 0;
		}
	}
	return 1;
}
