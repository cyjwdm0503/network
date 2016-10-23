
CC = g++
CFLAG = -Wall -g 


allObj=Channel.o ServiceName.o InetSock.o TcpSock.o Log.o
all:Channel.o ServiceName.o InetSock.o TcpSock.o Log.o client



client:client.cpp TcpSock.h TcpSock.h InetSock.h ServiceName.h socks.h
	$(CC) $(CFLAG) $^  $(allObj)  -o $@

server:server.cpp TcpSock.h $(all)
	$(CC) $(CFLAG) $(all) -o $@

Channel.o:Channel.cpp Channel.h socks.h
	$(CC) $(CFLAG)  -c $< -o $@

Log.o:Log.cpp Log.h
	$(CC) $(CFLAG) -c $< -o $@

ServiceName.o:ServiceName.cpp ServiceName.h socks.h
	$(CC) $(CFLAG) -c $< -o $@

InetSock.o:InetSock.cpp InetSock.h ServiceName.o
	$(CC) $(CFLAG) -c $< -o $@
TcpSock.o:TcpSock.cpp TcpSock.h ServiceName.o InetSock.o
	$(CC) $(CFLAG) -c $< -o $@

clean:$(all)
	rm -rf *.o client
