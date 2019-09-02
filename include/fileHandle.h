#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <cstdio>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/types.h> // socket
#include <gtk/gtk.h>

#define FILE_PATH_SIZE 80
#define SERVER_PORT 7000
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
#define LENGTH_OF_LISTEN_QUEUE 20

//这里写函数声明
void *fileSend(file_pthread_t *file_info);
void destroy_confirm(GtkWidget *a, gpointer data);
void destroy_confirm_win(GtkWidget *a, GtkWidget *window);
void createFileConfirmWindow(char *file_name);
void fileRecv(struct sockaddr_in client, char *fileName);


#endif

 
