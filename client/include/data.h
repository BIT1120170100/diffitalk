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
#define BUFFER_SIZE 2048 
//extern
const int MYPORT = 6000; //约定端口
const int MAXLEN = 140;  //最大消息长度
const int STRING_LEN = 100;
const int MAX_GROUP_NUM = 100;
enum Gender
{
    WOMAN,
    MAN
};
typedef struct message
{
    int id; //必须是五位数
    char id_to[20];
    char id_from[20];     //消息的标识符
    char str[MAXLEN + 1]; //消息正文
    time_t send_time;
} Message; //一条消息的结构体
typedef struct user
{
    char user_name[STRING_LEN];
    int user_id;
    enum Gender gender;
    char user_password[STRING_LEN];
    char user_mail[STRING_LEN];
    char user_avatar[STRING_LEN]; //daiding
    char user_note[STRING_LEN];
    char user_birth[STRING_LEN];
    bool user_online;
} User;
typedef struct loginInfo
{
    int user_id;
    char login_password;
} LoginInfo;
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
    chat_together,
    list_update,
    group_add,
     group_update
    //注册		登录 		 登出		 发送消息    修改用户密码
} Kind; //用枚举变量表示
typedef enum Operate_freind
{
    Ser_friend,
    Add_friend,
    Del_friend,
    Group_friend //将好友拉入群组
} Change_FKind;  //对好友的操作

typedef struct C_friend
{
    Change_FKind kind;
    int friend_id;
} C_Friend;

typedef struct _group
{
    int owner_id;
    char g_name[STRING_LEN];
    int member_id[MAX_GROUP_NUM];
} Group;
typedef struct _zu
{
    char groupID[STRING_LEN];
    char g_name[STRING_LEN]; 
} zu; 
typedef struct _packet
{
    Kind kind; //包类型
    Data data; //数据包
} Packet;      //通信协议

typedef struct MyUser
{
    char user_name[STRING_LEN];
    char user_id[5]; //修改为字符串
    //enum Gender gender;
    char user_password[STRING_LEN];
    char user_mail[STRING_LEN];
    char user_avatar[STRING_LEN]; //daiding
    char user_note[STRING_LEN];
    char user_birth[STRING_LEN];
    bool user_online;
    
} MyUser;

//登陆用户
static MyUser currentUser;
//当前用户的好友
static MyUser friends[MAXLEN];
static zu groupdata[MAXLEN];

static int friend_list_size=0;
static int group_list_size=0;
// 创建的套接字
static int client_socket; 
// 服务器id
static char *str_ip = "192.168.43.77";
//本机的ip
static char *my_ip;
#endif
