# Explicaciones
* [Proceso de enviar un mensaje desde un cliente a un EdgeServer](#proceso-de-enviar-un-mensaje-desde-un-cliente-a-un-edgeserver)

### Proceso de enviar un mensaje desde un cliente a un EdgeServer

Él código a continuación corresponde a la clase cliente, pero es común en los demás servidores (edge servers y wse):

```c
// Parametros de esta llamada: 
// id del creador, tipo creador, id receptor, tipo receptor, 
// tiempo creacion mensaje, mensaje (de tipo MessageWSE *) 
Message * message = new Message(this->GetId(), NODE_CLIENT, edge_server_to, NODE_EDGE_SERVER, time(), message_wse);
Message * message = new Message(this->GetId(), NODE_CLIENT, edge_server_to, NODE_EDGE_SERVER, time(), message_wse);
// delay corresponde al delay de enviar mensaje entre isp de emisor y receptor
delay = this->SendMessage(message);
```

SendMessage está definido en Node.cpp (**Ojo: puede ser sobreescrito por la clases que heredan de él)

```c
// Node.cpp
double Node::SendMessage(Message *message) {
    // Suma uno al contador de mensajes enviados
    this->num_messages_sended++;
    // Calcula el delay basado en el isp tanto del emisor como del receptor
    // Necesita el tipo del receptor para saber en que arreglo de servidores buscar (clients, edge_servers, wse)
    double delay = this->GetIspDelay(this->GetIsp(), message->GetIdTo(), message->GetTypeTo());
    // Añade el mensaje a la cola de la capa de transporte y lo despierta si está idle
    (*transport)->AddMessage(message);
    if ((*transport)->idle()) {
        (*transport)->activate();
    }
    return delay;
}
```

Luego, dentro de *Transport.cpp*:

```c
while (1) {
        // Por cada mensaje en el stack
        while (!message_stack.empty()) {
        	// Variable que guardará el servidor receptor (cliente, edge server o wse)
            Node *servidor;
            // [ Se asigna el servidor dependiendo del tipo ]

            // Se añade el mensaje al receptor y se activa
            servidor->AddMessage(message);
            if (servidor->idle()) {
                servidor->activate();
            }
        }
        [ Se duerme el proceso...]
    }
```

El receptor del mensaje realiza un proceso similar al proceso transporte:



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
