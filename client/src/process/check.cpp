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
		if (strlen((char *)arg2) > 1024)
		{
			printf("发送内容太长，请重新发送\n");
			break;
		}
		//发送类型 发送对象 发送内容 发送时间
		cJSON_AddStringToObject(root, "type", "message/text");
		cJSON_AddStringToObject(root, "sendto", (char *)arg1);
		cJSON_AddStringToObject(root, "sendfrom", currentUser.user_id);
		cJSON_AddStringToObject(root, "sendtime", get_formatted_time());
		cJSON_AddStringToObject(root, "content", (char *)arg2);
		send_function(cJSON_Print(root));
		//save the chat record while sending message
		//save_chatrecord_single(cJSON_Print(root));
		break;
	case modify:
		break;
	case chat_together:
		if (strlen((char *)arg2) > 1024)
		{
			printf("发送内容太长，请重新发送\n");
			break;
		}
		//发送类型 发送对象 发送人 发送时间 发送内容  发送的群组
		cJSON_AddStringToObject(root, "type", "message/text/group");
		cJSON_AddNumberToObject(root, "sendto", *(int *)arg1);
		cJSON_AddStringToObject(root, "sendfrom", currentUser.user_id);
		cJSON_AddStringToObject(root, "sendtime", get_formatted_time());
		cJSON_AddStringToObject(root, "content", (char *)arg2);
		//UNDO
		cJSON_AddStringToObject(root, "msgID", "segmentfault");
		send_function(cJSON_Print(root));
		break;
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
			printf("the status is : %d\n",status);
			if (status) //登陆成功 返回1
			{
				//返回用户信息 加载回去
				strcpy(currentUser.user_id, userid);
				strcpy(currentUser.user_password, password);
				//加载好友界面   需要发送好友信息
				listUpdate(currentUser.user_id);
				// strcpy()
				return 1;
			}
			else
			{
				//showDialog("密码输入错误或当前用户名不存在！");
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
int listUpdate(char *userid)
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

	//接受好友列表更新
	while (1)
	{
		char recvbuf[BUFFER_SIZE];
		memset(recvbuf, 0, sizeof(BUFFER_SIZE));
		long len;
		len = recv(client_socket, recvbuf, sizeof(recvbuf), 0);
		cJSON *root = cJSON_Parse(recvbuf);
		char *type = cJSON_GetObjectItem(root, "type")->valuestring;

		// //friend list
		//返回好友人数到
		int size = cJSON_GetObjectItem(root, "size")->valueint;
		cJSON *list = cJSON_GetObjectItem(root, "list");
		int i;
		printf("friend list of user %s:\n", currentUser.user_id);
		for (i = 0; i < size; i++)
		{
			cJSON *item = cJSON_GetArrayItem(list, i);
			char *username = cJSON_GetObjectItem(item, "username")->valuestring;
			int status = cJSON_GetObjectItem(item, "status")->valueint;
			printf("%s [%s]\n", username, (status ? "online" : "offline"));
			strcpy(friends[i].user_id, username); //UNDO
			friends[i].user_online = status;
		}
		printf("friend list size = %d\n", size);
		gdk_threads_enter();
		// update_friendlist(UPDATE_FRIENDLIST);
		gdk_threads_leave();

		printf("%s:", type);
		memset(recvbuf, 0, sizeof(recvbuf));
		//received the   receipt from server
		int status = cJSON_GetObjectItem(root, "status")->valueint;
		if (status) // 成功 返回1
		{
			//添加成功 在界面加载
			printf("success!");
			return 1;
		}
		else
		{
			// showDialog("当前用户名不存在！");
			return 0;
		}
	}
	return 1;
}

int sendText(char *userid, char *recv_id) //char *c_ipAddr, char *email)
{

	// char *sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valuestring;
	// char *sendtime = cJSON_GetObjectItem(root, "sendtime")->valuestring;
	// char *content = cJSON_GetObjectItem(root, "content")->valuestring;
	/*
		printf("user %s sent a message to you at %s, \nmessage is %s\n",
			sendfrom, sendtime, content);*/
	//save chat record when receiving new message
	gdk_threads_enter();
//	save_chatrecord_single(message);
	gdk_threads_leave();
	//exec_cmd(13, "single", sendfrom);
}

int addGroup(char *groupid,char * str_ip)
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

	build_packet(friend_add, groupid, NULL, NULL);

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
