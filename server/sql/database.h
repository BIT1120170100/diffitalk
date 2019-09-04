
#ifndef database_h
#define database_h

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char d_server[] = "localhost";
const char d_user[] = "root";
const char d_password[] = "root";
const char d_database[] = "server";



const char select_head[50] = "select * from ";
const char desc_head[50] = "desc ";
const char insert_head[200] = "insert into ";
const char drop_msg_head[50] = "delete from ";
const char change_base_head[50] = "use ";

typedef struct userlist{
    char id[100][20];
    char name[100][20];
    int len;
}List;


int passWordMatch(char *userid, char *password);
char *addUser(char *, char *,char*);
char *addFriend(char* user_id, char* friend_id);
void get_FriendInfo(char *user_id , List &f_info);
void getGroup(char *user_id,List &g_info);
int addGroup(char * g_name, char* user_id);
int intoGroup(char * g_id, char* user_id);
int delGroup(char* group_id);
char* getUserDetail(char *userid);
void sql_init();
void sql_quit();
#endif