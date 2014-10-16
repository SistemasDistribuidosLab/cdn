#ifndef NODE
#define NODE

// #include "Message.h"
#include <string>
#include <vector>

using namespace std;

class Node {
    private:
        int id;
        int type;
        vector<string*> message_stack;
    public:
        Node(int id, int type);
        ~Node();
        int GetId();
        string GetIdString();
        int GetType();
        void AddMessage(string * message) {
            message_stack.push_back(message);
        }
};

#endif