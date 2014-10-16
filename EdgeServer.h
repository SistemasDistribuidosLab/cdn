#ifndef EDGE_SERVER
#define EDGE_SERVER

#include "Node.h"

using namespace std;

class Client;

class EdgeServer : public Node {
    private:
        double idle_time;
        double busy_time;
        unsigned int processed_querys;
        unsigned int *received_querys_from_count;
        Client * client;
    public:
        EdgeServer(int id, int type) : Node(id, type) {
            idle_time = 0;
            busy_time = 0;
            processed_querys = 0;
            // received_querys_from_count = new int[ NUM_CLIENTS ];
            // for (int i = 0; i < NUM_CLIENTS; ++i) {
            // received_querys_from_count[ i ] = 0;
            // }
        }
        ~EdgeServer() {
        }
        double GetIdleTime();
        double GetBusyTime();
        double GetProcessedQuerys();
        int GetQuerysByClient(int j);
};
#endif