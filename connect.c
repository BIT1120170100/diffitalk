#include <stdlib.h>  
#include <stdio.h>  
#include <mysql.h> 
/**************************************************/
/*名称：connect.c 
/*描述：连接数据库
/*作成日期：2019-09-02 
/*参数：conn_ptr 连接数据库是否成功
/*返回值： 0/1
/*作者： 王子嘉
/***************************************************/
//gcc -o connect -g connect.c  -I /usr/include/mysql/ -L /usr/lib/x86_64-linux-gnu/ -l mysqlclient
void connect() {  
    MYSQL *conn_ptr;  
  
    conn_ptr = mysql_init(NULL);  
    if (!conn_ptr) {  
        printf("mysql_init failed\n");  
        return EXIT_FAILURE;  
    }  
    conn_ptr = mysql_real_connect(conn_ptr, "localhost", "root", "123456", "server", 0, NULL, 0);  
    //root 为用户名 123456为密码 test为要连接的database  
  
    if (conn_ptr) {  
        printf("Connection success\n");  
    } else {  
        printf("Connection failed\n");  
    }  
    mysql_close(conn_ptr);  
    //return EXIT_SUCCESS;  
}  
