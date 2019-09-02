#include <stdio.h>  
#include <stdlib.h>  
#include <mysql.h> 
/**************************************************/
/*名称：search.c
/*描述：连接数据库成功后,查询数据库中内容
/*作成日期：2019-09-02  
/*作者：王子嘉
/***************************************************/ 
//gcc -o search -g search.c  -I /usr/include/mysql/ -L /usr/lib/x86_64-linux-gnu/ -l mysqlclient
void search() {  
    MYSQL *conn_ptr;  
    MYSQL_RES *res_ptr;  
    MYSQL_ROW sqlrow;  
    MYSQL_FIELD *fd;  
    int res, i, j;  
  
    conn_ptr = mysql_init(NULL);  
    if (!conn_ptr) {  
        return EXIT_FAILURE;  
    }  
    conn_ptr = mysql_real_connect(conn_ptr, "localhost", "root", "123456", "server", 0, NULL, 0);//用root运行./XXX成功 “server”-数据库名称  
    if (conn_ptr) {
        printf("Connection success\n");  
        res = mysql_query(conn_ptr, "select name,age from user"); //查询语句  
        if (res) {         
            printf("SELECT error:%s\n",mysql_error(conn_ptr));     
        } else {        
            res_ptr = mysql_store_result(conn_ptr);             //取出结果集  
            if(res_ptr) {               
                printf("%lu Rows\n",(unsigned long)mysql_num_rows(res_ptr));   
                j = mysql_num_fields(res_ptr);          
                while((sqlrow = mysql_fetch_row(res_ptr)))  {   //依次取出记录  
                    for(i = 0; i < j; i++)         
                        printf("%s\t", sqlrow[i]);              //输出  
                    printf("\n");          
                }              
                if (mysql_errno(conn_ptr)) {                      
                    fprintf(stderr,"Retrive error:s\n",mysql_error(conn_ptr));               
                }        
            }        
            mysql_free_result(res_ptr);        
        }  
    } else {  
        printf("Connection failed\n");  
    }  
    mysql_close(conn_ptr);  
    //return EXIT_SUCCESS;  
}  
