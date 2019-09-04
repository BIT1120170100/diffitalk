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
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include "../src/util/util.h"
//#include "ui.h" 
#include <stdlib.h>   
#include <arpa/inet.h>
#include <pthread.h>

int loginAndRigistCheck(char *userid, char *password, Kind kind, char *c_ipAddr);

int build_packet(Kind kind, void *arg1, void *arg2);
 
#endif