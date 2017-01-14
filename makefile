
CC = g++
CFLAGS = -Wall -g -I./channelsock -I./server  -I./client -I.


channelcpp=./channelsock/Channel.cpp
channelh=./channelsock/Channel.h
inetsockcpp=./channelsock/InetSock.cpp
inetsockh=./channelsock/InetSock.h
servicenamecpp=./channelsock/ServiceName.cpp
servicenameh=./channelsock/ServiceName.h
sockh=./channelsock/sock.h
tcpsockcpp=./channelsock/TcpSock.cpp
tcpsockh=./channelsock/TcpSock.h
udpchannelcpp=./channelsock/UdpChannel.cpp
udpchannelh=./channelsock/UdpChannel.cpp
udpsockcpp=./channelsock/UdpSock.cpp
udpsockh=/channelsock/UdpSock.h

serverbasecpp=./server/ServerBase.cpp
serverbaseh=./server/ServerBase.h
servercpp=./server/Server.cpp
serverh= ./server/Server.h

logcpp = ./Log.cpp
logh=./Log.h
serverendpointcpp=./ServerEndPoint.cpp
clientendpointcpp=./ClientEndPoint.cpp

clientbasecpp=./client/ClientBase.cpp
clientbaseh=./client/ClientBase.h
clientcpp=./client/Client.cpp
clienth=./client/Client.h


channelo=./channelsock/Channel.o
inetsocko=./channelsock/InetScok.o
servicenameo=./channelsock/ServiceName.o
tcpsocko=./channelsock/TcpSock.o
udpsocko=./channelsock/UdpSock.o
udpchannelo=./channelsock/UdpChannel.o

serverbaseo=./server/ServerBase.o
servero=./server/Server.o
clientbaseo=./client/clientbase.o
cliento=./client/client.o


logo=./Log.o


target=ClientEndPoint ServerEndPoint

target:ClientEndPoint ServerEndPoint
allObj:$(channelo) $(inetsocko) $(servicenameo) $(tcpsocko) $(udpsocko) $(udpchannelo) $(serverbaseo) $(servero) $(clientbaseo) $(cliento) 
Obj = $(channelo) $(inetsocko) $(servicenameo) $(tcpsocko) $(udpsocko) $(udpchannelo) $(serverbaseo) $(servero) $(clientbaseo) $(cliento) 

ClientEndPoint:$(clientendpointcpp) $(Obj)
	$(CC) $(CFLAGS) $^    -o $@

ServerEndPoint:$(serverendpointcpp) $(Obj)
	$(CC) $(CFLAGS) $^    -o $@

$(servero):$(servercpp) $(serverh) 
	$(CC) $(CFLAGS) -c $< -o $@

$(channelo):$(channelcpp) $(channelh)
	$(CC) $(CFLAGS)  -c $< -o $@

$(logo):$(logcpp) $(logh)
	$(CC) $(CFLAGS) -c $< -o $@

$(servicenameo):$(servicenamecpp) $(servecinameh)
	$(CC) $(CFLAGS) -c $< -o $@

$(inetsocko):$(inetsockcpp) $(inetsockh)
	$(CC) $(CFLAGS) -c $< -o $@

$(tcpsocko):$(tcpsockcpp) $(tcpsockh)
	$(CC) $(CFLAGS) -c $< -o $@


$(serverbaseo):$(serverbasecpp) $(serverbaseh) 
	$(CC) $(CFLAGS) -c $< -o $@

$(clientbaseo):$(clientbasecpp) $(clientbaseh)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(cliento):$(tcpclientcpp) $(tcpclienth)
	$(CC) $(CFLAG) -c $< -o $@

clean:$(all)
	rm -rf */*.o ClientEndPoint ServerEndPoint *.o
