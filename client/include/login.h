#ifndef __LOGIN_H
#define __LOGIN_H
#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>
//#include"main.h"
typedef struct login_info{
    GtkWidget *user_id;
    GtkWidget *password;
}login_info;
void doLogin();
void on_login_clicked(GtkWidget* button,login_info* data);
void login_to_regist_clicked(GtkWidget* button,gpointer data);
void login_to_reset_clicked(GtkWidget* button,gpointer data);
GtkWidget* create_login();

#endif