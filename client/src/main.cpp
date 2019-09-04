#include "../include/chatWindow.h"
#include "../include/messList.h"
#include "../include/myInfo.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include "util/util.h" 
#include <stdlib.h>   
#include <arpa/inet.h>
#include <pthread.h>
#include "json/cJSON.h" 
/**************************************************/
/*名称： 
/*描述：主界面函数，定义主调函数，初始化函数等功能主函数
/*作成日期：  
/*参数： 
/*返回值： 
/*作者： 
/***************************************************/

#include "../include/main.h"
#include "../include/login.h"
#include "../include/regist.h"
#include "../include/reset.h"
#include "../include/settings.h"
#include "../include/main_window.h"

GtkWidget *main_window;
GtkWidget *login_window;
GtkWidget *regist_window;
GtkWidget *reset_window;
GtkWidget *settings_window;
GtkWidget *exit_window;

char *str_ip;

int main(int argc, char *argv[])
{
        gtk_init(&argc, &argv);
        str_ip=(char*)argv[1];
        FILE *fp;
        char theme;
        if((fp=fopen("themes/theme.txt","r"))==NULL){
                printf("cannot open file\n");
        }
        theme=getc(fp);
        fclose(fp);
        printf("%c\n",theme);
        switch(theme){
                case '1':
                        gtk_rc_parse("themes/gtkrc1");
                        break;
                case '2':
                        gtk_rc_parse("themes/gtkrc2");
                        break;
                case '3':
                        gtk_rc_parse("themes/gtkrc3");
                        break;
                case '4':
                        gtk_rc_parse("themes/gtkrc4");
                        break;
                case '5':
                        gtk_rc_parse("themes/gtkrc5");
                        break;
        }
        
        //main_window=create_main_window();
        login_window = create_login();
        regist_window = create_regist();
        reset_window = create_reset();
        settings_window = create_settings();
        exit_window = create_exit();
        gtk_widget_show_all(login_window);

        gtk_main();
        return 0;
}