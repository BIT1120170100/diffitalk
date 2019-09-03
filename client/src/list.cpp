#include"../include/list.h"

//#include"get_listinfo.h"
#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<string>
using namespace std;
extern GtkWidget* scrolled_window;
//以下为测试数据
Group* test1=(Group*)malloc(sizeof(Group)*1005);
User* test2=(User*)malloc(sizeof(User)*1005);
char a[20]="group";
char* label[1005];

int get_group_num(){
    return 10;
}
int get_friend_num(){
    return 20;
}
Group* get_group_info(){
    int n=get_group_num();
    for(int i=1;i<=n;i++){
	stpcpy(test1[i].g_name,a);
    }

	a[1]+=1;
    return test1;
}
User* get_friend_info(){
    int n=get_friend_num();
    for(int i=1;i<=n;i++){
	stpcpy(test2[i].user_name,a);
    }

	a[1]+=1;
    return test2;
}
//测试数据部分结束
GtkWidget* groupbox[1005];
GtkWidget* groupid[1005];
GtkWidget* groupboxsum;
GtkWidget* friendbox[1005];
GtkWidget* friendavatar[1005];
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
    User* c = (User* )a;
	User* d = (User* )b;
    if(c->user_online!=d->user_online){
        if(c->online)
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
			gtk_widget_destroy(groupbox[i]);
		}
		gtk_widget_destroy(groupboxsum);
	
	}
	if(friendboxsum!=NULL){
		for(int i=1;i<=(oldnum);i++){
			gtk_widget_destroy(friendid[i]);
			gtk_widget_destroy(friendbox[i]);
		}
		gtk_widget_destroy(friendboxsum);
	}
	if(label[1]==NULL){
		for(int i=1;i<1005;i++)
		label[i]=(char*)malloc(STRING_LEN*sizeof(char));//
	}
	
	qsort(info,(num),sizeof(Group),cmp_group);
	groupboxsum=gtk_vbox_new(FALSE,0);
	for(int i=1;i<=(num);i++){
		groupbox[i]=gtk_hbox_new(FALSE,0);
		
		label[i]=info[i].g_name;
		
		groupid[i]=gtk_button_new_with_label(label[i]);
		//groupid[i]=gtk_button_new_with_label("group");
		gtk_box_pack_start(GTK_BOX(groupbox[i]),groupid[i],TRUE,TRUE,0);
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
GtkWidget* update_friendlist(int oldnum,int num,User* info,GtkWidget* scrolled_window) {
	if(friendboxsum!=NULL){
		for(int i=1;i<=(oldnum);i++){
			gtk_widget_destroy(friendid[i]);
			gtk_widget_destroy(friendbox[i]);
		}
		gtk_widget_destroy(friendboxsum);
	}
	if(groupboxsum!=NULL){
		for(int i=1;i<=(oldnum);i++){
			gtk_widget_destroy(groupid[i]);
			gtk_widget_destroy(groupbox[i]);
		}
		gtk_widget_destroy(groupboxsum);
	
	}
	if(label[1]==NULL){
		for(int i=1;i<1005;i++)
		label[i]=(char*)malloc(STRING_LEN*sizeof(char));//
	}

	qsort(info,(num),sizeof(User),cmp_friend);
	friendboxsum=gtk_vbox_new(FALSE,0);
	for(int i=1;i<=(num);i++){
		friendbox[i]=gtk_hbox_new(FALSE,0);
		label[i]=info[i].user_name;
		
		friendid[i]=gtk_button_new_with_label(label[i]);
		//groupid[i]=gtk_button_new_with_label("group");
		gtk_box_pack_start(GTK_BOX(friendbox[i]),friendid[i],TRUE,TRUE,0);
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
	User* friendinfo=get_friend_info();
	int oldnum;
    oldnum=numnow;
	numnow=num;
	scrolled_window=update_friendlist(oldnum,num,friendinfo,scrolled_window);
	gtk_widget_show_all(scrolled_window);
}