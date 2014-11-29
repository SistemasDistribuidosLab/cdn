# Modificaciones interesantes
* [Donde se trabaja con el cache en EdgeServers](#donde_se_utiliza_cache_edge_server)
* [Modificar política de asignación DNS](#politica_asignacion_dns)

<a name="donde_se_utiliza_cache_edge_server"></a>
### Donde se trabaja con el cache en EdgeServers
*EdgeServer.cpp*:
* Buscar en cache:
```c
Entry * a = ANSWERS->check( message_wse->getQuery() ); // Busca en el cache una query (message_wse->getQuery() -> BIGNUM*).
if (a != NULL && a->old( time() )) // Si está en el cache y no ha vencido su ttl
ANSWERS->remove(a); // Se remueve de cache
a = NULL;
```
Existen dos posibles caminos:
```c
if (a == NULL) // No está en el cache
{
    // Sumo cache hit y envio la consulta al WSE
    // [...]
}
else // La consulta está en cache
{
    // Sumo cache hit y envio la respuesta al cliente
    // [...]
}
```

<a name="politica_asignacion_dns"></a>
### Modificar Política de asignación DNS
*DNS.cpp:*
```c
/****************************************************************************************
*  Nombre: GetEdgeServerId
*  Funcion: Asigna un edge server al client i que pertenece al isp isp
*
*  Parametros:
*      - int id: id del cliente
*      - int isp: isp del cliente
*
*  Retorno: id del EdgeServer asignado al cliente
****************************************************************************************/
int Dns::GetEdgeServerId(int id, int isp) {
	// [...]
}
    ```


# Comandos

## Ejecutar
```sh
rm main ; clear ; make
```

## Compilar
```sql
g++ main.cpp Client.cpp EdgeServer.cpp Node.cpp Transport.cpp Message.cpp DNS.cpp ../../src/libcppsim.a -I../../src  -o main
```

## Tests
- [ ] `./main 100 5 5000`

## Mostrar Grafo Simulador
*__Importante__: Se debe hacer después de ejecutar el programa, ya que se crea al final de cada ejecución*
```sql
# Formato "dot"
dot ./grafo.dot -o ./grafodot && xdot ./grafodot
# Formato "neato" (para poder posicionar los elementos mas distribuidamente)
dot ./grafo.dot -o ./grafodot && xdot -f "neato" ./grafodot
```

# Otros

## Git
- Agregar modificaciones (includyendo archivos eliminados): `git add . -A`
- Revert changes made to your working copy:
  `git checkout .`
Revert changes made to the index (i.e., that you have added):
	`git reset`
* Revert a change that you have committed:
	`git revert ...`

## Crear grafo de dependencias
```
 	perl grafo.pl --quotetypes=quote >> grafo/grafo.dot
 	dot grafo/grafo.dot -o grafo/grafo
 	xdot grafo/grafo
 	#Todo en un comando:
 	perl grafo.pl --quotetypes=quote >> ./grafo/grafo.dot && dot ./grafo/grafo.dot -o ./grafo/grafo && xdot ./grafo/grafo
```
