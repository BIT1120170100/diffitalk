#include <stdlib.h>  
#include <stdio.h>  
#include <mysql.h> 
/**************************************************/
/*名称：delete.c 
/*描述：删除数据库内容 需修改
/*作成日期：2019-09-02
/*作者： 王子嘉
/***************************************************/
////gcc -o delete -g delete.c  -I /usr/include/mysql/ -L /usr/lib/x86_64-linux-gnu/ -l mysqlclient
void delete() {  
    MYSQL *conn_ptr;  
    int res;  
  
    conn_ptr = mysql_init(NULL);  
    if (!conn_ptr) {  
        printf("mysql_init failed\n");  
        return EXIT_FAILURE;  
    }  
    conn_ptr = mysql_real_connect(conn_ptr, "localhost", "root", "root", "server", 0, NULL, 0);  
    if (conn_ptr) {  
//  res = mysql_query(conn_ptr, "insert into user values(null,'Ann',5)");   
    res = mysql_query(conn_ptr, "delete from user where name = 'Ann' and age < 10");  //更改delete语句
        if (!res) {     //输出受影响的行数  
            printf("Inserted %lu rows\n",(unsigned long)mysql_affected_rows(conn_ptr));   
        }  else {       //打印出错误代码及详细信息  
            fprintf(stderr, "Insert error %d: %sn",mysql_errno(conn_ptr),mysql_error(conn_ptr));  
        }  
    } else {  
        printf("Connection failed\n");  
    }  
    mysql_close(conn_ptr);  
    //return EXIT_SUCCESS;  
}  