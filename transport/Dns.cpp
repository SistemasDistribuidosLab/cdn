#include "Dns.h"

inline int abs(int a) {
    return a < 0 ? -a : a;
}

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
    int weight[ NUM_EDGE_SERVERS ];

    max_received_queries_by_edge_servers_cycle = 0;

    // Calcular la cantidad maxima de consultas recibidas en el intervalo (TIME_WINDOW segundos)
    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        if (num_messages_received_by_edge_servers_cycle[ i ] > max_received_queries_by_edge_servers_cycle) {
            max_received_queries_by_edge_servers_cycle = num_messages_received_by_edge_servers_cycle[ i ];
        }
    }

    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        weight[ i ] =
            // A mayor cantidad de mensajes recibidos, mayor peso
            (
                max_received_queries_by_edge_servers_cycle > 0 ?
                (
                    ( num_messages_received_by_edge_servers_cycle[ i ] ) / max_received_queries_by_edge_servers_cycle
                )
                :
                0
            )
            +
            // Si la latencia es mayor, sube el peso
            isps[ isp ][ edge_servers[ i ]->GetIsp() ];
    }

    int id_menor = 0;
    int menor    = weight[ 0 ];
    for (int i = 1; i < NUM_EDGE_SERVERS; ++i) {
        if (weight[ i ] < menor) {
            menor = weight[ i ];
            id_menor = i;
        }
    }
    num_messages_received_by_edge_servers_cycle[ id_menor ]++;
    return id_menor;
    // return id % NUM_EDGE_SERVERS;
}

// El reseteo se realiza en stats.cpp cada TIME_WINDOW segundos
void Dns::ResetCycle() {
    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        num_messages_received_by_edge_servers_cycle[ i ] = 0;
    }
}