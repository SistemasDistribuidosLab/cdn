main:
	@g++ main.cpp Client.cpp EdgeServer.cpp Node.cpp ../../src/libcppsim.a -I../../src  -o main
	clear
	@./main

clear:
	rm main ; clear