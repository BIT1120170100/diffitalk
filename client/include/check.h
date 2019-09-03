#ifndef __CHECK_H
#define __CHECK_H
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

#include<gtk/gtk.h>
#include<stdio.h>
#include<strings.h>
#include "data.h"
//#include"main.h"


int loginAndRigistCheck(int userid,const char *password,Kind kind, char  *c_ipAddr);

int parse_packet(Packet packet,Kind *kind,Data *data);

int build_packet(Packet *packet,Kind kind,...);
#endif