
#include"../include/settings.h"
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
void settings(GtkWidget* button,GtkWidget* data){
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
gint on_settings_close(GtkWidget* button,GtkWidget* data){
    gtk_widget_hide_all(settings_window);
    return TRUE;
}

void on_radio_clicked(GtkWidget* radio,gint data){
    GdkColor color;
    switch((int)data){
        case 1:
        color=white;
        break;
        case 2:
        color=skyblue;
        break;
        case 3:
        color=red;
        break;
        case 4:
        color=blue;
        break;
        case 5:
        color=aliceblue;
        break;
    }
    
}

GtkWidget* create_settings(){
    GtkWidget* window;
    GtkWidget* box;
    GtkWidget* box1;
    GtkWidget* frame;
    GtkWidget* radio1;
    GtkWidget* radio2;
    GtkWidget* radio3;
    GtkWidget* radio4;
    GtkWidget* radio5;
    GSList* group;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window),"delete_event",
			G_CALLBACK(on_settings_close),window);

    
    box=gtk_hbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),box);
    frame=gtk_frame_new("style:");
    gtk_box_pack_start(GTK_BOX(box),frame,FALSE,FALSE,5);
    box1=gtk_vbox_new(FALSE,0);
    gtk_container_set_border_width(GTK_CONTAINER(box1),10);
    gtk_container_add(GTK_CONTAINER(frame),box1);

    radio1=gtk_radio_button_new_with_label(NULL,"white");
    g_signal_connect(G_OBJECT(radio1),"released",
                    G_CALLBACK(on_radio_clicked),(gpointer)1);
    gtk_box_pack_start(GTK_BOX(box1),radio1,FALSE,FALSE,5);

    group=gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1));
    radio2=gtk_radio_button_new_with_label(group,"skyblue");
    g_signal_connect(G_OBJECT(radio2),"released",
                    G_CALLBACK(on_radio_clicked),(gpointer)2);
    gtk_box_pack_start(GTK_BOX(box1),radio2,FALSE,FALSE,5);

    group=gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio2));
    radio3=gtk_radio_button_new_with_label(group,"red");
    g_signal_connect(G_OBJECT(radio3),"released",
                    G_CALLBACK(on_radio_clicked),(gpointer)3);
    gtk_box_pack_start(GTK_BOX(box1),radio3,FALSE,FALSE,5);

    group=gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio3));
    radio4=gtk_radio_button_new_with_label(group,"blue");
    g_signal_connect(G_OBJECT(radio4),"released",
                    G_CALLBACK(on_radio_clicked),(gpointer)4);
    gtk_box_pack_start(GTK_BOX(box1),radio4,FALSE,FALSE,5);

    group=gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio4));
    radio5=gtk_radio_button_new_with_label(group,"aliceblue");
    g_signal_connect(G_OBJECT(radio5),"released",
                    G_CALLBACK(on_radio_clicked),(gpointer)5);
    gtk_box_pack_start(GTK_BOX(box1),radio5,FALSE,FALSE,5);

    return window;
}

