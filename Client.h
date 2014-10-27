#ifndef CLIENT
#define CLIENT

#include "Node.h"

class EdgeServer;
class Transport;
class Dns;

class Client : public Node {
    private:
        rng<double> *arrival_time;
        Dns * dns;
        int number_of_messages_sended_to_dns;
        int number_of_querys_sended_this_cycle;
    public:
        unsigned int querys_send;
        Client(const string &name, int id, int type, rng<double> *arrival_time) : Node(name, id, type) {
            this->arrival_time = arrival_time;
            this->querys_send = 0;
            this->number_of_messages_sended_to_dns = 0;
            this->number_of_querys_sended_this_cycle = 0;
        }
        ~Client() {

        }
        void SetDns(Dns * dns){
            this->dns = dns;
        }
        
        void ResetCycle();
        int GetNumberOfQuerysSendedThisCycle();

        void inner_body(void);
        int GetEdgeServerId();
        int GetNumberOfMessagesSendedToDns();
        void HaveToSendAMessage();
};

#endif