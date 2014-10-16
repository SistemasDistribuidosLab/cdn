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
    public:
        unsigned int querys_send;
        Client(const string &name, int id, int type, rng<double> *arrival_time) : Node(name, id, type) {
            this->arrival_time = arrival_time;
            this->querys_send = 0;
        }
        ~Client() {

        }
        void SetDns(Dns * dns){
            this->dns = dns;
        }
        void inner_body(void);
};

#endif