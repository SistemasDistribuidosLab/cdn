#ifndef DNS
#define DNS

#include "Constants.h"
#include "Client.h"
#include "EdgeServer.h"

class Dns {
    private:
        handle<Client> * clients;
        handle<EdgeServer> * edge_servers;
        unsigned int * num_messages_received_by_edge_servers_cycle;
    public:
        Dns(handle<Client> * clients, handle<EdgeServer> * edge_servers) {
            this->edge_servers = edge_servers;
            this->clients = clients;
            this->num_messages_received_by_edge_servers_cycle    = new unsigned int[ NUM_EDGE_SERVERS ];
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                num_messages_received_by_edge_servers_cycle[ i ] = 0;
            }
        }
        ~Dns() {}
        int GetEdgeServerId(int id, int isp);
        void ResetCycle();
};

#endif