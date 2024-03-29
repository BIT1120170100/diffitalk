#include "../include/main_window.h"
#include "../include/settings.h"
#include "../include/chatWindow.h"
#include "../include/group.h"
#include "../include/myself_setting.h"
#include "../include/list.h"
#include"../include/group.h"
#include"../include/data.h"
#include"../include/search.h"
//#include"main.h"
extern GtkWidget *main_window;
extern GtkWidget *login_window;
extern GtkWidget *regist_window;
extern GtkWidget *reset_window;
extern GtkWidget *settings_window;
extern GtkWidget *exit_window;
GtkWidget* scrolled_window;
/**************************************************/
/*名称：on_click_close
/*描述：主窗口关闭按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、关闭按钮
        参数2：data、gpointer 、输入参数
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void on_click_close(GtkWidget *button, gpointer data)
{
    gtk_widget_show_all(exit_window);
}
/**************************************************/
/*名称：on_click_exit
/*描述：确认关闭窗口确认按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、确认按钮
        参数2：data、gpointer 、输入参数
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void on_click_exit(GtkWidget *button, gpointer data)
{
    gtk_main_quit();
}
/**************************************************/
/*名称：on_click_exit_cancel
/*描述：确认关闭窗口取消按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、确认按钮
        参数2：data、gpointer 、输入参数
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void on_click_exit_cancel(GtkWidget *button, GtkWidget *data)
{
    gtk_widget_hide_all(data);
}
/**************************************************/
/*名称：create_regist
/*描述：创建确认退出界面
/*作成日期： 
/*参数：VOID
/*返回值：GtkWidget*
/*作者：刘梦涵
/***************************************************/
GtkWidget *create_exit()
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *exit;
    GtkWidget *cancel;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    label = gtk_label_new("请问是否退出？");
    exit = gtk_button_new_with_label("退出");
    cancel = gtk_button_new_with_label("取消");

    box = gtk_vbox_new(FALSE, 0);
    box1 = gtk_hbox_new(TRUE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box1), exit, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box1), cancel, FALSE, FALSE, 5);

        //
    g_signal_connect(G_OBJECT(exit), "clicked",
                     G_CALLBACK(on_click_exit), NULL);
    g_signal_connect(G_OBJECT(cancel), "clicked",
                     G_CALLBACK(on_click_exit_cancel), window);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(on_click_exit_cancel), window); //直接关闭确认退出窗口和取消是一个效果
    return window;
}

//创建主窗口
GtkWidget *create_main_window()
{
    GtkWidget *window;
    GtkWidget *head;
    GtkWidget *headbox;
    GtkWidget *username;
    GtkWidget *searchtext;
    GtkWidget *searchbutton;
    GtkWidget *list;
    GtkWidget *group;
    GtkWidget *settingsbutton;
    GtkWidget *box1;
    GtkWidget *table1;
    GtkWidget *box2;
    //GtkWidget* box3;
    //GtkWidget *scroll;
    //GtkWidget* box4;
    GtkWidget *s;
    //GtkWidget* menu;
    //lu测试
    GtkWidget *button;
    //
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_widget_set_size_request(window, 350, 780);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(window), "delete_event",
                     G_CALLBACK(on_click_close), exit_window);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); //
  //  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    box1 = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box1);
     
    table1 = gtk_table_new(1, 5, TRUE);
    head = gtk_button_new();
    headbox = gtk_fixed_new();

    gtk_fixed_put(GTK_FIXED(headbox),head,120,0);
    gtk_widget_set_size_request(head, 70, 70);
   // g_print("%s\n",currentUser.user_id);
    username = gtk_label_new(currentUser.user_id);
    gtk_box_pack_start(GTK_BOX(box1), headbox, FALSE, FALSE, 3);
    gtk_box_pack_start(GTK_BOX(box1), username, FALSE, FALSE, 3);
    gtk_table_set_row_spacings(GTK_TABLE(table1), 5);
    gtk_table_set_col_spacings(GTK_TABLE(table1), 5);
    gtk_box_pack_start(GTK_BOX(box1), table1, FALSE, FALSE, 3);
    
    

    s = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box1), s, FALSE, FALSE, 3);

    box2 = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box1), box2, FALSE, FALSE, 3);

    list=gtk_button_new_with_label("朋友");
    group=gtk_button_new_with_label("小组");
    gtk_box_pack_start(GTK_BOX(box2),list,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box2),group,TRUE,TRUE,0);
    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window),10);
    gtk_widget_set_size_request(scrolled_window,70,400);

    g_signal_connect(group,"clicked",
        G_CALLBACK(on_click_group),scrolled_window);
    g_signal_connect(list,"clicked",
        G_CALLBACK(on_click_friend),scrolled_window);
    gtk_box_pack_start(GTK_BOX(box1),scrolled_window,FALSE,FALSE,3);
    
    searchbutton = gtk_button_new_with_label("搜索");
    g_signal_connect(searchbutton, "clicked",
                     G_CALLBACK(create_search), NULL);
    gtk_box_pack_start(GTK_BOX(box1), searchbutton, FALSE, FALSE, 3);
    settingsbutton = gtk_button_new_with_label("设置");
    gtk_box_pack_start(GTK_BOX(box1), settingsbutton, FALSE, FALSE, 3);
    g_signal_connect(settingsbutton, "button_press_event",
                     G_CALLBACK(settings), settings_window);

    
    // button = gtk_button_new_with_label("跳到单人聊天界面");
    // g_signal_connect(G_OBJECT(exit), "clicked",
                    //  G_CALLBACK( createChatWindow), NULL); //UNDO
    button = gtk_button_new_with_label("聊天界面");
    gtk_box_pack_start(GTK_BOX(box1), button, FALSE, FALSE, 3);
    g_signal_connect(G_OBJECT(button), "clicked",
                     G_CALLBACK(createChatWindow), NULL);
    button = gtk_button_new_with_label("群组聊天界面");
    gtk_box_pack_start(GTK_BOX(box1), button, FALSE, FALSE, 3);
    g_signal_connect(G_OBJECT(button), "clicked",
                     G_CALLBACK(createMultiChatWindow), NULL);   //!!!!group chat function need to rewrite!!!
    button = gtk_button_new_with_label("新建群聊");
    gtk_box_pack_start(GTK_BOX(box1), button, FALSE, FALSE, 3);
    g_signal_connect(G_OBJECT(button), "clicked",
                     G_CALLBACK(create_group), NULL);
    return window;
}