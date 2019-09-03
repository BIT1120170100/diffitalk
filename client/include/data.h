#ifndef data_h
#define data_h

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <time.h>

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

extern const int MYPORT = 3440;//约定端口
extern const int MAXLEN = 140;  //最大消息长度
extern const int STRING_LEN = 100;
extern const int MAX_GROUP_NUM = 100;
enum Gender{
    WOMAN,MAN
};
typedef struct message
{
    int id;
    char id_to[20];
    char id_from[20];     //消息的标识符
    char str[MAXLEN + 1]; //消息正文
    time_t send_time;
} Message;                //一条消息的结构体
typedef struct user{
    char user_name[STRING_LEN];
    int user_id;
    enum Gender gender;
    char user_password[STRING_LEN];
    char user_mail[STRING_LEN];
    char user_avatar[STRING_LEN];   //daiding
    char user_note[STRING_LEN];
    char user_birth[STRING_LEN];
    bool user_online;
}User;
typedef struct loginInfo{
    int user_id;
    char login_password;
}LoginInfo;
typedef union _data {
    User userinfo;   //用户信息
    Message message; //消息
} Data;            
typedef enum _kind
{
    regist,
    login,
    logout,
    chat,
    modify,
    friend_add,
    chat_together
    //注册		登录 		 登出		 发送消息    修改用户密码
} Kind; //用枚举变量表示
typedef enum Operate_freind{
    Ser_friend,
    Add_friend,
    Del_friend,
    Group_friend //将好友拉入群组
}Change_FKind; //对好友的操作

typedef struct C_friend{
    Change_FKind kind;
    int friend_id;
}C_Friend;

typedef struct _group{
    int owner_id;
    char g_name[STRING_LEN];
    int member_id[MAX_GROUP_NUM];
}Group;


typedef struct _packet{
	Kind kind;		        //包类型
	Data data;		        //数据包
}Packet;					      //通信协议
#endif
