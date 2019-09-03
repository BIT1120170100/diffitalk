#include "../../include/errorMess.h"
#include <gtk/gtk.h>
#include <stdio.h>
void showDialog(char *mess)
{
        GtkWidget *dialog;
        //初始化GTK环境
        // gtk_init(&argc, &argv);
        dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK, mess, mess);
        gtk_window_set_title(GTK_WINDOW(dialog), "系统提示");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        //绑定信号函数,点击退出时执行的操作
        //g_signal_connect(GTK_OBJECT(dialog), "destroy", GTK_SIGNAL_FUNC(close_app), NULL);
        //gtk_widget_show_all(dialog);
        //gtk_main();
        return;
}
