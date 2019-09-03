#SRCS= ./src
#SRCS=$(wildcard ${SRC}/*.cpp)$(wildcard ${SRC}/process/*.cpp)
SRCS=  ./scr/main.cpp   ./scr/process/check.cpp   ./scr/login.cpp scr/main_window.cpp \
	./scr/regist.cpp ./scr/process/reset.cpp  ./scr/settings.cpp \
	./scr/search.cpp ./scr/myself_setting.cpp \
	./scr/chatWindow.cpp   ./scr/multiChatWindow.cpp  ./scr/process/messList.cpp   ./scr/myInfo.cpp
main : $(SRCS)\
    gcc -o bin/main $(src) -lpthread -lm -ldl -w `pkg-config --cflags --libs gtk+-2.0`

#CC=g++
#PROG_NAME=main
#INC=./include
#INCS=$(wildcard ${INC}/*.h)
#INCS=include/main.h include/check.h  include/login.h include/main_window.h \
	include/regist.h include/reset.h include/settings.h \
	include/search.h include/myself_setting.h \
	include/chatWindow.h  include/messList.h  include/myInfo.h
#SRC = ./src
#SRCS=(wildcard ${SRC}/*.cpp)$(wildcard ${SRC}/process/*.cpp)
#SRCS=  scr/main.cpp   scr/process/check.cpp   scr/login.cpp scr/main_window.cpp \
	scr/regist.cpp scr/process/reset.cpp  scr/settings.cpp \
	scr/search.cpp scr/myself_setting.cpp \
	scr/chatWindow.cpp   scr/multiChatWindow.cpp  scr/process/messList.cpp   scr/myInfo.cpp

#从xx.cpp 文件得到 xx.o 文件
#OBJ = ./bin
#OBJS=${wildcard ${OBJ}/*.o}
#OBJS=/bin/main.o bin/check.o  bin/login.o bin/main_window.o \
	bin/regist.o bin/reset.o bin/settings.o \
	bin/search.o bin/myself_setting.o \
	bin/chatWindow.o  bin/multiChatWindow.o  bin/messList.o  bin/myInfo.o


#编译GTK程序时要用到的库
#LIBS=gtk+-2.0
#---- 用户修改区域 结束 
    #CFLAGS=`pkg-config --cflags ${LIBS}`  -g  -o -W
   # LDFLAGS=`pkg-config --libs ${LIBS}` -g  -o -W
#
#all: ${PROG_NAME}
#
 #   ${PROG_NAME}:${OBJS}
#	${CC} -g -o ${PROG_NAME} ${OBJS} ${LDFLAGS}
#  #注意：上边”${CC}" 的前边有一个TAB键，而不是空格

#如果有头文件进行修改，则自动编译源文件
#${OBJS}:${INCS}

#.cpp.o:
#	${CC} -c $< ${CFLAGS}

#clean:
	#rm -f *.o ${PROG_NAME}

#rebuild:
#	clean all