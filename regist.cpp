
#include"include/regist.h"
#include"include/check.h"
//#include"main.h"
extern GtkWidget* main_window;
extern GtkWidget* login_window;
extern GtkWidget* regist_window;
extern GtkWidget* reset_window;
extern GtkWidget* settings_window;
extern GtkWidget* exit_window;
regist_info registinfo;
/**************************************************/
/*名称：on_register_clicked
/*描述：注册按钮的回调函数
/*作成日期： 
/*参数：
        参数1：button、GtkWidget* 、输入参数、注册按钮
        参数2：data、regist_info* 、输入参数、注册信息
/*返回值：VOID
/*作者：刘梦涵
/***************************************************/
void on_register_clicked(GtkWidget* button,regist_info* data){
    const char *username=gtk_entry_get_text(GTK_ENTRY(data->user_id));
    const char *password=gtk_entry_get_text(GTK_ENTRY(data->password));
    const char *rpassword=gtk_entry_get_text(GTK_ENTRY(data->rpassword));
    const char *email=gtk_entry_get_text(GTK_ENTRY(data->email));
    g_print("username:%s\n",username);
	g_print("password:%s\n",password);
    g_print("email:%s\n",email);
	g_print("rpassword:%s\n",rpassword);
    if(regist_check()){
        gtk_widget_hide_all(regist_window);
        gtk_widget_show_all(login_window);
    }
    else{
    }
}
/**************************************************/
/*名称：create_regist
/*描述：创建注册界面
/*作成日期： 
/*参数：VOID
/*返回值：GtkWidget*
/*作者：刘梦涵
/***************************************************/
GtkWidget* create_regist(){
    GtkWidget* window;
	GtkWidget* box;
	GtkWidget* box1;
	GtkWidget* box2;
    GtkWidget* box3;
    GtkWidget* box4;
	GtkWidget* label1;
	GtkWidget* label2;
    GtkWidget* label3;
    GtkWidget* label4;
    GtkWidget* entry1;
	GtkWidget* entry2;
    GtkWidget* entry3;
    GtkWidget* entry4;
	GtkWidget* regst;
	GtkWidget* sep;

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete_event",
			G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(window),"register");
	gtk_window_set_default_size(GTK_WINDOW(window),500,200);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window),20);

	box=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	box1=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,5);
	box2=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);
	box3=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,5);
    box4=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,5);
		
	label1=gtk_label_new("username:");
	entry1=gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);
	gtk_box_pack_end(GTK_BOX(box1),entry1,FALSE,FALSE,5);
	
	label2=gtk_label_new("password:");
    entry2=gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
    gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,5);
    gtk_box_pack_end(GTK_BOX(box2),entry2,FALSE,FALSE,5);

    label3=gtk_label_new("confirm password:");
    entry3=gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(entry3),FALSE);
    gtk_box_pack_start(GTK_BOX(box3),label3,FALSE,FALSE,5);
    gtk_box_pack_end(GTK_BOX(box3),entry3,FALSE,FALSE,5);

    label4=gtk_label_new("email:");
    entry4=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box4),label4,FALSE,FALSE,5);
    gtk_box_pack_end(GTK_BOX(box4),entry4,FALSE,FALSE,5);

    sep=gtk_hseparator_new();
        gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,5);

    
    registinfo.user_id=entry1;
    registinfo.password=entry2;
    registinfo.rpassword=entry3;
    registinfo.email=entry4;
	regst=gtk_button_new_with_label("register");
	g_signal_connect(G_OBJECT(regst),"clicked",
                    G_CALLBACK(on_register_clicked),&registinfo);
    gtk_box_pack_start(GTK_BOX(box),regst,FALSE,FALSE,5);
    return window;
}