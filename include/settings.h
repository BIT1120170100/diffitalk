#ifndef __SETTINGS_H
#define __SETTINGS_H
#include<gtk/gtk.h>
//#include"main.h"
GtkWidget* create_settings();
void on_settings_close(GtkWidget* button,GtkWidget* data);
void settings(GtkWidget* button,gpointer data);
#endif