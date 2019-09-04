#include <math.h>
#include <gtk/gtk.h>
#include "../include/data.h"
#include "../include/regist.h"
#include "../include/check.h"
#include "../include/errorMess.h"
#include "../include/main_window.h" 
// #include <regex>
extern GtkWidget *main_window;
extern GtkWidget *login_window;
extern GtkWidget *regist_window;
extern GtkWidget *reset_window;
extern GtkWidget *settings_window;
extern GtkWidget *exit_window;
regist_info registinfo;

/*
int check_email(const char email_address[])
{
    std::regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
    // 正则表达式，匹配规则：
    // 第1组（即用户名），匹配规则：0至9、A至Z、a至z、下划线、点、连字符之中
    // 的任意字符，重复一遍或以上
    // 中间，一个“@”符号
    // 第二组（即域名），匹配规则：0至9或a至z之中的任意字符重复一遍或以上，
    // 接着一个点，接着a至z之中的任意字符重复2至3遍（如com或cn等），
    // 第二组内部的一组，一个点，接着a至z之中的任意字符重复2遍（如cn或fr等）
    // 内部一整组重复零次或一次
    int flag=regex_match( email_address, pattern );
    // 输入文件结尾符（Windows用Ctrl+Z，UNIX用Ctrl+D）结束循环
    return flag;
}
 */


/**************************************************/
/*名称：on_register_clicked
/*描述：注册按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、注册按钮
        参数2：data、regist_info* 、输入参数、注册信息
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void on_register_clicked(GtkWidget *button, regist_info *data)
{
    const char *userid = gtk_entry_get_text(GTK_ENTRY(data->user_id));
    const char *password = gtk_entry_get_text(GTK_ENTRY(data->password));
    const char *rpassword = gtk_entry_get_text(GTK_ENTRY(data->rpassword));
    const char *email = gtk_entry_get_text(GTK_ENTRY(data->email));
    
    //密码不相同
    if(strcmp(password,rpassword)!=0)
    {
         showDialog("两次密码输入不相同！请重新输入"); //
         return ;
    }
    // else if(check_email(email))
    // {
    //      showDialog("两次密码输入不相同！请重新输入"); //
    //      return ;
    // }


    // //先设置本地ip 
    char ui[MAXLEN],pw[MAXLEN],rpw[MAXLEN],e[MAXLEN];
    strcpy(ui,userid);
    strcpy(pw,password);
    strcpy(e,email);
     if (loginAndRigistCheck(ui, pw, regist, str_ip,e))
    {
        gtk_widget_hide_all(login_window);
        main_window = create_main_window();
        gtk_widget_show_all(main_window);
    }
    else
    {
        showDialog("注册失败！"); //
    }
} 
/**************************************************/
/*名称：create_regist
/*描述：创建注册界面
/*作成日期： 
/*参数：VOID
/*返回值：GtkWidget*
/*作者：刘梦涵
/***************************************************/
GtkWidget *create_regist()
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *box4;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;
    GtkWidget *regst;
    GtkWidget *sep;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "delete_event",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "register");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    box1 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 5);
    box2 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 5);
    box3 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box3, FALSE, FALSE, 5);
    box4 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box4, FALSE, FALSE, 5);

    label1 = gtk_label_new("username:");
    entry1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1), label1, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(box1), entry1, FALSE, FALSE, 5);

    label2 = gtk_label_new("password:");
    entry2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry2), FALSE);
    gtk_box_pack_start(GTK_BOX(box2), label2, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(box2), entry2, FALSE, FALSE, 5);

    label3 = gtk_label_new("confirm password:");
    entry3 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry3), FALSE);
    gtk_box_pack_start(GTK_BOX(box3), label3, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(box3), entry3, FALSE, FALSE, 5);

    label4 = gtk_label_new("email:");
    entry4 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box4), label4, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(box4), entry4, FALSE, FALSE, 5);

    sep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box), sep, FALSE, FALSE, 5);

    registinfo.user_id = entry1;
    registinfo.password = entry2;
    registinfo.rpassword = entry3;
    registinfo.email = entry4;
    regst = gtk_button_new_with_label("register");
    g_signal_connect(G_OBJECT(regst), "clicked",
                     G_CALLBACK(on_register_clicked), &registinfo);
    gtk_box_pack_start(GTK_BOX(box), regst, FALSE, FALSE, 5);
    return window;
}