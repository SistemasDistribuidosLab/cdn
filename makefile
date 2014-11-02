CPPSIM=-Isrc

all: main.o Client.o EdgeServer.o Node.o Transport.o Message.o DNS.o WSE.o LruA.o gen_rnd.o Util.o Stats.o Observer.o
	@g++ objects/main.o objects/Client.o objects/EdgeServer.o objects/Node.o objects/Transport.o objects/Message.o objects/DNS.o objects/WSE.o objects/LruA.o objects/gen_rnd.o objects/Util.o objects/Stats.o objects/Observer.o src/libcppsim.a -Isrc  -o main
	clear
	@./main

main.o: main.cpp
	@g++ $(CPPSIM) -c main.cpp -o objects/main.o

Client.o: Client.cpp
	@g++ $(CPPSIM) -c Client.cpp -o objects/Client.o

EdgeServer.o: EdgeServer.cpp
	@g++ $(CPPSIM) -c EdgeServer.cpp -o objects/EdgeServer.o

Node.o: Node.cpp
	@g++ $(CPPSIM) -c Node.cpp -o objects/Node.o

Transport.o: Transport.cpp
	@g++ $(CPPSIM) -c Transport.cpp -o objects/Transport.o

Message.o: Message.cpp
	@g++ $(CPPSIM) -c Message.cpp -o objects/Message.o

DNS.o: DNS.cpp
	@g++ $(CPPSIM) -c DNS.cpp -o objects/DNS.o

WSE.o: wse/WSE.cc
	@g++ $(CPPSIM) -c wse/WSE.cc -o objects/WSE.o

LruA.o: wse/LruA.cc
	@g++ $(CPPSIM) -c wse/LruA.cc -o objects/LruA.o

gen_rnd.o: generador/gen_rnd.cc
	@g++ $(CPPSIM) -c generador/gen_rnd.cc -o objects/gen_rnd.o

Util.o: auxiliar/Util.cc
	@g++ $(CPPSIM) -c auxiliar/Util.cc -o objects/Util.o

Stats.o: Stats.cpp
	@g++ $(CPPSIM) -c Stats.cpp -o objects/Stats.o

Observer.o: Observer.cc
	@g++ $(CPPSIM) -c Observer.cc -o objects/Observer.o




main:
	@g++ main.cpp Client.cpp EdgeServer.cpp Node.cpp Transport.cpp Message.cpp DNS.cpp wse/WSE.cc wse/LruA.cc generador/gen_rnd.cc auxiliar/Util.cc Stats.cpp Observer.cc src/libcppsim.a -Isrc  -o main
	clear
	@./main



clear:
	rm main ; clear