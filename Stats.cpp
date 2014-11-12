#include "Stats.h"
#include "EdgeServer.h"
#include "Constants.h"

unsigned int Stats::cycles = 0;

static inline void loadBar(int x, int n, int w, double time) {
    // ANSI Control codes to go back to the
    // previous line and clear it.
    printf("\n\033[F\033[J");

    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x / (float)n;
    int   c     = ratio * w;

    // Show the percentage complete.
    printf("Elapsed: %4.2f Left: %4.2f %3d%% [", time, ( time * 100 / (int)(ratio * 100) ) - time, (int)(ratio * 100) );

    // Show the load bar.
    for (int x = 0; x < c; x++)
        printf("=");

    for (int x = c; x < w; x++)
        printf(" ");

    printf("]");
}

void Stats::inner_body() {
    clock_t begin = clock();
    unsigned int total_received_queries_by_edge_servers;
    int * num_messages_received_by_edge_servers_cycle_aux = new int[ NUM_EDGE_SERVERS ];
    cout << ".";
    while (1) {
        loadBar(time(), DURACION_SIMULACION, 100, double(clock() - begin) / CLOCKS_PER_SEC);
        total_received_queries_by_edge_servers = 0;
        (*received_querys_by_edge_servers) << time() << ", ";
        cache_hits_by_edge_servers << time() << ", ";
        for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
            (*received_querys_by_edge_servers) << (edge_servers[ i ]->GetReceivedQueriesByClientsCycle() / TIME_WINDOW) << ", ";
            total_received_queries_by_edge_servers += edge_servers[ i ]->GetReceivedQueriesByClientsCycle();

            // Guardo las queries recividas por el edge server aca
            num_messages_received_by_edge_servers_cycle_aux[ i ] = edge_servers[ i ]->GetReceivedQueriesByClientsCycle();

            /*    Cache Hits File */

            cache_hits_by_edge_servers << edge_servers[i]->GetCacheHitsReceivedQueriesByClientsCycle() << ", ";

            /*// Cache Hits File */

            edge_servers[i]->ResetCycle();
        }
        dns->ResetCycle();

        (*received_querys_by_edge_servers) << total_received_queries_by_edge_servers / TIME_WINDOW << ", ";
        (*received_querys_by_edge_servers) << endl;

        cache_hits_by_edge_servers << endl;
        cycles++;
        hold(TIME_WINDOW);
    }
}
