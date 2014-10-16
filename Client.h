#ifndef CLIENT
#define CLIENT

#include "Node.h"

class EdgeServer;

class Client : public Node {
    private:
        // rng<double> *arrival_time;
    public:
        Client(int id, int type) : Node(id, type) {

        }
        ~Client(){

        }
};

#endif