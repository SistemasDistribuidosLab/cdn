#ifndef CLIENT
#define CLIENT

#include "Node.h"

class EdgeServer;
class Transport;
class Dns;

class Client : public Node {
    private:
        rng<double> *arrival_time;
        Dns *dns;
        int number_of_messages_sended_to_dns;
        int number_of_querys_sended_this_cycle;
        ifstream *endStream;
        vector<MessageWSE*> message_wse_stack;
        unsigned int querys_sended;
    public:
        Client(const string &name, int id, int type, rng<double> *arrival_time, ifstream *endStream) : Node(name, id, type) {
            this->arrival_time = arrival_time;
            this->querys_sended = 0;
            this->number_of_messages_sended_to_dns = 0;
            this->number_of_querys_sended_this_cycle = 0;
            this->endStream = endStream;
        }
        ~Client() {

        }
        void SetDns(Dns *dns) {
            this->dns = dns;
        }

        void AddMessageWse(MessageWSE *message_wse);

        void ResetCycle();
        int GetNumberOfQuerysSendedThisCycle();

        void inner_body(void);
        int GetEdgeServerId();
        int GetNumberOfMessagesSendedToDns();
        void HaveToSendAMessage();
        double SendMessage(Message * message);
        unsigned int GetQuerysSended();
};

#endif
