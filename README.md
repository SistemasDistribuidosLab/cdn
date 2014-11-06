##Comandos Simulador
###Ejecutar
```sh
rm main ; clear ; make
```


###Compilar
```sql
g++ main.cpp Client.cpp EdgeServer.cpp Node.cpp Transport.cpp Message.cpp DNS.cpp ../../src/libcppsim.a -I../../src  -o main
```

###Mostrar Grafo Simulador
```sql
# Formato "dot"
dot ./grafo.dot -o ./grafodot && xdot ./grafodot
# Formato "neato" (para poder posicionar los elementos mas distribuidamente)
dot ./grafo.dot -o ./grafodot && xdot -f "neato" ./grafodot
```

##Git
- Agregar modificaciones (includyendo archivos eliminados): ```git add . -A```
* Revert changes made to your working copy:
	```git checkout .```
* Revert changes made to the index (i.e., that you have added):
	```git reset```
* Revert a change that you have committed:
	```git revert ...```

##Otros
###Crear grafo de dependencias
```
 	perl grafo.pl --quotetypes=quote >> grafo/grafo.dot
 	dot grafo/grafo.dot -o grafo/grafo
 	xdot grafo/grafo
 	#Todo en un comando:
 	perl grafo.pl --quotetypes=quote >> ./grafo/grafo.dot && dot ./grafo/grafo.dot -o ./grafo/grafo && xdot ./grafo/grafo
```
