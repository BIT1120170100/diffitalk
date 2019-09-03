#ifndef __REGIST_H
#define __REGIST_H

#include <gtk/gtk.h>
#include<string.h>
#include<stdio.h>
//#include"main.h"
typedef struct regist_info{
    GtkWidget *user_id;
    GtkWidget *password;
    GtkWidget *rpassword;
    GtkWidget *email;
}regist_info;
void on_register_clicked(GtkWidget* button,regist_info* data);
GtkWidget* create_regist();

#endif