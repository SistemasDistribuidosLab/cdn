#ifndef EDGE_SERVER
#define EDGE_SERVER

#include "Node.h"
#include "Constants.h"

using namespace std;

// class Client;
class MessageWSE;

class EdgeServer : public Node {
    private:
        double idle_time;
        double busy_time;
        unsigned int processed_querys;
        unsigned int *received_querys_from_count;
        unsigned int received_queries_by_clients_cycle;
        // Client *client;
    public:
        EdgeServer(const string &name, int id, int type) : Node(name, id, type) {
            idle_time = 0;
            busy_time = 0;
            processed_querys = 0;
            received_querys_from_count = new unsigned int[ NUM_CLIENTS ];
            for (int i = 0; i < NUM_CLIENTS; ++i) {
                received_querys_from_count[ i ] = 0;
            }
            this->received_queries_by_clients_cycle = 0;
        }
        ~EdgeServer() {
        }
        double GetIdleTime();
        double GetBusyTime();
        double GetProcessedQuerys();
        int GetQuerysByClient(int j);
        void inner_body(void);
        void SumToIdleTime(double);
        void SumToBusyTime(double);
        void SumToProcessedQuerys();
        void ReceiveANewMessageFromClient(int);
        Message * GetMessage();
        void AddANewUnprocessedMessage(Message * message);
        void ResetReceivedQueriesByClients();
        unsigned int GetReceivedQueriesByClients();
};
#endif