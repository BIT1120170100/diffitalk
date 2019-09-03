#ifndef __CHECK_H
#define __CHECK_H

#include<gtk/gtk.h>
#include<stdio.h>
#include<strings.h>
#include "data.h"
//#include"main.h"


int loginAndRigistCheck(int userid,char *password,Kind kind, char  *c_ipAddr);

int parse_packet(Packet packet,Kind *kind,Data *data);

int build_packet(Packet *packet,Kind kind,...);
#endif