#makefile
main: main.o chatWindow.o  messList.o
	gcc -o main main.o chatWindow.o  messList.o `pkg-config gtk+-2.0 --cflags --libs`
main.o: main.cpp
	gcc -c main.cpp `pkg-config gtk+-2.0 --cflags --libs`
chatWindow.o: chatWindow.cpp
	gcc  -c chatWindow.cpp  `pkg-config gtk+-2.0 --cflags --libs`
messList.o: lib/help/messList.cpp
	gcc  -c lib/help/messList.cpp  `pkg-config gtk+-2.0 --cflags --libs`
#删除所有.o文件
clean:
	rm *.o