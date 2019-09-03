/**************************************************/
/*名称：个人信息页面
/*描述：实现用户个人信息的修改
/*作成日期： 2019/9/1
/*参数：VOID
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
#include <gtk/gtk.h>
#include "../include/myself_setting.h"
static GtkWidget *entry_username;
static GtkWidget *entry_image;
static GtkWidget *entry_sign;
static GtkWidget *entry_mail;
static gchar *sex = "男"; //用于确定性别

/**************************************************/
/*名称：on_sure_clicked
/*描述：点击“确定”按钮后在后台打印出修改的信息,应该改为某种写入数据库操作
/*作成日期：未完成
/*参数：
        参数1：button、GtkWidget*、输入参数、“确认”按钮
        参数2：data、gpointer、输入参数、传入的参数
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
inline void on_sure_clicked(GtkWidget *button, gpointer data)
{
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry_username));
    const gchar *self = gtk_entry_get_text(GTK_ENTRY(entry_sign));
    const gchar *mail = gtk_entry_get_text(GTK_ENTRY(entry_mail));
    g_print("用户名是：%s ", username);
    g_print("\n");
    g_print("签名是：%s ", self);
    g_print("\n");
    g_print("邮箱是：%s ", mail);
    g_print("\n");
    g_print("性别是：%s ", sex);
    g_print("\n");
}

/**************************************************/
/*名称：on_check_sex
/*描述：获取用户的性别信息，并更改sex值
/*作成日期： 2019/9/1
/*参数：
        参数1：radio、GtkWidget*、输入参数、男/女选项按钮
        参数2：data、gpointer、输入参数、传入的参数：男为1女为2
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
//获得性别
inline void on_check_sex(GtkWidget *radio, gpointer data)
{
    switch (GPOINTER_TO_INT(data))
    {
    case 1:
        sex = "男";
        break;
    case 2:
        sex = "女";
        break;
    }
}

/**************************************************/
/*名称：create_button
/*描述：创建头像按钮
/*作成日期：2019/9/1 
/*参数：无
/*返回值：返回值名称：button、类型：GtkWidget*、含有头像的按钮
/*作者：卢虹羽
/***************************************************/
inline GtkWidget *create_button(void)
{
    GtkWidget *image;
    GtkWidget *button;

    image = gtk_image_new_from_file("../source/icon/apple-red.jpg"); //这里的图片是系统初始图片
    button = gtk_button_new();
    gtk_widget_set_size_request(button, 100, 100);
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_widget_show(image);
    return button;
} 
/**************************************************/
/*名称：on_file_select_ok
/*描述：从本地选择图片上传
/*作成日期：未完成
/*参数：
        参数1：button、GtkWidget*、输入参数、对应意义按钮
        参数2：fs、GtkFileSelection*、输入参数、需要选择的文件名
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
// void on_file_select_ok (GtkWidget *button,GtkFileSelection *fs)
// {
//     GtkWidget *dialog;
//     gchar message[1024];
//     const gchar *filename;
//     filename = gtk_file_selection_get_filename(fs);
//     if(g_file_test(filename,G_FILE_TEST_IS_DIR))
//     sprintf(message,"你选择的目录是：%s",filename);
//     else
//     sprintf(message,"你选择的文件是：%s",filename);
//     dialog = gtk_message_dialog_new(NULL,
//     GTK_DIALOG_DESTROY_WITH_PARENT,
//     GTK_MESSAGE_INFO,
//     GTK_BUTTONS_OK,
//     message,
//     NULL);
//     gtk_widget_destroy(GTK_WIDGET(fs));
//     gtk_dialog_run(GTK_DIALOG(dialog));
//     gtk_widget_destroy(dialog);
//     g_print("你选择的文件是：%s",filename);
// }

/**************************************************/
/*名称：on_click_image
/*描述：点击图片按钮选择图片函数（调用on_file_select_ok）
/*作成日期：未完成 
/*参数：
        参数1：button、GtkWidget*、输入参数、头像按钮
        参数2：userdata、gpointer、输入参数、传入参数（空）
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
// void on_click_image(GtkWidget *button,gpointer userdata)
// {
//     GtkWidget* dialog ;
//     dialog = gtk_file_selection_new("请选择一个图片：");
//     gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
//     gtk_signal_connect(GTK_OBJECT(dialog),"destroy",
//     GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog);
//     gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button),"clicked",
//     GTK_SIGNAL_FUNC(on_file_select_ok),
//     GTK_FILE_SELECTION(dialog));
//     gtk_signal_connect_object(
//     GTK_OBJECT(GTK_FILE_SELECTION(dialog)->cancel_button),
//     "clicked",
//     GTK_SIGNAL_FUNC(gtk_widget_destroy),
//     GTK_OBJECT(dialog));
//     gtk_widget_show(dialog);
// }

/**************************************************/
/*名称：creat_myself_setting
/*描述：创建个人信息设置页面函数
/*作成日期：2019/9/1
/*参数：
    GtkWidget* button_ori 触发函数的button名 输入参数
	gpointer* data 需要传进来的参数（用户名什么的） 输入参数
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
void creat_myself_setting(GtkWidget *button_ori, gpointer *data)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *button2;
    GtkWidget *box3;
    GtkWidget *box4;
    GtkWidget *box5;
    GtkWidget *box6;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    GtkWidget *label6;
    GtkWidget *radio1;
    GtkWidget *radio2;
    GSList *group;
    GtkWidget *button;

    // gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "个人信息");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_size_request(window, 300, 500);
    change_background(window, 300, 500, "../source/skins/search_background.jpg");
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    box2 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 5);
    box1 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 5);
    box3 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box3, FALSE, FALSE, 5);
    box4 = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box4, FALSE, FALSE, 5);
    box5 = gtk_hbox_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), box5, FALSE, FALSE, 5);
    // box6 = gtk_hbox_new(FALSE,0);
    // gtk_box_pack_start(GTK_BOX(box),box6,FALSE,FALSE,5);

    label2 = gtk_label_new("头     像：");
    button2 = create_button();
    // g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(on_click_image),NULL);
    gtk_box_pack_start(GTK_BOX(box2), label2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box2), button2, FALSE, FALSE, 5);
    label1 = gtk_label_new("用户名：");
    entry_username = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1), label1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box1), entry_username, FALSE, FALSE, 5);
    label3 = gtk_label_new("签     名：");
    entry_sign = gtk_entry_new();
    // gtk_entry_set_visibility(GTK_ENTRY(entry3),FALSE);
    gtk_box_pack_start(GTK_BOX(box3), label3, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box3), entry_sign, FALSE, FALSE, 5);
    label4 = gtk_label_new("邮     箱：");
    entry_mail = gtk_entry_new();
    // gtk_entry_set_visibility(GTK_ENTRY(entry4),FALSE);
    gtk_box_pack_start(GTK_BOX(box4), label4, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box4), entry_mail, FALSE, FALSE, 5);
    label5 = gtk_label_new("性     别：");
    gtk_box_pack_start(GTK_BOX(box5), label5, FALSE, FALSE, 5);
    radio1 = gtk_radio_button_new_with_label(NULL, "男"); //男
    g_signal_connect(G_OBJECT(radio1), "released", G_CALLBACK(on_check_sex), (gpointer)1);
    gtk_box_pack_start(GTK_BOX(box5), radio1, FALSE, FALSE, 5);
    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1)); //多选按钮
    radio2 = gtk_radio_button_new_with_label(group, "女");        //女
    g_signal_connect(G_OBJECT(radio2), "released", G_CALLBACK(on_check_sex), (gpointer)2);
    gtk_box_pack_start(GTK_BOX(box5), radio2, FALSE, FALSE, 5);
    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio2)); //多选按钮
    // label6 = gtk_label_new("生     日：");
    // gtk_box_pack_start(GTK_BOX(box6),label6,FALSE,FALSE,5);

    button = gtk_button_new_with_label("确认");
    g_signal_connect(G_OBJECT(button), "clicked",
                     G_CALLBACK(on_sure_clicked), NULL);
    g_signal_connect_swapped(G_OBJECT(button), "clicked",
                             G_CALLBACK(gtk_widget_destroy), window);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 5);
    gtk_widget_show_all(window);
    // gtk_main();
    // return 0;
}