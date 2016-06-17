
CC = g++
CFLAG = -Wall -g 


allObj=Channel.o ServiceName.o InetSock.o TcpSock.o Log.o client.o
all:Channel.o ServiceName.o InetSock.o TcpSock.o Log.o client.o

client:$(allObj)
	$(CC) $(CFLAG) $(allObj) -o $@

client.o:client.cpp
	$(CC) $(CFLAG) -c $< -o $@


server:server.cpp TcpSock.h $(all)
	$(CC) $(CFLAG) $(all) -o $@

Channel.o:Channel.cpp Channel.h socks.h
	$(CC) $(CFLAG)  -c $< -o $@

Log.o:Log.cpp Log.h
	$(CC) $(CFLAG) -c $< -o $@

ServiceName.o:ServiceName.cpp ServiceName.h socks.h
	$(CC) $(CFLAG) -c $< -o $@

InetSock.o:InetSock.cpp InetSock.h
	$(CC) $(CFLAG) -c $< -o $@
TcpSock.o:TcpSock.cpp TcpSock.h
	$(CC) $(CFLAG) -c $< -o $@

clean:$(all)
	rm -rf *.o client
