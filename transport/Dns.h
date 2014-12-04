#ifndef DNS
#define DNS

#include "../Constants.h"
#include "../client/Client.h"
#include "../edgeserver/EdgeServer.h"

class Dns {
    private:
        handle<Client> * clients;
        handle<EdgeServer> * edge_servers;
        // Almacena la cantidad de mensajes recibidos por parte de los edge servers
        // Cuando se llama a "ResetCycle()", se reinicia a 0.
        unsigned int * num_messages_received_by_edge_servers_cycle;
        double isps[3][3];
        int max_received_queries_by_edge_servers_cycle;
    public:
        /**
          *
          * - clients: puntero que referencia a los clientes creados en main.cpp
          * - edge_servers: puntero que referencia a los edge servers creados en main.cpp
          * - ptr_isps: matriz que representa a los isp's. En main.cpp se define esta matriz
          *
          **/
        Dns(handle<Client> * clients, handle<EdgeServer> * edge_servers, double ptr_isps[][3]) {
            this->edge_servers = edge_servers;
            this->clients = clients;
            this->num_messages_received_by_edge_servers_cycle    = new unsigned int[ NUM_EDGE_SERVERS ];
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                num_messages_received_by_edge_servers_cycle[ i ] = 0;
            }

            // Copio la matriz a mi matriz local ya que los valores no cambiarán a lo largo de la ejecución
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