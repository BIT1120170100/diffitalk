#ifndef __LIST_H
#define __LIST_H

#include<gtk/gtk.h>
#include<stdio.h>
#include"data.h"

GtkWidget* update_grouplist(int oldnum,int num,Group* info,GtkWidget* scrolled_window);
void on_click_group(GtkWidget* widget,GtkWidget* scrolled_window);
int get_group_num();
Group* get_group_info();

GtkWidget* update_friendlist(int oldnum,int num,User* info,GtkWidget* scrolled_window);
void on_click_friend(GtkWidget* widget,GtkWidget* scrolled_window);
int get_friend_num();
MyUser* get_friend_info();


#endif