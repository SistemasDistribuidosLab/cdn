#include "Dns.h"

int Dns::GetEdgeServerId(int id) {
    // return 0;
    return id % NUM_EDGE_SERVERS;
}