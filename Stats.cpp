#include "Stats.h"
#include "EdgeServer.h"
#include "Constants.h"

unsigned int Stats::cycles = 0;

void Stats::inner_body() {
    unsigned int total_received_queries_by_edge_servers;
    while (1) {
        total_received_queries_by_edge_servers = 0;
        (*received_querys_by_edge_servers) << time() << ", ";
        for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
            (*received_querys_by_edge_servers) << edge_servers[ i ]->GetReceivedQueriesByClients() << ", ";
            total_received_queries_by_edge_servers += edge_servers[ i ]->GetReceivedQueriesByClients();
            edge_servers[ i ]->ResetReceivedQueriesByClients();
        }
        (*received_querys_by_edge_servers) << total_received_queries_by_edge_servers << ", ";
        (*received_querys_by_edge_servers) << endl;
        cycles++;
        hold(10);
    }
}