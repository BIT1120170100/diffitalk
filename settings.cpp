
#include"include/settings.h"
//#include"main.h"
extern GtkWidget* main_window;
extern GtkWidget* login_window;
extern GtkWidget* regist_window;
extern GtkWidget* reset_window;
extern GtkWidget* settings_window;
extern GtkWidget* exit_window;
/**************************************************/
/*名称：settings
/*描述 设置按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、设置按钮
        参数2：data、gpointer 、输入参数
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void settings(GtkWidget* button,gpointer data){
    gtk_widget_show_all(settings_window);
}
/**************************************************/
/*名称：settings
/*描述 关闭设置按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、关闭按钮
        参数2：data、gpointer 、输入参数
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void on_settings_close(GtkWidget* button,GtkWidget* data){
    gtk_widget_hide_all(data);
}

GtkWidget* create_settings(){
    GtkWidget* window;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window),"destroy",
			G_CALLBACK(on_settings_close),window);

    
    return window;
}

