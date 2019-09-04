CC=gcc
PROG_NAME=server
INCS=server.h ../include/data.h ./json/cJSON.h  ./util/util.h \
	../sql/database.h 
SRCS=server.cpp function.cpp  ./util/util.c \
	./json/cJSON.c ../sql/database.cpp

#从xx.cpp 文件得到 xx.o 文件
OBJS=${SRCS:.cpp=.o}
#OBJS=main.o check.o  login.o main_window.o \
	regist.o reset.o settings.o \
	search.o myself_setting.o \
	chatWindow.o  multiChatWindow.o  messList.o  myInfo.o

OBJS2=server.o function.o  util.o cJSON.o database.o 

#编译GTK程序时要用到的库
LIBS=gtk+-2.0 
#---- 用户修改区域 结束 
CFLAGS=`pkg-config --cflags ${LIBS}` -lpthread -lm -g -W
LDFLAGS=`pkg-config --libs ${LIBS}` -lpthread -lm -g -W
DATAFLAGS=`mysql_config --cflags --libs`
#
all: ${PROG_NAME}
#
${PROG_NAME}:${OBJS}
	${CC} -g -o ${PROG_NAME} ${OBJS2} ${LDFLAGS} ${DATAFLAGS}
#  #注意：上边”${CC}" 的前边有一个TAB键，而不是空格

#如果有头文件进行修改，则自动编译源文件
${OBJS}:${INCS}

.cpp.o:
	${CC} -c $< ${CFLAGS} ${DATAFLAGS}

clean:
	rm -f *.o ${PROG_NAME}

rebuild:
	clean all