#include "../include/login.h"
#include "../include/check.h"
#include "../include/main_window.h"
#include <math.h>
extern GtkWidget *main_window;
extern GtkWidget *login_window;
extern GtkWidget *regist_window;
extern GtkWidget *reset_window;
extern GtkWidget *settings_window;
extern GtkWidget *exit_window;
login_info info;
void showDialog(char * mess)
{
          GtkWidget *dialog;
    //初始化GTK环境    
   // gtk_init(&argc, &argv);
    dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK, argv[1], mess);
    gtk_window_set_title(GTK_WINDOW(dialog), "系统提示");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    //绑定信号函数,点击退出时执行的操作 
    //g_signal_connect(GTK_OBJECT(dialog), "destroy", GTK_SIGNAL_FUNC(close_app), NULL);
    //gtk_widget_show_all(dialog);
    //gtk_main();
    return ;
}

/**************************************************/
/*名称：on_login_clicked
/*描述：登录按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、登录按钮
        参数2：data、regist_info* 、输入参数、登录信息
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void on_login_clicked(GtkWidget *button, login_info *data)
{
        const char *username = gtk_entry_get_text(GTK_ENTRY(data->user_id));
        const char *password = gtk_entry_get_text(GTK_ENTRY(data->password));
        g_print("username:%s\n", username);
        g_print("password:%s\n", password);
        int userid =0;
        //字符转换数字
        for(int i=4;i>=0;--i)
        {
                userid += power(10,(4-i))*(username[i]-'0' )  ;
        }

        if (loginAndRigistCheck(userid,password,login, char  *c_ipAddr))
        { 
                
                gtk_widget_hide_all(login_window);
                
                main_window = create_main_window();
                gtk_widget_show_all(main_window);
               
        }
        else
        {
                showDialog("当前不存在该用户或密码输入错误！");//
        }
        //g_print("username:%s\n",username);
        //g_print("password:%s\n",password);
}
/**************************************************/
/*名称：login_to_regist_clicked
/*描述：注册按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、注册按钮
        参数2：data、gpointer 、输入参数、
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void login_to_regist_clicked(GtkWidget *button, gpointer data)
{
        gtk_widget_hide_all(login_window);
        gtk_widget_show_all(regist_window);
}
/**************************************************/
/*名称：login_to_reset_clicked
/*描述：密码重置按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、重置按钮
        参数2：data、gpointer 、输入参数、
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void login_to_reset_clicked(GtkWidget *button, gpointer data)
{
        gtk_widget_hide_all(login_window);
        gtk_widget_show_all(reset_window);
}

/**************************************************/
/*名称：create_login
/*描述：创建登录界面
/*作成日期： 
/*参数：VOID
/*返回值：GtkWidget*
/*作者：刘梦涵
/***************************************************/
GtkWidget *create_login()
{
        GtkWidget *window;
        GtkWidget *box;
        GtkWidget *box1;
        GtkWidget *box2;
        GtkWidget *label1;
        GtkWidget *label2;
        GtkWidget *entry1;
        GtkWidget *entry2;
        GtkWidget *login;
        GtkWidget *reset;
        GtkWidget *regst;
        GtkWidget *sep;

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(G_OBJECT(window), "destroy",
                         G_CALLBACK(gtk_main_quit), NULL);
        gtk_window_set_title(GTK_WINDOW(window), "log in DiffiTalk");
        gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(window), 20);

        box = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(window), box);
        box1 = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 5);
        box2 = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 5);

        label1 = gtk_label_new("userid:");
        entry1 = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(box1), label1, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(box1), entry1, FALSE, FALSE, 5);

        label2 = gtk_label_new("password:");
        entry2 = gtk_entry_new();
        gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
        gtk_box_pack_start(GTK_BOX(box2), label2, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(box2), entry2, FALSE, FALSE, 5);

        login = gtk_button_new_with_label("log in");

        info.user_id = entry1;
        info.password = entry2;
        g_signal_connect(G_OBJECT(login), "clicked",
                         G_CALLBACK(on_login_clicked), &info);
        gtk_box_pack_start(GTK_BOX(box), login, FALSE, FALSE, 5);

        sep = gtk_hseparator_new();
        gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 5);

        reset = gtk_button_new_with_label("password reset");
        g_signal_connect(G_OBJECT(reset), "clicked",
                         G_CALLBACK(login_to_reset_clicked), window);
        gtk_box_pack_start(GTK_BOX(box), reset, FALSE, FALSE, 5);

        regst = gtk_button_new_with_label("register");
        g_signal_connect(G_OBJECT(regst), "clicked",
                         G_CALLBACK(login_to_regist_clicked), window);
        gtk_box_pack_start(GTK_BOX(box), regst, FALSE, FALSE, 5);

        return window;
}