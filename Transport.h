#ifndef TRANSPORT
#define TRANSPORT

#include "Message.h"
#include "cppsim.hh"
#include <vector>

using namespace std;

class Client;
class EdgeServer;

class Transport {
    private:
        handle<EdgeServer> *edge_servers;
        handle<Client> *clients;
    public:
        Transport() {
            //cout << "{*} Transporte iniciado" << endl;
        }
        ~Transport() {}
        void SetEdgeServers(handle<EdgeServer> *edge_servers) {
            this->edge_servers = edge_servers;
        }
        void SetClients(handle<EdgeServer> *edge_servers) {
            this->clients = clients;
        }
        void SendMessage(Message *message);
};

#endif