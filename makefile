main:
	@g++ main.cpp Client.cpp EdgeServer.cpp Node.cpp Transport.cpp Message.cpp DNS.cpp wse/WSE.cc wse/LruA.cc generador/gen_rnd.cc auxiliar/Util.cc Observer.cc ../../src/libcppsim.a -I../../src  -o main
	clear
	@./main

clear:
	rm main ; clear