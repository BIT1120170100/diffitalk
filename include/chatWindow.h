#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include <gdk/gdkkeysyms.h>

//这里写函数声明
void createChatWindow( int argv,char *args[]);
void change_background(GtkWidget *widget, int w, int h, const gchar *path);
//char *ip, char *name, char *msg, char *sig, int img_code, int avatar_code
#endif