#ifndef __SETTINGS_H
#define __SETTINGS_H
#include<gtk/gtk.h>
//#include"main.h"
GtkWidget* create_settings();
gint on_settings_close(GtkWidget* button,GtkWidget* data);
void settings(GtkWidget* button,GtkWidget* data);


static GdkColor white= {0,0xffff,0xffff,0xffff};
static GdkColor focus={0,0xf4f4,0xa4a4,0x6060};
static GdkColor skyblue={0,0x8787,0xcece,0xebeb};
static GdkColor red={0,0xffff,0,0};
static GdkColor blue = {0,0x2121,0x9696,0xf3f3};
static GdkColor aliceblue = {0,0xf0f0,0xf8f8,0xffff};
#endif