CDN
===
Ejecutar
--------
```
rm main ; clear ; make
```
 
Crear grafo
-----------
 	perl grafo.pl --quotetypes=quote >> grafo/grafo.dot
 	dot grafo/grafo.dot -o grafo/grafo
 	xdot grafo/grafo

 	perl grafo.pl --quotetypes=quote >> ./grafo/grafo.dot && dot ./grafo/grafo.dot -o ./grafo/grafo && xdot ./grafo/grafo

 Compilar:
 	rm main ; clear && g++ -DHAVE_CONFIG_H -I. -I.. -I../src    -g -O2 -MT main.o -MD -MP -MF .deps/main.Tpo -c -o main.o main.cc && mv -f .deps/main.Tpo .deps/main.Po && g++ -g -O2 -static  -o main main.o ../src/libcppsim.a && ./main

 Mostrar Grafo Simulador:
 	dot ./grafo.dot -o ./grafodot && xdot ./grafodot
 	dot ./grafo.dot -o ./grafodot && xdot -f "neato" ./grafodot

Comando Git:
	If you want to revert changes made to your working copy, do this:
	git checkout .

	If you want to revert changes made to the index (i.e., that you have added), do this:
	git reset

	If you want to revert a change that you have committed, do this:
	git revert ...
