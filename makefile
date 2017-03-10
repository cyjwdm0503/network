CC = g++
CFLAGS = -Wall -lpthread -g -lrt -ldl -I./channelsock -I./client \
					 -I./lowsession -I./package -I./server -I./thread -I./
CXXFLAGS = $(CFLAGS)

####channelsock
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
udpsockh=./channelsock/UdpSock.h

##client
clientbasecpp=./client/ClientBase.cpp
clientbaseh=./client/ClientBase.h
clientcpp=./client/Client.cpp
clienth=./client/Client.h

#lowsession
sessionbasecpp = ./lowsession/SessionBase.cpp 
sessionbaseh=./lowsession/SessionBase.h

#package
channelpackagecpp = ./package/channelpackage.cpp 
channelpackageh = ./package/channelpackage.h 
contentpackagecpp = ./package/contentpackage.cpp
contentpackageh = ./package/contentpackage.h
packagecpp = ./package/Package.cpp 
packageh = ./package/Package.h 


#server 
serverbasecpp=./server/ServerBase.cpp
serverbaseh=./server/ServerBase.h
servercpp=./server/Server.cpp
serverh= ./server/Server.h

#thread 
commonh = ./thread/Common.h 
dispathercpp = ./thread/Dispatcher.cpp 
dispatherh = ./thread/Dispatcher.h
eventqueuecpp = ./thread/EventQueue.cpp
eventqueueh = ./thread/EventQueue.h 
handlercpp= ./thread/Handler.cpp
handlerh = ./thread/Handler.h 
mutexcpp = ./thread/Mutex.cpp 
mutexh = ./thread/Mutex.h 
mutexgurardcpp = ./thread/MutexGuard.cpp 
mutexgurardh = ./thread/MutexGuard.h 
selectreactorcpp =./thread/SelectReactor.cpp
selectreactorh =./thread/SelectReactor.h
semaphorecpp = ./thread/Semaphore.cpp 
semaphoreh = ./thread/Semaphore.h 
threadcpp = ./thread/Thread.cpp 
threadh = ./thread/Thread.h 
timerheapcpp = ./thread/TimerHeap.cpp
timerheaph = ./thread/TimerHeap.h
timerqueueh = ./thread/TimerQueue.h

#global
clientapicpp = ./ClientApi.cpp 
clientapih =./ClientApi.h
logcpp = ./Log.cpp
logh=./Log.h
serverendpointcpp=./ServerEndPoint.cpp
clientendpointcpp=./ClientEndPoint.cpp
serverapicpp = ./ServerApi.cpp 
serverapih = ./ServerApi.h


####channelsock
channelo=./channelsock/Channel.o
inetsocko=./channelsock/InetSock.o
servicenameo=./channelsock/ServiceName.o
tcpsocko=./channelsock/TcpSock.o
udpchannelo=./channelsock/UdpChannel.o
udpsocko=./channelsock/UdpSock.o

##client
clientbaseo=./client/ClientBase.o
cliento=./client/Client.o

#lowsession
sessionbaseo = ./lowsession/SessionBase.o

#package
channelpackageo = ./package/channelpackage.o
contentpackageo = ./package/contentpackage.o
packageo= ./package/Package.o

#server 
serverbaseo=./server/ServerBase.o
servero=./server/Server.o

#thread 
dispathero = ./thread/Dispatcher.o
mutexo = ./thread/Mutex.o
mutexgurardo = ./thread/MutexGuard.o
selectreactoro =./thread/SelectReactor.o
semaphoreo = ./thread/Semaphore.o
threado = ./thread/Thread.o
handlero = ./thread/Handler.o
eventqueueo = ./thread/EventQueue.o
timerheapo = ./thread/TimerHeap.o

#global
clientapio = ./ClientApi.o
logo = ./Log.o
serverendpointo=./ServerEndPoint.o
clientendpointo=./ClientEndPoint.o
serverapio = ./ServerApi.o 



target:ClientEndPoint ServerEndPoint \

Obj = $(channelo) $(inetsocko) $(servicenameo) $(tcpsocko) $(udpsocko) $(udpchannelo) \
			$(clientbaseo) $(cliento) \
			$(sessionbaseo) \
			$(channelpackageo) $(contentpackageo) $(packageo) \
			$(serverbaseo) $(servero) \
			$(handlero) $(eventqueueo) $(timerheapo)  $(threado) $(dispathero) $(mutexo) $(mutexgurardo) $(selectreactoro) $(semaphoreo) \
			$(clientapio) $(logo) $(serverendpointo) $(clientendpointo) $(serverapio)



ClientEndPoint:$(clientendpointcpp) $(Obj)
	$(CC) $(CFLAGS) -DCLIENT  $^    -o $@

ServerEndPoint:$(serverendpointcpp) $(Obj)
	$(CC) $(CFLAGS) -DSERVER $^    -o $@

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

$(cliento):$(clientcpp) $(clienth)
	$(CC) $(CFLAGS) -c $< -o $@

clean:$(all)
	rm -rf */*.o ClientEndPoint ServerEndPoint *.o
