#include "Dns.h"

int abs(int a) {
    return a < 0 ? -a : a;
}

int Dns::GetEdgeServerId(int id, int isp) {
    int weight[ NUM_EDGE_SERVERS ];

    // Calcular la cantidad maxima de consultas recibidas en el intervalo (TIME_WINDOW segundos)
    int max_received_queries_by_edge_servers = 0;
    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        if (num_messages_received_by_edge_servers_cycle[ i ] > max_received_queries_by_edge_servers) {
            max_received_queries_by_edge_servers = num_messages_received_by_edge_servers_cycle[ i ];
        }
    }

    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        weight[ i ] =
            ( max_received_queries_by_edge_servers - num_messages_received_by_edge_servers_cycle[ i ] ) * 0.5 +
            abs( isp - edge_servers[ i ]->GetIsp() ) * 0.5
            ;
    }

    int id_mayor = 0;
    int mayor    = weight[ 0 ];
    for (int i = 1; i < NUM_EDGE_SERVERS; ++i) {
        if (weight[ i ] > mayor) {
            mayor = weight[ i ];
            id_mayor = i;
        }
    }
    num_messages_received_by_edge_servers_cycle[ id_mayor ]++;
    return id_mayor;
    // return id % NUM_EDGE_SERVERS;
}

// El reseteo se realiza en stats.cpp cada TIME_WINDOW segundos
void Dns::ResetCycle() {
    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        num_messages_received_by_edge_servers_cycle[ i ] = 0;
    }
}