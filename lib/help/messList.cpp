
# include "../../include/messList.h"

/* 创建一个"信息"列表 */
GtkWidget *create_list(void)
{
        GtkWidget *scrolled_window;
        GtkWidget *tree_view;
        GtkListStore *model;
        GtkTreeIter iter;
        GtkCellRenderer *cell;
        GtkTreeViewColumn *column;
        int i;
        /* 创建一个新的滚动窗口(scrolled window)，只有需要时，滚动条才出现 */
        scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                       GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_AUTOMATIC);
        model = gtk_list_store_new(1, G_TYPE_STRING);
        tree_view = gtk_tree_view_new();
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),
                                              tree_view);
        gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(model));
        gtk_widget_show(tree_view);
        /* 在窗口中添加一些消息 */
        for (i = 0; i < 10; i++)
        {
                gchar *msg = g_strdup_printf("Message #%d", i);
                gtk_list_store_append(GTK_LIST_STORE(model), &iter);
                gtk_list_store_set(GTK_LIST_STORE(model),
                                   &iter,
                                   0, msg,
                                   1);
                g_free(msg);
        }
        cell = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Messages",
                                                          cell,
                                                          "text", 0,
                                                          NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    GTK_TREE_VIEW_COLUMN(column));
        return scrolled_window;
}