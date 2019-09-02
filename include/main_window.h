#ifndef __MAIN_WINDOW_H
#define __MAIN_WINDOW_H
#include<gtk/gtk.h>
#include<stdio.h>
#include"main.h"
GtkWidget* create_main_window();
void on_click_close(GtkWidget* button,gpointer data);
void on_click_exit(GtkWidget* button,gpointer data);
void on_click_exit_cancel(GtkWidget* button,GtkWidget* data);
GtkWidget* create_exit();

#endif