#ifndef NODE
#define NODE

// #include "Message.h"
#include "cppsim.hh"
#include <string>
#include <vector>

using namespace std;

class Node : public process {
    private:
        int id;
        int type;
        vector<string *> message_stack;
    public:
        Node(const string &name, int id, int type) : process(name) {
            this->id = id;
            this->type = type;
        }
        ~Node() { }
        int GetId();
        string GetIdString();
        int GetType();
        void AddMessage(string *message) {
            message_stack.push_back(message);
        }
        void inner_body(void) {

        }
};

#endif