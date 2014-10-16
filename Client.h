#ifndef CLIENT
#define CLIENT

#include "Node.h"

class EdgeServer;

class Client : public Node{
    private:
        // rng<double> *arrival_time;
    public:
        Client(const string &name, int id, int type) : Node(name, id, type){

        }
        ~Client() {

        }
};

#endif