CPPSIM=-Isrc

all: main.o Client.o EdgeServer.o Node.o Transport.o Message.o DNS.o
	main.o Client.o EdgeServer.o Node.o Transport.o Message.o DNS.o wse/WSE.cc wse/LruA.cc generador/gen_rnd.cc auxiliar/Util.cc Stats.cpp Observer.cc src/libcppsim.a -Isrc  -o main

main.o: Client.o EdgeServer.o Node.o Transport.o Message.o DNS.o
	g++ main.o Client.o EdgeServer.o Transport.o Message.o DNS.o wse/WSE.cc wse/LruA.cc generador/gen_rnd.cc auxiliar/Util.cc Stats.cpp Observer.cc src/libcppsim.a -Isrc  -o main

Client.o: Client.cpp
	@g++ $(CPPSIM) -c Client.cpp

EdgeServer.o: EdgeServer.cpp 
	@g++ $(CPPSIM) -c EdgeServer.cpp 

Node.o: Node.cpp 
	@g++ $(CPPSIM) -c Node.cpp 

Transport.o: Transport.cpp
	@g++ $(CPPSIM) -c Transport.cpp

Message.o: Message.cpp
	@g++ $(CPPSIM) -c Message.cpp

DNS.o: DNS.cpp
	@g++ $(CPPSIM) -c DNS.cpp




main:
	@g++ main.cpp Client.cpp EdgeServer.cpp Node.cpp Transport.cpp Message.cpp DNS.cpp wse/WSE.cc wse/LruA.cc generador/gen_rnd.cc auxiliar/Util.cc Stats.cpp Observer.cc src/libcppsim.a -Isrc  -o main
	clear
	@./main



clear:
	rm main ; clear