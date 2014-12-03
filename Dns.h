#ifndef DNS
#define DNS

#include "Constants.h"
#include "client/Client.h"
#include "edgeserver/EdgeServer.h"

class Dns {
    private:
        handle<Client> * clients;
        handle<EdgeServer> * edge_servers;
        unsigned int * num_messages_received_by_edge_servers_cycle;
        double isps[3][3];
        int max_received_queries_by_edge_servers_cycle;
    public:
        Dns(handle<Client> * clients, handle<EdgeServer> * edge_servers, double ptr_isps[][3]) {
            this->edge_servers = edge_servers;
            this->clients = clients;
            this->num_messages_received_by_edge_servers_cycle    = new unsigned int[ NUM_EDGE_SERVERS ];
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                num_messages_received_by_edge_servers_cycle[ i ] = 0;
            }

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    this->isps[ i ][ j ] = ptr_isps[ i ][ j ];
                }
            }
            this->max_received_queries_by_edge_servers_cycle = 1;
        }
        ~Dns() {}
        int GetEdgeServerId(int id, int isp);
        void ResetCycle();
};

#endif