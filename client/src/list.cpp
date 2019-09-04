#include"../include/list.h"

//#include"get_listinfo.h"
#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<string>
using namespace std;
extern GtkWidget* scrolled_window;
//以下为测试数据
Group test1[10]={{1,"group1",{1,2,3}},{1,"groupa",{1,2,3}},{1,"groupg",{1,2,3}},{1,"groupa",{1,2,3}},{1,"groupv",{1,2,3}}};
MyUser test2[20]={
    {"sada","1234","111","111","111","111","1213",TRUE},
    {"sagsa","1214","111","111","111","111","1213",TRUE},
    {"sadsaa","1224","111","111","111","111","1213",TRUE},
    {"sadvxc","1234","111","111","111","111","1213",TRUE},
    {"sdasa","1244","111","111","111","111","1213",TRUE},
    {"sa1a","1254","111","111","111","111","1213",TRUE},
    {"sabfd","1264","111","111","111","111","1213",TRUE},
    {"sabbh","1234","111","111","111","111","1213",TRUE},
    {"sazc","1234","111","111","111","111","1213",TRUE}
};
char a[20]="group";
char* label[1005];

int get_group_num(){
    return 3;
}
int get_friend_num(){
    return 5;
}

Group* get_group_info(){
    return test1;
}
MyUser* get_friend_info(){
    return test2;
}
//测试数据部分结束
GtkWidget* groupbox[1005];
GtkWidget* groupname[1005];
GtkWidget* groupid[1005];
GtkWidget* groupboxsum;
GtkWidget* friendbox[1005];
GtkWidget* friendname[1005];
GtkWidget* friendid[1005];
GtkWidget* friendboxsum;

int numnow=0;
/**************************************************/
/*名称：destroy_widget
/*描述：删除构件
/*作成日期： 
/*参数：
         参数1：参数名称 *widget、参数类型 GtkWidget 、输入参数、参数含义 需操作的窗口
         参数2：参数名称 *a、参数类型 GtkWidget 、输入参数、参数含义	需删除的构件
/*返回值：gint
/*作者：刘梦涵
/***************************************************/
void destroy_widget(GtkWidget *widget,GtkWidget *a){		      //删除构件
	gtk_widget_destroy(a);
}

int strtoint(char *txt){
	int len = strlen(txt);
	int res = 0;
	if(len>=9) return -1;
	int i;
	for(i = 0;i < len;i++){
		if(txt[i]>'9'||txt[i]<'0'){
			res = -1;
			break;
		}
		res += txt[i] - '0';
		res *= 10;
	}
	return res;
}

void inttostr(char *txt,int a){
	int l = 0;
	char ch;
	while(a){
		txt[l++] = '0' + a%10;
		a /= 10;
	}
	txt[l] = 0;
	int i;
	for(i = 0;i < l/2;i++){
		ch = txt[i];
		txt[i] = txt[l - i - 1];
		txt[l-i-1] = ch;
	}
	if(l == 0){
		txt[0] = '0';
		txt[1] = 0;
	}
}
/**************************************************/
/*名称：cmp_group cmp_friend
/*描述：群组列表对比 好友列表对比
/*作成日期： 
/*参数：
         参数1：参数名称 *a、参数类型 const void 、输入参数
         参数2：参数名称 *b、参数类型 const void 、输入参数
/*返回值：int
/*作者：刘梦涵
/***************************************************/
int cmp_group(const void * a,const void * b){
    Group *c = (Group *)a;
	Group *d = (Group *)b;
	return c->owner_id-d->owner_id;
}

int cmp_friend(const void* a,const void* b){
    MyUser* c = (MyUser* )a;
	MyUser* d = (MyUser* )b;
    if(c->user_online!=d->user_online){
        if(c->user_online)
		return 1;
		else
		return -1;
    }
    else{
        return c->user_id - d->user_id;
    }
}
/**************************************************/
/*名称：update_grouplist
/*描述：刷新群组信息
/*作成日期： 
/*参数：
         参数1：参数名称 oldnum、参数类型 int 、输入参数
         参数2：参数名称 num、参数类型 int 、输入参数
		参数3：参数名称 info、参数类型 Group*、输入参数
		参数4：参数名称 scrolled_window、参数类型 GtWidget* 、输入参数
/*返回值：GtkWidget*
/*作者：刘梦涵
/***************************************************/
GtkWidget* update_grouplist(int oldnum,int num,Group* info,GtkWidget* scrolled_window) {
	
    if(groupboxsum!=NULL){
		for(int i=1;i<=(oldnum);i++){
			gtk_widget_destroy(groupid[i]);
            gtk_widget_destroy(groupname[i]);
			gtk_widget_destroy(groupbox[i]);
		}
		gtk_widget_destroy(groupboxsum);
	
	}
	if(friendboxsum!=NULL){
		for(int i=1;i<=(oldnum);i++){
			gtk_widget_destroy(friendid[i]);
			gtk_widget_destroy(friendbox[i]);
            gtk_widget_destroy(friendname[i]);
		}
		gtk_widget_destroy(friendboxsum);
	}
	if(label[1]==NULL){
		for(int i=1;i<1005;i++)
		label[i]=(char*)malloc(STRING_LEN*sizeof(char));//
	}
	
	//qsort(info,(num),sizeof(Group),cmp_group);
	groupboxsum=gtk_vbox_new(FALSE,0);
	for(int i=1;i<=(num);i++){
		groupbox[i]=gtk_hbox_new(FALSE,0);
		
		//label[i]=info[i].g_name;
		groupname[i]=gtk_button_new_with_label(info[i].g_name);
		//groupid[i]=gtk_label_new(info[i].g_id);
		gtk_box_pack_start(GTK_BOX(groupbox[i]),groupname[i],TRUE,TRUE,0);
        //gtk_box_pack_start(GTK_BOX(groupbox[i]),groupid[i],TRUE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(groupboxsum),groupbox[i],FALSE,FALSE,5);
		
	}
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),groupboxsum);
    return scrolled_window;
}
void on_click_group(GtkWidget* widget,GtkWidget* scrolled_window){
	//scrolled_window=gtk_scrolled_window_new(NULL,NULL);
	int num;
    num=get_group_num();
	g_print("%d\n",num);
	Group* groupinfo=get_group_info();
	int oldnum;
    oldnum=numnow;
	numnow=num;
	scrolled_window=update_grouplist(oldnum,num,groupinfo,scrolled_window);
	gtk_widget_show_all(scrolled_window);
}
/**************************************************/
/*名称：update_grouplist
/*描述：刷新好友信息
/*作成日期： 
/*参数：
         参数1：参数名称 oldnum、参数类型 int 、输入参数
         参数2：参数名称 num、参数类型 int 、输入参数
		参数3：参数名称 info、参数类型 User*、输入参数
		参数4：参数名称 scrolled_window、参数类型 GtWidget* 、输入参数
/*返回值：GtkWidget*
/*作者：刘梦涵
/***************************************************/
GtkWidget* update_friendlist(int oldnum,int num,MyUser* info,GtkWidget* scrolled_window) {
	if(friendboxsum!=NULL){
		for(int i=1;i<=(oldnum);i++){
			gtk_widget_destroy(friendid[i]);
            gtk_widget_destroy(friendname[i]);
			gtk_widget_destroy(friendbox[i]);
		}
		gtk_widget_destroy(friendboxsum);
	}
	if(groupboxsum!=NULL){
		for(int i=1;i<=(oldnum);i++){
			gtk_widget_destroy(groupid[i]);
			gtk_widget_destroy(groupbox[i]);
            gtk_widget_destroy(groupname[i]);
		}
		gtk_widget_destroy(groupboxsum);
	
	}
	if(label[1]==NULL){
		for(int i=1;i<1005;i++)
		label[i]=(char*)malloc(STRING_LEN*sizeof(char));//
	}

	//qsort(info,(num),sizeof(User),cmp_friend);
	friendboxsum=gtk_vbox_new(FALSE,0);
	for(int i=1;i<=(num);i++){
		friendbox[i]=gtk_hbox_new(TRUE,0);
		label[i]=info[i].user_name;
		
		friendname[i]=gtk_label_new(info[i].user_name);
        friendid[i]=gtk_button_new_with_label(info[i].user_id);
		//groupid[i]=gtk_button_new_with_label("group");
		gtk_box_pack_start(GTK_BOX(friendbox[i]),friendid[i],TRUE,TRUE,0);
        gtk_box_pack_start(GTK_BOX(friendbox[i]),friendname[i],TRUE,TRUE,0);
		gtk_box_pack_start(GTK_BOX(friendboxsum),friendbox[i],FALSE,FALSE,5);
	}

	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),friendboxsum);
    return scrolled_window;

}

void on_click_friend(GtkWidget* widget,GtkWidget* scrolled_window){

	//scrolled_window=gtk_scrolled_window_new(NULL,NULL);
	int num;
    num=get_friend_num();
	g_print("%d\n",num);
	MyUser* friendinfo=get_friend_info();
	int oldnum;
    oldnum=numnow;
	numnow=num;
	scrolled_window=update_friendlist(oldnum,num,friendinfo,scrolled_window);
	gtk_widget_show_all(scrolled_window);
}