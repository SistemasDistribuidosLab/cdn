#include "Stats.h"
#include "EdgeServer.h"
#include "Constants.h"

unsigned int Stats::cycles = 0;

void Stats::inner_body() {
    unsigned long int previous_query_number_by_edge_server[ NUM_EDGE_SERVERS ];
    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        previous_query_number_by_edge_server[ i ] = 0;
    }
    while (1) {
    	(*output) << cycles << ", ";
        for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
            (*output) << ( edge_servers[ i ]->GetProcessedQuerys() - previous_query_number_by_edge_server[ i ] ) << ", ";
            previous_query_number_by_edge_server[ i ] = edge_servers[ i ]->GetProcessedQuerys();
        }
        (*output) << endl;
        cycles++;
        hold(10);
    }
}