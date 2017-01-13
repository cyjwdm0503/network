
CC = g++
CFLAG = -Wall -g -I./channelsock -I./server  -I./client -I.

clientcpp=./client.cpp
channelcpp=./channelsock/Channel.cpp
channelh=./channelsock/Channel.h
inetsockcpp=./channelsock/InetSock.cpp
inetsockh=./channelsock/InetSock.h
servicenamecpp=./channelsock/ServiceName.cpp
servicenameh=./channelsock/ServiceName.h
sockh=./channelsock/sock.h
tcpsockcpp=./channelsock/TcpSock.cpp
tcpsockh=./channelsock/TcpSock.h
serverbasecpp=./server/ServerBase.cpp
serverbaseh=./server/ServerBase.h
serverendpointcpp=./ServerEndPoint.cpp
clientcpp=./client.cpp
servercpp=./server/Server.cpp
serverh= ./server/Server.h
logcpp = ./Log.cpp
logh=./Log.h
clientbasecpp=./client/ClientBase.cpp
clientbaseh=./client/ClientBase.h
tcpclientcpp=./client/TcpClient.cpp
tcpclienth=./client/TcpClient.h


channelo=./channelsock/Channel.o
inetsocko=./channelsock/InetScok.o
servicenameo=./channelsock/ServiceName.o
tcpsocko=./channelsock/TcpSock.o
serverbaseo=./server/ServerBase.o
cliento=./client.o
logo=./Log.o
servero=./server/Server.o
clientbaseo=./client/clientbase.o
tcpcliento=./client/tcpclient.o

allObj:$(channelo) $(servicenameo) $(tcpsocko) $(serverbaseo)  $(logo) $(clientbaseo) $(tcpcliento)
target: ClientEndPoint ServerEndPoint

Obj = $(channelo) $(servicenameo) $(tcpsocko) $(serverbaseo)  $(logo) $(inetsocko) $(servero) $(serverbaseo) $(clientbaseo) $(tcpcliento)

ClientEndPoint:$(clientcpp) $(Obj)
	$(CC) $(CFLAG) $^    -o $@

ServerEndPoint:$(serverendpointcpp) $(Obj)
	$(CC) $(CFLAG) $^    -o $@

$(servero):$(servercpp) $(serverh) 
	$(CC) $(CFLAG) -c $< -o $@

$(channelo):$(channelcpp) $(channelh)
	$(CC) $(CFLAG)  -c $< -o $@

$(logo):$(logcpp) $(logh)
	$(CC) $(CFLAG) -c $< -o $@

$(servicenameo):$(servicenamecpp) $(servecinameh)
	$(CC) $(CFLAG) -c $< -o $@

$(inetsocko):$(inetsockcpp) $(inetsockh)
	$(CC) $(CFLAG) -c $< -o $@

$(tcpsocko):$(tcpsockcpp) $(tcpsockh)
	$(CC) $(CFLAG) -c $< -o $@


$(serverbaseo):$(serverbasecpp) $(serverbaseh) 
	$(CC) $(CFLAG) -c $< -o $@

$(clientbaseo):$(clientbasecpp) $(clientbaseh)
	$(CC) $(CFLAG) -c $< -o $@
	
$(tcpcliento):$(tcpclientcpp) $(tcpclienth)
	$(CC) $(CFLAG) -c $< -o $@

clean:$(all)
	rm -rf */*.o ClientEndPoint ServerEndPoint *.o
