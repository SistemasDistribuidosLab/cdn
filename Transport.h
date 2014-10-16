#ifndef TRANSPORT
#define TRANSPORT

#include "cppsim.hh"
#include "Node.h"
#include "Message.h"
#include <vector>

using namespace std;

class Client;
class EdgeServer;

class Transport : public Node {
    private:
        handle<EdgeServer> *edge_servers;
        handle<Client> *clients;
    public:
        Transport(const string &name, int id, int type) : Node(name, id, type) {
            //cout << "{*} Transporte iniciado" << endl;
        }
        ~Transport() {}
        void SetEdgeServers(handle<EdgeServer> *edge_servers);
        void SetClients(handle<Client> *clients);
        void AddMessage(Message *message);
        void inner_body(void);
};

#endif