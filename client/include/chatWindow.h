#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include <gdk/gdkkeysyms.h>

//这里写函数声明
void createChatWindow(GtkWidget *button_ori, gpointer *data);
void createMultiChatWindow(GtkWidget *button_ori, gpointer *data);
void change_background(GtkWidget *widget, int w, int h, const gchar *path);
void change_background_(GtkWidget *widget, int w, int h, const gchar *path);
//char *ip, char *name, char *msg, char *sig, int img_code, int avatar_code
#endif