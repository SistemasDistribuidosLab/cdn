#ifndef NODE
#define NODE

// #include "Message.h"
#include "cppsim.hh"
#include "Message.h"
#include <vector>

using namespace std;

class Transport;

class Node : public process {
    private:
        int id;
        int type;
        handle<Transport> * transport;
    protected:
        vector<Message *> message_stack;
    public:
        Node(const string &name, int id, int type) : process(name) {
            this->id = id;
            this->type = type;
        }
        ~Node() { }
        int GetId();
        string GetIdString();
        int GetType();
        void SetTransport(handle<Transport> * transport);
        void AddMessage(Message *message) {
            message_stack.push_back(message);
        }
        void SendMessage(Message *message);
        virtual void inner_body(void) = 0;
};

#endif