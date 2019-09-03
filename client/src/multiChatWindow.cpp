#include "../include/chatWindow.h"
#include "../include/messList.h"
/**************************************************/
/*名称：multiChatWindow
/*描述：群组聊天
/*作成日期：  
/*参数： 
/*返回值： 
/*作者： 卢虹羽
/***************************************************/

/**************************************************/
/*名称：change_background_
/*描述：设置背景图
/*作成日期：2019/9/1
/*参数：
    GtkWidget*  widget  设置背景图的窗口
    int w  图片宽度
    int h 图片高度
    gchar* path 图片路径
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
void change_background_(GtkWidget *widget, int w, int h, const gchar *path)
{
    //1.允许窗口可以绘图
    gtk_widget_set_app_paintable(widget, TRUE);
    gtk_widget_realize(widget);

    /* 更改背景图时，图片会重叠 
	* 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。 
	*/
    gtk_widget_queue_draw(widget);
    GdkPixbuf *src = gdk_pixbuf_new_from_file(path, NULL);
    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, w, h, GDK_INTERP_BILINEAR);

    /* 创建pixmap图像;  
	* NULL：不需要蒙版;  
	* 123： 0~255，透明到不透明 
	*/
    GdkPixmap *pixmap = NULL;
    gdk_pixbuf_render_pixmap_and_mask(dst, &pixmap, NULL, 100);

    // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE
    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);

    g_object_unref(src);
    g_object_unref(dst);
    g_object_unref(pixmap);
}

/**************************************************/
/*名称：create_button_expression
/*描述：创建发送表情按钮
/*作成日期：2019/9/1 
/*参数：VOID
/*返回值：名称：button；类型：GtkWidget*；含义：发送表情按钮
/*作者：卢虹羽
/***************************************************/
GtkWidget *create_button_expression_(void) //expression
{
    GtkWidget *image;
    GtkWidget *button;

    image = gtk_image_new_from_file("source/icon/apple-red.jpg"); //
    button = gtk_button_new();
    gtk_widget_set_size_request(button, 30, 30);
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_widget_show(image);
    return button;
}

/**************************************************/
/*名称：create_button_image
/*描述：创建发图片按钮
/*作成日期：2019/9/1 
/*参数：VOID
/*返回值：名称：button；类型：GtkWidget*；含义：发送图片按钮
/*作者：卢虹羽
/***************************************************/
GtkWidget *create_button_image_(void) //image
{
    GtkWidget *image;
    GtkWidget *button;

    image = gtk_image_new_from_file("source/icon/apple-red.jpg"); //
    button = gtk_button_new();
    gtk_widget_set_size_request(button, 30, 30);
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_widget_show(image);
    return button;
}

/**************************************************/
/*名称：create_button_file
/*描述：创建发送文件按钮
/*作成日期：2019/9/1 
/*参数：VOID
/*返回值：名称：button；类型：GtkWidget*；含义：发送文件按钮
/*作者：卢虹羽
/***************************************************/
GtkWidget *create_button_file_(void) //files
{
    GtkWidget *image;
    GtkWidget *button;

    image = gtk_image_new_from_file("source/icon/apple-red.jpg"); //
    button = gtk_button_new();
    gtk_widget_set_size_request(button, 30, 30);
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_widget_show(image);
    return button;
}

/**************************************************/
/*名称：create_history
/*描述：创建查看历史消息按钮
/*作成日期：2019/9/1 
/*参数：VOID
/*返回值：名称：button；类型：GtkWidget*；含义：查看历史消息按钮
/*作者：卢虹羽
/***************************************************/
GtkWidget *create_button_history_(void) //history
{
    GtkWidget *image;
    GtkWidget *button;

    image = gtk_image_new_from_file("source/icon/apple-red.jpg"); //
    button = gtk_button_new();
    gtk_widget_set_size_request(button, 30, 30);
    gtk_container_add(GTK_CONTAINER(button), image);
    gtk_widget_show(image);
    return button;
}

/**************************************************/
/*名称：button_send_expression
/*描述：选择表情并发送表情
/*作成日期：未完成
/*参数：VOID
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
static void button_send_expression_(GtkWidget *button, gpointer data)
{
}

/**************************************************/
/*名称：button_send_image
/*描述：选择图片并发送图片
/*作成日期：未完成 
/*参数：VOID
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
static void button_send_image_(GtkWidget *button, gpointer userdata)
{
}

/**************************************************/
/*名称：on_file_select_ok
/*描述：在本机选择文件
/*作成日期：2019/8/31
/*参数：VOID
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
void on_file_select_ok_(GtkWidget *button, GtkFileSelection *fs)
{
    GtkWidget *dialog;
    gchar message[1024];
    const gchar *filename;
    filename = gtk_file_selection_get_filename(fs);
    if (g_file_test(filename, G_FILE_TEST_IS_DIR))
        sprintf(message, "你选择的目录是：%s", filename);
    else
        sprintf(message, "你选择的文件是：%s", filename);
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    message,
                                    NULL);
    gtk_widget_destroy(GTK_WIDGET(fs));
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    g_print("你选择的文件是：%s", filename);
}

/**************************************************/
/*名称：button_send_file
/*描述：弹出文件窗口并发送文件
/*作成日期：未完成
/*参数：VOID
/*返回值：VOID
/*作者：卢虹羽
/***************************************************/
void button_send_file_(GtkWidget *button, gpointer userdata)
{
    GtkWidget *dialog;
    dialog = gtk_file_selection_new("请选择一个文件或目录：");
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                       GTK_SIGNAL_FUNC(gtk_widget_destroy), &dialog);
    gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(dialog)->ok_button), "clicked",
                       GTK_SIGNAL_FUNC(on_file_select_ok_),
                       GTK_FILE_SELECTION(dialog));
    gtk_signal_connect_object(
        GTK_OBJECT(GTK_FILE_SELECTION(dialog)->cancel_button),
        "clicked",
        GTK_SIGNAL_FUNC(gtk_widget_destroy),
        GTK_OBJECT(dialog));
    gtk_widget_show(dialog);
}

/**************************************************/
/*名称：button_send_history
/*描述：弹出历史记录窗口
/*作成日期：未完成
/*参数：VOID
/*返回值：VOID
/*作者：卢虹羽cl
/***************************************************/
void button_send_history_(GtkWidget *button, gpointer userdata)
{
}

/**************************************************/
/*名称：createMultiChatWindow
/*描述：群组聊天界面主函数
/*作成日期：2019/8/31
/*参数：
    int argc 参数个数 输入参数
	char* argv[] 参数列表 输入参数
/*返回值：int 0,表示函数退出成功
/*作者：卢虹羽
/***************************************************/
//char *ip, char *name, char *msg, char *sig, int img_code, int avatar_code
//void creat_single_chat
void createMultiChatWindow(GtkWidget *button_ori, gpointer *data)
{
    GtkWidget *window;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *scrolled_window;

    GtkWidget *image;
    GtkWidget *button_expression; //expression
    GtkWidget *button_image;      //image
    GtkWidget *button_file;       //file
    GtkWidget *button_history;    //history
    GtkWidget *box;

    GtkWidget *button;
    GtkWidget *text_view;
    GtkTextBuffer *buffer;
    GtkTextIter *Iter; //no use

    //init
    // gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "单人聊天界面");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_size_request(window, 600, 500);
    //设置窗口图片
    change_background_(window, 600, 500, "../skins/chat_background.jpg");

    //first
    hbox = gtk_hbox_new(FALSE, 3);
    vbox = gtk_vbox_new(FALSE, 3);
    gtk_widget_set_size_request(vbox, 400, 400);
    gtk_container_add(GTK_CONTAINER(window), hbox);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 0);

    //second-left
    //second-left-1-information
    scrolled_window = create_list();
    gtk_widget_set_size_request(scrolled_window, 400, 250);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    //second-left-2-function
    box = gtk_hbox_new(FALSE, 0);
    gtk_widget_set_size_request(box, 400, 30);
    button_expression = create_button_expression_();
    gtk_box_pack_start(GTK_BOX(box), button_expression, FALSE, FALSE, 3);
    g_signal_connect(G_OBJECT(button_expression), "clicked", G_CALLBACK(button_send_expression_), NULL);
    button_image = create_button_image_();
    gtk_box_pack_start(GTK_BOX(box), button_image, FALSE, FALSE, 3);
    g_signal_connect(G_OBJECT(button_image), "clicked", G_CALLBACK(button_send_image_), NULL);
    button_file = create_button_file_();
    gtk_box_pack_start(GTK_BOX(box), button_file, FALSE, FALSE, 3);
    g_signal_connect(G_OBJECT(button_file), "clicked", G_CALLBACK(button_send_file_), NULL);
    button_history = create_button_history_();
    gtk_box_pack_start(GTK_BOX(box), button_history, FALSE, FALSE, 3);
    g_signal_connect(G_OBJECT(button_history), "clicked", G_CALLBACK(button_send_history_), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), box, FALSE, FALSE, 0);

    //second-left-3-edit
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    button = gtk_button_new_with_label("submit");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 3);

    //second-right
    vbox = gtk_vbox_new(FALSE, 3);
    gtk_widget_set_size_request(vbox, 200, 400);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 3);
    //second-right-1-another
    frame = gtk_frame_new("Normal Label");
    label = gtk_label_new("This should be the imformation of anotherone");
    gtk_container_add(GTK_CONTAINER(frame), label);
    gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 1);
    //second-right-2-mine
    // frame = gtk_frame_new("Normal Label");
    // label = gtk_label_new("This should be your imformation");
    // gtk_container_add(GTK_CONTAINER(frame), label);
    // gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 1);
    scrolled_window = create_list();
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 1);

    //show
    gtk_widget_show_all(window);
    // gtk_main();
}