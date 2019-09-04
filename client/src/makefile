CC=gcc
PROG_NAME=main
INCS=../include/main.h  ./json/cJSON.h  ./util/util.h ../include/check.h  ../include/login.h  ../include/main_window.h \
	../include/regist.h ../include/reset.h ../include/settings.h ../include/errorMess.h\
	../include/search.h   ../include/myself_setting.h \
	../include/chatWindow.h  ../include/messList.h  ../include/myInfo.h\
	../include/group.h ../include/list.h
	
SRCS=main.cpp  ./json/cJson.c   ./util/util.c  ./process/check.cpp  login.cpp main_window.cpp \
	regist.cpp ./process/reset.cpp settings.cpp \
	search.cpp myself_setting.cpp ./process/errorMess.cpp\
	chatWindow.cpp  multiChatWindow.cpp ./process/messList.cpp  myInfo.cpp\
	group.cpp list.cpp
	 
#从xx.cpp 文件得到 xx.o 文件
OBJS=${SRCS:.cpp=.o}
OBJS2=main.o check.o  login.o group.o main_window.o list.o\
	regist.o reset.o settings.o \
	search.o myself_setting.o \
	chatWindow.o  multiChatWindow.o  messList.o  myInfo.o\
	cJSON.o util.o  errorMess.o\

#编译GTK程序时要用到的库
LIBS=gtk+-2.0
#---- 用户修改区域 结束 
CFLAGS=`pkg-config --cflags ${LIBS}` -lm -g -W
LDFLAGS=`pkg-config --libs ${LIBS}` -lm -g -W
#
all: ${PROG_NAME}
#
${PROG_NAME}:${OBJS}
	${CC} -g -o ${PROG_NAME} ${OBJS2} ${LDFLAGS}
#  #注意：上边”${CC}" 的前边有一个TAB键，而不是空格

#如果有头文件进行修改，则自动编译源文件
${OBJS}:${INCS}

.cpp.o:
	${CC} -c $< ${CFLAGS}

clean:
	rm -f *.o ${PROG_NAME}

rebuild:
	clean all