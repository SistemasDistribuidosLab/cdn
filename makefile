OPCIONES_COMPILADOR=-g -w
CPPSIM=-Isrc $(OPCIONES_COMPILADOR)

all: main.o Client.o EdgeServer.o Node.o Transport.o Message.o DNS.o WSE.o LruA.o Lru.o gen_rnd.o Util.o Stats.o Observer.o Hash.o
	clang++ objects/main.o objects/Client.o objects/EdgeServer.o objects/Node.o objects/Transport.o objects/Message.o objects/DNS.o objects/WSE.o objects/LruA.o objects/Lru.o objects/gen_rnd.o objects/Util.o objects/Stats.o objects/Observer.o objects/Hash.o src/libcppsim.a $(CPPSIM) -L/usr/lib -lssl -lcrypto -o main
	clear
	@./main

main.o: main.cpp
	@clang++ $(CPPSIM) -c main.cpp -o objects/main.o

Client.o: Client.cpp
	@clang++ $(CPPSIM) -c Client.cpp -o objects/Client.o

EdgeServer.o: EdgeServer.cpp
	@clang++ $(CPPSIM) -c EdgeServer.cpp -o objects/EdgeServer.o

Node.o: Node.cpp
	@clang++ $(CPPSIM) -c Node.cpp -o objects/Node.o

Transport.o: Transport.cpp
	@clang++ $(CPPSIM) -c Transport.cpp -o objects/Transport.o

Message.o: Message.cpp
	@clang++ $(CPPSIM) -c Message.cpp -o objects/Message.o

DNS.o: DNS.cpp
	@clang++ $(CPPSIM) -c DNS.cpp -o objects/DNS.o

WSE.o: wse/WSE.cc
	@clang++ $(CPPSIM) -c wse/WSE.cc -o objects/WSE.o

LruA.o: wse/LruA.cc
	@clang++ $(CPPSIM) -c wse/LruA.cc -o objects/LruA.o

Lru.o: wse/Lru.cc
	@clang++ $(CPPSIM) -c wse/Lru.cc -o objects/Lru.o

gen_rnd.o: generador/gen_rnd.cc
	@clang++ $(CPPSIM) -c generador/gen_rnd.cc -o objects/gen_rnd.o

Util.o: auxiliar/Util.cc
	@clang++ $(CPPSIM) -c auxiliar/Util.cc -o objects/Util.o

Stats.o: Stats.cpp
	@clang++ $(CPPSIM) -c Stats.cpp -o objects/Stats.o

Observer.o: Observer.cc
	@clang++ $(CPPSIM) -c Observer.cc -o objects/Observer.o

Hash.o: auxiliar/Hash.cc
	@clang++ $(CPPSIM) -c auxiliar/Hash.cc -o objects/Hash.o

main:
	@clang++ main.cpp Client.cpp EdgeServer.cpp Node.cpp Transport.cpp Message.cpp DNS.cpp wse/WSE.cc wse/LruA.cc generador/gen_rnd.cc auxiliar/Util.cc Stats.cpp Observer.cc src/libcppsim.a -Isrc  -o main
	clear
	@./main



clear:
	rm main ; clear