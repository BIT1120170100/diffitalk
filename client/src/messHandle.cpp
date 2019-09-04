#include "../include/messHandle.h"
#include "../include/data.h"

/**************************************************/
/*名称：send_function
/*描述：负责发送信息的函数
/*作成日期：2016.8.31
/*参数：
	char *message 所要发送的函数
/*返回值：VOID
/*作者：张宇森
/***************************************************/
//TODO: send in another thread?
int send_function(char *message)
{
        ;
        // char send_buffer[BUFFER_SIZE];
        // memset(send_buffer, '\0', sizeof(send_buffer));
        // strcpy(send_buffer, message);
        // printf("sending message to server:\n%s\n", send_buffer);
        // return send(serverfd, send_buffer, BUFFER_SIZE, 0);
}

/**************************************************/
/*名称：exec_cmd
/*描述：上面所有相关操作的执行部分的实现
/*作成日期：2016.8.31
/*参数：
	int op 操作类型
	void *arg1 对于不同操作类型有不同的意义
	void *arg2 对于不同操作类型有不同的意义
/*返回值：VOID
/*作者：张宇森
/***************************************************/
void exec_cmd(int op, void *arg1, void *arg2)
{
        cJSON *root = cJSON_CreateObject();
        printf("exec_cmdinit==============\n");
        if (root == NULL)
        {
                printf("create json object failed\n");
                return;
        }
        //&& strlen(current_username) == 0
        if (op >= 3)
        {
                printf("haven't logged in");
                return;
        }
        printf("%d===================\n", op);
        switch (op)
        {
                printf("exec_cmdinit switch==============\n");
        //send to server:      0 <any string>
        case 0:
                send_function((char *)arg1);
                break;

        //register:            1 <username> <password>
        case 1:
                cJSON_AddStringToObject(root, "type", "register-message");
                cJSON_AddStringToObject(root, "username", (char *)arg1);
                cJSON_AddStringToObject(root, "password", (char *)arg2);
                send_function(cJSON_Print(root));
                break;

        //login:               2 <username> <password>
        case 2:
                cJSON_AddStringToObject(root, "type", "login-message");
                cJSON_AddStringToObject(root, "username", (char *)arg1);
                cJSON_AddStringToObject(root, "password", (char *)arg2);
                send_function(cJSON_Print(root));
                break;
        }
        return;
}