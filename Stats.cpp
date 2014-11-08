#include "Stats.h"
#include "EdgeServer.h"
#include "Constants.h"

unsigned int Stats::cycles = 0;

void Stats::inner_body()
{
    unsigned int total_received_queries_by_edge_servers;
    while (1)
    {
        total_received_queries_by_edge_servers = 0;
        (*received_querys_by_edge_servers) << time() << ", ";
        cache_hits_by_edge_servers << time() << ", ";
        for (int i = 0; i < NUM_EDGE_SERVERS; ++i)
        {
            (*received_querys_by_edge_servers) << edge_servers[ i ]->GetReceivedQueriesByClients() << ", ";
            total_received_queries_by_edge_servers += edge_servers[ i ]->GetReceivedQueriesByClients();

            /*    Cache Hits File */

            // cout << edge_servers[i]->GetCacheMissCycle() << endl;
            // cache_hits_by_edge_servers << edge_servers[i]->GetCacheHitsCycle() << ", ";
            // cache_hits_by_edge_servers << edge_servers[i]->GetCacheMissCycle() << ", ";
            // cout << "Stats:" << endl;
            // cout << edge_servers[i]->GetCacheMissCycle() << " + " << edge_servers[i]->GetCacheHitsCycle() << endl;
            if ( edge_servers[i]->GetCacheMissCycle() + edge_servers[i]->GetCacheHitsCycle() > 0)
            {
                cout << edge_servers[i]->GetCacheHitsCycle() << " / " << total_received_queries_by_edge_servers << " = " << 100 * (((double)edge_servers[i]->GetCacheHitsCycle()) / (double)total_received_queries_by_edge_servers ) << endl;
                cache_hits_by_edge_servers << 100 * (((double)edge_servers[i]->GetCacheHitsCycle()) / (double)total_received_queries_by_edge_servers ) << ", ";
                total_cache_hits_by_edge_servers += (double)edge_servers[i]->GetCacheHitsCycle();
            }
            else{
                cache_hits_by_edge_servers << 0 << ", ";
            }
            edge_servers[i]->ResetCycle();

            /*// Cache Hits File */

            // edge_servers[i]->ResetCycle();
        }
        (*received_querys_by_edge_servers) << total_received_queries_by_edge_servers << ", ";
        (*received_querys_by_edge_servers) << endl;

        cache_hits_by_edge_servers << endl;
        cycles++;
        hold(10);
    }
}