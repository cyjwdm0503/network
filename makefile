
CC = g++
CFLAG = -Wall -g 


allObj=Channel.o ServiceName.o InetSock.o TcpSock.o Log.o ServerBase.o Server.o
all:Channel.o ServiceName.o InetSock.o TcpSock.o Log.o ServerBase.o Server.o
target: ClientEndPoint ServerEndPoint


ClientEndPoint:client.cpp TcpSock.h TcpSock.h InetSock.h ServiceName.h socks.h 
	$(CC) $(CFLAG) $^ $(allObj)    -o $@

ServerEndPoint:ServerEndPoint.cpp TcpSock.h TcpSock.h InetSock.h ServiceName.h socks.h 
	$(CC) $(CFLAG) $^ $(allObj)    -o $@

Server.o:Server.cpp TcpSock.h socks.h 
	$(CC) $(CFLAG) -c $< -o $@

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

ServerBase.o:ServerBase.cpp 
	$(CC) $(CFLAG) -c $< -o $@

clean:$(all)
	rm -rf *.o ClientEndPoint ServerEndPoint
