#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

/**************************************************/
/*名称：passWordMatch
/*描述 密码匹佩
/*作成日期： 
/*参数：
        用户登陆id和密码
/*返回值：INT
/*作者：池夏烨
/***************************************************/

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void sql_init()
{
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, d_server, d_user, d_password, d_database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}
void sql_quit()
{
    mysql_free_result(res);
    mysql_close(conn);

    printf("finish! \n");
}
char *addUser(char *user_name, char *user_password, char *email)
{
    sql_init();
    int t;
    char insert_query[200];
    char table_name[50];
    char field[100];
    char left[5] = "(";
    char right[5] = ") ";
    char quote[5] = "\"";
    char valuess[20] = "values";
    char message[200] = {0}; 
    char error[100] = "error";
 
    memset(message, 0, sizeof(message));
    memset(field, 0, sizeof(message));
    memset(table_name, 0, sizeof(message));

    strcpy(table_name, "user");

    strcpy(insert_query, insert_head); //insert into

    strcpy(field, "user_name,user_password,user_mail");

    strcpy(message, quote);

    strcat(message, user_name);
    strcat(message, quote);
    strcat(message, ",");
    strcat(message, quote);
    strcat(message, user_password);
    strcat(message, quote);
    strcat(message, ",");
    strcat(message, quote);
    strcat(message, email);
    strcat(message, quote);
    /*把几个变量字符串连接成一个完整的mysql命令*/
    strcat(insert_query, table_name);
    strcat(insert_query, left);
    strcat(insert_query, field);
    strcat(insert_query, right);

    printf("1:%s\n", insert_query);
    printf("2:%s\n", valuess);
    strcat(insert_query, valuess);

    printf("%s\n", insert_query);

    strcat(insert_query, left);
    strcat(insert_query, message);
    strcat(insert_query, right);
    printf("%s\n", insert_query);
    printf("ok!\n");

    t = mysql_real_query(conn, insert_query, strlen(insert_query));
    if (t)
    {
        printf("failed to query:%s\n", mysql_error(conn));
        sql_quit();
        return error;
    }

    // sql_quit();
    // sql_init(); 
    char query_id[100] = "select max(user_id) from user";
    mysql_query(conn, query_id);
    printf("query_id: %s\n",query_id);
    res = mysql_store_result(conn);
    if(res==NULL)
    {
        printf("res is null\n");
        return error;
    }
    printf("resget\n");
    if((row = mysql_fetch_row(res)) != NULL){ 
        printf("row0 is : %s\n", row[0]);
        char *last_id = row[0];
        sql_quit();
        return last_id;
    }
    else
    {
        printf("no user!\n");
        // mysql_free_result(res);
        sql_quit();
        return error;
    }
    //TODO 返回用户id
}
/**************************************************/
/*名称：searchUser
/*描述 查找用户
/*作成日期： 
/*参数：
        用户id
/*返回值：INT
/*作者：李妙宇
/***************************************************/
int searchUser(int friend_id)
{
}
int addFriend(int user_id, int add_id)
{
}
int addGroup(char *g_name, char *owner_id)
{
    sql_init();
    int t;
    char insert_query[200];
    char table_name[50] = "groups";
    char field[100];
    char left[5] = "(";
    char right[5] = ") ";
    char quote[] = "\"";
    char devide[] = ",";
    char values[50] = "values";
    char message[200] = {0};
    char g_id[] = "select max(id) from tablename";

    memset(message, 0, sizeof(message));
    memset(field, 0, sizeof(message));
    memset(table_name, 0, sizeof(message));

    strcpy(insert_query, insert_head); //insert into

    strcpy(field, "owner_id,g_name");

    strcpy(message, owner_id);
    strcat(message, devide);
    strcat(message, quote);
    strcat(message, g_name);
    strcat(message, quote);
    /*把几个变量字符串连接成一个完整的mysql命令*/
    strcat(insert_query, table_name);
    strcat(insert_query, left);
    strcat(insert_query, field);
    strcat(insert_query, right);
    strcat(insert_query, values);
    strcat(insert_query, left);
    strcat(insert_query, message);
    strcat(insert_query, right);
    printf("%s\n", insert_query);

    t = mysql_real_query(conn, insert_query, strlen(insert_query));
    if (t)
    {
        printf("failed to query:%s\n", mysql_error(conn));
        return 0;
    }

    printf("OK\n");

    mysql_free_result(res);
    mysql_close(conn);

    printf("finish! \n");
    return 1;
    sql_quit();
}

int delGroup(char *group_id)
{
    sql_init();
    int t;
    char drop_query[200] = {0};
    char table_name[20] = "groupinfo";

    strcpy(drop_query, drop_msg_head);

    strcat(drop_query, table_name);
    strcat(drop_query, " where g_id =");
    strcat(drop_query, group_id);
    printf("%s\n", drop_query);

    t = mysql_real_query(conn, drop_query, strlen(drop_query));
    if (t)
    {
        printf("failed to query:%s\n", mysql_error(conn));
        return 0;
    }
    if (mysql_query(conn, drop_query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        sql_quit();
        return 0;
    }
    else
    {
        sql_quit();
        return 1;
    }
}
int intoGroup(char *g_id, char *user_id)
{
}
int passWordMatch(char *userid, char *user_password)
{
    //    char query[] = "select ";
    printf("\nuserid:%s\nuser_password:%s\n", userid, user_password);
    char query[256] = "select user_password from user WHERE user_id=";

    strcat(query, userid);

    sql_init();

    mysql_query(conn, query);
    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("row0 is : %s\n", row[0]);

        if (strcmp(row[0], user_password))
        {
            printf("password wrong!\n");
            mysql_free_result(res);
            mysql_close(conn);
            return 0;
        }
        printf("success!\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    else
    {
        printf("no user!\n");
        // mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }
}