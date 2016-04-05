
CC = g++
CFLAG = -Wall

all:Channel.o ServiceName.o InetSock.o

Channel.o:Channel.cpp Channel.h socks.h
	$(CC) $(CFLAG)  -c $< -o $@


ServiceName.o:ServiceName.cpp ServiceName.h socks.h
	$(CC) $(CFLAG) -c $< -o $@

InetSock.o:InetSock.cpp InetSock.h ServiceName.o
	$(CC) $(CFLAG) -c $< -o $@
