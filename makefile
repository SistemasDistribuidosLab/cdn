CPPSIM=-Isrc

all: main.o Client.o EdgeServer.o Node.o Transport.o Message.o DNS.o WSE.o LruA.o gen_rnd.o Util.o Stats.o Observer.o
	@g++ main.o Client.o EdgeServer.o Node.o Transport.o Message.o DNS.o WSE.o LruA.o gen_rnd.o Util.o Stats.o Observer.o src/libcppsim.a -Isrc  -o main
	clear
	@./main

main.o: main.cpp
	@g++ $(CPPSIM) -c main.cpp

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

WSE.o: wse/WSE.cc
	@g++ $(CPPSIM) -c wse/WSE.cc

LruA.o: wse/LruA.cc
	@g++ $(CPPSIM) -c wse/LruA.cc

gen_rnd.o: generador/gen_rnd.cc
	@g++ $(CPPSIM) -c generador/gen_rnd.cc

Util.o: auxiliar/Util.cc
	@g++ $(CPPSIM) -c auxiliar/Util.cc

Stats.o: Stats.cpp
	@g++ $(CPPSIM) -c Stats.cpp

Observer.o: Observer.cc
	@g++ $(CPPSIM) -c Observer.cc




main:
	@g++ main.cpp Client.cpp EdgeServer.cpp Node.cpp Transport.cpp Message.cpp DNS.cpp wse/WSE.cc wse/LruA.cc generador/gen_rnd.cc auxiliar/Util.cc Stats.cpp Observer.cc src/libcppsim.a -Isrc  -o main
	clear
	@./main



clear:
	rm main ; clear