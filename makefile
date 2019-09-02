#makefile
main: main.o chatWindow.o
	g++ -o main main.o chatWindow.o `pkg-config gtk+-2.0 --cflags --libs`
main.o: main.cpp
	gcc -c main.cpp `pkg-config gtk+-2.0 --cflags --libs`
chatWindow.o: chatWindow.cpp
	gcc  -c chatWindow.cpp  `pkg-config gtk+-2.0 --cflags --libs`