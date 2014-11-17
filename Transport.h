#ifndef TRANSPORT
#define TRANSPORT

#include "cppsim.hh"
#include "Node.h"
#include "Message.h"
#include <vector>

using namespace std;

class Client;
class EdgeServer;
class WSE;

class Transport : public Node {
    private:
        handle<EdgeServer> *edge_servers;
        handle<Client> *clients;
        handle<WSE> *wse;
        static double isps[3][3];
    public:
        Transport(const string &name, int id, int type) : Node(name, id, type) {
            //cout << "{*} Transporte iniciado" << endl;
        }
        static void SetIsps(double isps[][3]);
        ~Transport() {}
        void SetEdgeServers(handle<EdgeServer> *edge_servers);
        void SetClients(handle<Client> *clients);
        void SetWse(handle<WSE> *wse);
        void AddMessage(Message *message);
        void SetIsp(int);
        void inner_body(void);
        Node *GetServer(int id_, int type);
        int GetNumOfServers(int type);
        double GetIspDelay(int isp_from, int id_to, int type_to) {
            Node *server = GetServer(id_to, type_to);
            // cout << "Isp from: " << isp_from << " - " << server->GetIsp() << ": " << isps[ server->GetIsp() ][ isp_from ] << endl;
            /*cout << isps[ 0 ][ 0 ] << endl;
            cout << server->GetIsp() << " x " << isp_from << endl;*/
            return isps[ server->GetIsp() ][ isp_from ];
        }
};

#endif