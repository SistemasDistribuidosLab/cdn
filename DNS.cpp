#include "Dns.h"

int Dns::GetEdgeServerId(int id) {
    return id % NUM_EDGE_SERVERS;
}