#include "../include/regist.h"
#include"../include/check.h"
#include "../include/data.h"
#include "../include/errorMess.h"
/**************************************************/

/*名称：search.c

/*描述：实现查询功能

/*作成日期： 2019/9/1

/*参数：VOID

/*返回值：VOID

/*作者：卢虹羽

/***************************************************/

#include <gtk/gtk.h>

static GtkWidget *entry;

static GtkWidget *text_view;

static GtkTextBuffer *buffer;

/**************************************************/

/*名称：change_background

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

inline void change_background(GtkWidget *widget, int w, int h, const gchar *path)

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

    // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASL

    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);

    g_object_unref(src);

    g_object_unref(dst);

    g_object_unref(pixmap);
}

/**************************************************/

/*名称：create_button

/*描述：创建搜索按钮

/*作成日期：2019/9/1 

/*参数：无

/*返回值：返回值名称：button、类型：GtkWidget*、含义：搜索按钮

/*作者：卢虹羽

/***************************************************/

GtkWidget *create_button(void)

{

    GtkWidget *image;

    GtkWidget *button;

    // image = gtk_image_new_from_file("apple-red.png"); //这里是搜索图片

    // button = gtk_button_new();

    // gtk_widget_set_size_request(button, 10, 10);

    // gtk_container_add(GTK_CONTAINER(button), image);

    // gtk_widget_show(image);

    button = gtk_button_new_with_label("搜索");

    return button;
}

/**************************************************/

/*名称：on_click_add

/*描述：点击按钮，添加好友/群组

/*作成日期：未完成 

/*参数：

        参数1：button、GtkWidget*、输入参数、搜索按钮

        参数2：userdata、gpointer、输入参数、传入参数

/*返回值：VOID

/*作者：卢虹羽

/***************************************************/

void on_click_add(GtkWidget *button, gpointer  *data)
{ 
    const char *userid = gtk_entry_get_text(GTK_ENTRY(data));
    char id[10];
    strcpy(id, userid);
    if (addFriend(id, str_ip))
    { 
        //成功后更新列表
        listUpdate(currentUser.user_id);
        printf("创建成功");
    }
    else
    {
        showDialog("创建失败"); //
    }
    //某种数据库中的操作
}

/**************************************************/

/*名称：creat_search

/*描述：创建查找界面函数

/*作成日期：2019/9/1

/*参数：

    GtkWidget* button_ori 触发函数的button名 输入参数

	gpointer* data 需要传进来的参数（用户名什么的） 输入参数

/*返回值：VOID

/*作者：卢虹羽

/***************************************************/

void create_search(GtkWidget *button_ori, gpointer *data)
{

    GtkWidget *window;

    GtkWidget *hbox;

    GtkWidget *vbox;

    GtkWidget *image;

    GtkWidget *label;

    GtkWidget *button_search; //搜索的按钮

    GtkWidget *button_add; //添加的按钮

    //init

    // gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_signal_connect_object(GTK_OBJECT(window), "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), GTK_OBJECT(window));

    gtk_window_set_title(GTK_WINDOW(window), "添加好友");

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_widget_set_size_request(window, 300, 100);

    change_background(window, 300, 200, "../source/skins/search_background.jpg");

    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    //第一层整体纵向排布

    vbox = gtk_vbox_new(FALSE, 3);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    //第二层-1-搜索栏hbox

    hbox = gtk_hbox_new(FALSE, 3);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new("请输入好友id:");

    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 3);

    entry = gtk_entry_new();

    gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 3);

    // button_search = gtk_button_new_with_label("search"); //

    // gtk_widget_set_size_request(button_search, 50, 50);

    // change_background(button_search, 50, 50, "../source/icon/button_search.jpg");

    // g_signal_connect(G_OBJECT(button_search), "clicked", G_CALLBACK(on_click_search), NULL);

    // gtk_box_pack_start(GTK_BOX(hbox), button_search, FALSE, FALSE, 2);

    //第二层-2-信息显示

    // text_view = gtk_text_view_new();

    // buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 5);

    //第二层-3-添加按钮

    button_add = gtk_button_new_with_label("添加");

    g_signal_connect(G_OBJECT(button_add), "clicked", G_CALLBACK(on_click_add), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), button_add, FALSE, FALSE, 5);

    //show

    gtk_widget_show_all(window);

    // gtk_main();

    // return 0;
}