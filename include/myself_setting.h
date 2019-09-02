#ifndef __MYSELF_SETTING_H
#define __MYSELF_SETTING_H

#include <gtk/gtk.h>
#include <stdio.h>
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

void creat_myself_setting(GtkWidget *button_ori, gpointer *data);

#endif