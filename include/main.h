#ifndef MAIN_H
#define MAIN_H
#include<stdio.h>
#include<strings.h>
#include<gtk/gtk.h>


//========================= 群列表宏定义 ===============================
#define CREATE_GROUPLIST num_group,talk_to_group,group_ID,focus_group,lastfocus,args_for_callback_grouplist,attribute_group,groupdata,group_box,label_grouplist
#define UPDATE_GROUPLIST args_for_callback_grouplist,attribute_group,groupdata,num_group,lastfocus,talk_to_group,focus_group,group_page,group_box,label_grouplist
//========================= 好友宏定义 =================================
#define CREATE_FRIENDLIST num_friend,talk_to_user,friend_ID,focus_user,lastfocus_friend,args_for_callback_friendlist,attribute_friend,userdata,friend_box,label_friendlist
#define UPDATE_FRIENDLIST args_for_callback_friendlist,attribute_friend,userdata,num_friend,lastfocus_friend,talk_to_user,focus_user,friend_page,friend_box,label_friendlist

/*
static GdkColor white= {0,0xffff,0xffff,0xffff};
static GdkColor focus={0,0xf4f4,0xa4a4,0x6060};
static GdkColor skyblue={0,0x8787,0xcece,0xebeb};
static GdkColor red={0,0xffff,0,0};
static GdkColor Blue = {0,0x2121,0x9696,0xf3f3};
static GdkColor AliceBlue = {0,0xf0f0,0xf8f8,0xffff};
*/

#endif