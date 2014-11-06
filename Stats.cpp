#include "Stats.h"
#include "EdgeServer.h"
#include "Constants.h"

unsigned int Stats::cycles = 0;

void Stats::inner_body() {
    unsigned int total_received_queries_by_edge_servers;
    while (1) {
        total_received_queries_by_edge_servers = 0;
        (*received_querys_by_edge_servers) << time() << ", ";
        cache_hits_by_edge_servers << time() << ", ";
        for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
            (*received_querys_by_edge_servers) << edge_servers[ i ]->GetReceivedQueriesByClientsCycle() << ", ";
            total_received_queries_by_edge_servers += edge_servers[ i ]->GetReceivedQueriesByClientsCycle();

            /*    Cache Hits File */

            cache_hits_by_edge_servers << edge_servers[i]->GetCacheHitsReceivedQueriesByClientsCycle() << ", ";

            /*// Cache Hits File */

            edge_servers[i]->ResetCycle();
        }
        (*received_querys_by_edge_servers) << total_received_queries_by_edge_servers << ", ";
        (*received_querys_by_edge_servers) << endl;

        cache_hits_by_edge_servers << endl;
        cycles++;
        hold(10);
    }
}
