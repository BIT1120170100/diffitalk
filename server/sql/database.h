
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

int passWordMatch(char *userid, char *password);
char *addUser(char *, char *,char*);
int searchUser(char *);
int addFriend(char* user_id, char** friend_id);
int addGroup(char * g_id, char* user_id);
int intoGroup(char * g_id, char* user_id);
int delGroup(char* group_id);
void sql_init();
void sql_quit();
#endif