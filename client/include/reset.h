#ifndef __RESET_H
#define __RESET_H
#include<gtk/gtk.h>
#include<string.h>
//#include"main.h"

typedef struct reset_info{
    GtkWidget *user_id;
    GtkWidget *email;
    GtkWidget *vcode;
    GtkWidget *new_password;
}reset_info;
void on_reset_clicked(GtkWidget* button,reset_info* data);
GtkWidget* create_reset();

#endif