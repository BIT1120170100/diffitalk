#include "../../include/check.h"
#include "../../include/login.h"
#include "../../include/chatWindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

#include <gtk/gtk.h>
#include "../../include/data.h"
#include <stdio.h>
#include <unistd.h>
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
char buffer[BUFFER_SIZE], send_buffer[BUFFER_SIZE];

//创建自动更新线程
void auto_update_thread()
{
	while (1)
	{
		sleep(15);
		build_packet(list_update,NULL,NULL,NULL); 
		sleep(5);
		build_packet(group_update,NULL,NULL,NULL);
		
		sleep(10);

		// printf("group : %d\n friend :%d\n", group_list_size, friend_list_size);
	}
}

//MyUser currentUser;
//监听 接受线程
//在主函数创建
void recv_thread()
{
	int numbytes;
	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		numbytes = recv(client_socket, buffer, BUFFER_SIZE, 0);

		if (numbytes == 0)
		{
			printf("server offline.\n");
			exit(1);
		}
		if (numbytes == -1)
		{
			perror("error receiving message\n");
			exit(1);
		}
		printf("recv judge over, client_socket = %d\n", client_socket);
		//buffer[numbytes] = '\0';
		printf("received message from server: \"%s\"\n", buffer);
		printf("before handle message, client_socket = %d\n", client_socket);
		//gdk_threads_enter();
		handle_message(buffer);
		//gdk_threads_leave();
	}
}

//处理信息
void handle_message(char *message)
{
	//gdk_threads_enter();
	printf("handle message start, client_socket = %d\n", client_socket);
	cJSON *root = cJSON_Parse(message);
	if (root == NULL)
	{
		printf("json parse error, message is \"%s\"\n", message);
		return;
	}
	char *type = cJSON_GetObjectItem(root, "type")->valuestring;

	printf("handle_message: %s\n", type);

	if (strcmp(type, "register-receipt") == 0)
	{
		int status = cJSON_GetObjectItem(root, "status")->valueint;
		char *userid = cJSON_GetObjectItem(root, "userid")->valuestring;
		char *password = cJSON_GetObjectItem(root, "password")->valuestring;
		char *username = cJSON_GetObjectItem(root, "username")->valuestring; 
		gdk_threads_enter();
		if (status == 1)
		{
			char str[100] = "登陆成功 用户的ID是: \n";
			strcat(str, userid);
			showDialog(str);
			printf("registered new user  successfully\n");
			strcpy(currentUser.user_password, password);
			strcpy(currentUser.user_id, userid);
			strcpy(currentUser.user_name, username);
			doLogin();
			//action undo
		}
		else
		{
			printf("register new user %s fail\n", username);
			// showDialog("注册失败");
		}
		gdk_threads_leave();
	}
	else if (strcmp(type, "login-receipt") == 0)
	{
		//received the login receipt from server
		int status = cJSON_GetObjectItem(root, "status")->valueint;
		printf("%d\n", status);
		if (status == 1)
		{
			char *userid = cJSON_GetObjectItem(root, "userid")->valuestring;
			char *username = cJSON_GetObjectItem(root, "username")->valuestring;
			strcpy(currentUser.user_id, userid);
			strcpy(currentUser.user_name, username);
			//strcpy(currentUser.user_id,userid);
			// printf("now is : %s\n",currentUser.user_id);
			//login_action(username);
			gdk_threads_enter();
			doLogin();
			//undo 改变在线状态
			//change_my_portrait(userimage);
			gdk_threads_leave();
		}
		else
		{
			sleep(3);
			gdk_threads_enter();
			showDialog("登陆失败!\n");
			gdk_threads_leave();
			printf("登陆失败!\n");
			exit(1);
		}
	}
	else if (strcmp(type, "message/text") == 0)
	{
		char *sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valuestring; 
		char *content = cJSON_GetObjectItem(root, "content")->valuestring; 
		printf("user %s sent a message to you  , message is %s\n",
			sendfrom,  content);
		sendToText(content);
		printf("userrrr");
		//save chat record when receiving new message
		gdk_threads_enter();
		// save_chatrecord_single(message);
		gdk_threads_leave();
		//exec_cmd(13, "single", sendfrom);
	}
	else if (strcmp(type, "message/text/group") == 0)
	{
		// printf("[%d]\n", root == NULL);
		// int sendto = cJSON_GetObjectItem(root, "sendto")->valueint;
		// printf("%d\n", sendto);
		// char *sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valuestring;
		// printf("%s\n", sendfrom);
		// char *sendtime = cJSON_GetObjectItem(root, "sendtime")->valuestring;
		// printf("%s\n", sendtime);
		// char *content = cJSON_GetObjectItem(root, "content")->valuestring;
		// printf("%s\n", content);

		/*
		char content_text[1025];
		int i = 0;
		putchar('\"');
		for(i = 0; *(content+i) != 0; i++) {
			content_text[i] = *(content+i);
			putchar(*(content+i));
		}
		putchar('\"');
		content_text[i] = '\0';
		printf("you have a message from group %d, sent by %s at %s:%s", sendto, sendfrom, sendtime, content_text);
		//for group message, save chat record only when receiving a new message
		*/
		gdk_threads_enter();
		// save_chatrecord_group(message);

		gdk_threads_leave();
		//exec_cmd(13, "group", &sendto);
	}
	else if (strcmp(type, "friend-list-receipt") == 0)
	{
		//friend list
		int size = cJSON_GetObjectItem(root, "size")->valueint;
		cJSON *list = cJSON_GetObjectItem(root, "list");
		printf("friend list of user %s:\n", currentUser.user_id);
		friend_list_size = size;
		for (int i = 0; i < size; i++)
		{
			cJSON *item = cJSON_GetArrayItem(list, i);
			char *userid = cJSON_GetObjectItem(item, "userid")->valuestring;
			char *username = cJSON_GetObjectItem(item, "username")->valuestring;
			int status = cJSON_GetObjectItem(item, "status")->valueint;
			printf("%s [%s]\n", userid, (status ? "online" : "offline"));
			strcpy(friends[i].user_name, username);
			strcpy(friends[i].user_id, userid);
			friends[i].user_online = status;
		}
		printf("friend list size = %d \n", friend_list_size);
		gdk_threads_enter();
		//UNDO
		// update_friendlist(UPDATE_FRIENDLIST);
		gdk_threads_leave();
	}
	else if (strcmp(type, "group-create-receipt") == 0)
	{
		int status = cJSON_GetObjectItem(root, "status")->valueint;
		if (status == 1)
		{
			int groupID = cJSON_GetObjectItem(root, "groupID")->valueint;
			printf("create group success, new group ID is %d\n", groupID);
		}
		else
		{
			printf("create group failed");
		}
	}
	else if (strcmp(type, "group-list-receipt") == 0)
	{
		//group list
		int size = cJSON_GetObjectItem(root, "size")->valueint;
		cJSON *list = cJSON_GetObjectItem(root, "list");
		int i;
		printf("groups of user %s:\n", currentUser.user_id);
		group_list_size = size;
		for (i = 0; i < size; i++)
		{
			cJSON *item = cJSON_GetArrayItem(list, i);
			char *groupID = cJSON_GetObjectItem(item, "groupid")->valuestring;
			char *groupName = cJSON_GetObjectItem(item, "groupname")->valuestring;
			printf("group %d\n", groupID);
			strcpy(groupdata[i].groupID, groupID);
			strcpy(groupdata[i].g_name, groupName);
		}
		gdk_threads_enter();
		// update_grouplist(UPDATE_GROUPLIST);
		gdk_threads_leave();
	}
	// else if (strcmp(type, "group-join-receipt") == 0)
	// {
	// 	int groupID = cJSON_GetObjectItem(root, "groupID")->valueint;
	// 	int status = cJSON_GetObjectItem(root, "status")->valueint;
	// 	printf("join group %d %s\n", groupID, (status ? "success" : "fail"));
	// 	gdk_threads_enter();
	// 	update_grouplist(UPDATE_GROUPLIST);
	// 	gdk_threads_leave();
	// }
	// else if (strcmp(type, "group-quit-receipt") == 0)
	// {
	// 	int groupID = cJSON_GetObjectItem(root, "groupID")->valueint;
	// 	int status = cJSON_GetObjectItem(root, "status")->valueint;
	// 	printf("quit group %d %s\n", groupID, (status ? "success" : "fail"));
	// }
	// else if (strcmp(type, "add-to-contact-receipt") == 0)
	// {
	// 	char *contact = cJSON_GetObjectItem(root, "contact")->valuestring;
	// 	int status = cJSON_GetObjectItem(root, "status")->valueint;
	// 	printf("add contact %s %s\n", contact, (status ? "success" : "fail"));
	// 	gdk_threads_enter();
	// 	update_friendlist(UPDATE_FRIENDLIST);
	// 	gdk_threads_leave();
	// }
	// else if (strcmp(type, "friend-image-receipt") == 0)
	// {
	// 	cJSON_Print(root);
	// 	int status = cJSON_GetObjectItem(root, "image")->valueint;
	// 	char *username = cJSON_GetObjectItem(root, "sendto")->valuestring;
	// 	char *sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valuestring;
	// 	if (strcmp(username, sendfrom) == 0)
	// 	{
	// 		printf("friend-image-receipt:\n");
	// 		gdk_threads_enter();
	// 		change_my_portrait(status);
	// 		gdk_threads_leave();
	// 	}
	// 	else
	// 	{
	// 		printf("friend-image-receipt:\n");
	// 		gdk_threads_enter();
	// 		change_you_portrait(status);
	// 		gdk_threads_leave();
	// 	}
	// }
	printf("handle message over, client_socket = %d\n", client_socket);
	//gdk_threads_leave();
}

int send_function(char *message)
{
	char send_buffer[BUFFER_SIZE];
	memset(send_buffer, '\0', sizeof(send_buffer));
	strcpy(send_buffer, message);
	printf("sending message to server:\n%s\n", send_buffer);
	return send(client_socket, send_buffer, BUFFER_SIZE, 0);
}

int init_client()
{
	int try_time;
	struct sockaddr_in server_addr;

	client_socket = socket(AF_INET, SOCK_STREAM, 0); //创建客户端套接字
	if (client_socket == -1)
	{
		return -1;
	}
	server_addr.sin_addr.s_addr = inet_addr(str_ip);
	server_addr.sin_port = htons(MYPORT);
	server_addr.sin_family = AF_INET;
	try_time = 0; //如果不成功每隔一秒连接一次，最多10次

	while (try_time < 5 && connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		sleep(1);
		try_time++;
	}
	if (try_time >= 5)
		return -1;
	else
		return client_socket;
}

int build_packet(Kind kind, void *arg1, void *arg2, void *arg3)
{
	cJSON *root = cJSON_CreateObject();
	printf("build_packet init\n");
	if (root == NULL)
	{
		printf("create json object failed\n");
		return 1;
	}
	printf("build_packet  switch\n");
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
		//发送类型 发送对象 发送内容  
		cJSON_AddStringToObject(root, "type", "message/text");
		cJSON_AddStringToObject(root, "sendto", (char *)arg1);
		cJSON_AddStringToObject(root, "sendfrom", currentUser.user_id); 
		cJSON_AddStringToObject(root, "content", (char *)arg2);
		send_function(cJSON_Print(root)); 
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
	case friend_add:
		cJSON_AddStringToObject(root, "type", "add-friend-request");
		cJSON_AddStringToObject(root, "userid", currentUser.user_id);
		cJSON_AddStringToObject(root, "friendid", (char *)arg1);
		send_function(cJSON_Print(root));
		break;
	case list_update: //添加后更新好友列表
		cJSON_AddStringToObject(root, "type", "friend-list-request");
		cJSON_AddStringToObject(root, "userid", currentUser.user_id);
		send_function(cJSON_Print(root));
		break;
	case group_update:
		cJSON_AddStringToObject(root, "type", "group-list-request");
		cJSON_AddStringToObject(root, "userid", currentUser.user_id);
		send_function(cJSON_Print(root));
		break;
	case group_add:
		cJSON_AddStringToObject(root, "type", "add-group-request");
		cJSON_AddStringToObject(root, "userid", currentUser.user_id);
		cJSON_AddStringToObject(root, "groupid", (char *)arg1);
		send_function(cJSON_Print(root));
		break;
	}
	return 1;
}
