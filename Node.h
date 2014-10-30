#ifndef NODE
#define NODE

// #include "Message.h"
#include "cppsim.hh"
#include "Message.h"
#include "Isp.h"
#include <vector>

using namespace std;

class Transport;

class Node : public process {
    private:
        int id;
        int type;
        handle<Transport> *transport;
        int isp;
        double delay_acum;
        unsigned int num_messages_sended;
    protected:
        vector<Message *> message_stack;
        vector<Message *> unprocessed_message_stack;
    public:

        Node(const string &name, int id, int type) : process(name) {
            this->id                  = id;
            this->type                = type;
            this->delay_acum          = 0;
            this->num_messages_sended = 0;
        }
        ~Node() { }
        int GetId();
        string GetIdString();
        int GetType();
        int GetIsp();
        void SetIsp(int);
        double GetIspDelay(int isp_from, int id_to, int type_to);
        void SetTransport(handle<Transport> *transport);
        int GetHoldTimeBeforeSendMessage();
        unsigned int GetNumMessagesSended(){
            return this->num_messages_sended;
        }
        void SumDelayAcum(double delay){
            this->delay_acum += delay;
            this->num_messages_sended++;
        }
        virtual void AddMessage(Message *message) {
            message_stack.push_back(message);
        }
        double SendMessage(Message *message);
        virtual void inner_body(void) = 0;
};

#endif