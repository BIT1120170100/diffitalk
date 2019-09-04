#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stdio.h>
#include <gtk/gtk.h>
#include"check.h"
#include "data.h"
#include "errorMess.h"
void create_search(GtkWidget *button_ori, gpointer *data);
void on_click_add(GtkWidget *button, gpointer *data);
#endif