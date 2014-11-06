#include "Client.h"
#include "Constants.h"
#include "Dns.h"

#include <iostream>
#include <iomanip>
using namespace std;

void Client::inner_body(void) {
    int edge_server_to;
    double delay;
    cout << fixed << setprecision(4);
    while (1) {
        while (!message_stack.empty()) {
            Message * message = message_stack.back();
            SumDelayAcum( time() - message->GetCreationTime() );
            message_stack.pop_back();
            if (message->GetTypeFrom() == NODE_EDGE_SERVER) {
                int id_message = -1;
                for (int id = 0; id < unprocessed_message_stack.size(); ++id) {
                    if (unprocessed_message_stack.at(id)->GetMessagePointer()->getQuery() == message->GetMessagePointer()->getQuery()) {
                        id_message = id;
                        break;
                    }
                }
                Message * original = unprocessed_message_stack.at(id_message);
                unprocessed_message_stack.erase(unprocessed_message_stack.begin() + id_message);
            }
        }

        if ( ! message_wse_stack.empty() ) {
            MessageWSE * message_wse = message_wse_stack.back();
            message_wse_stack.pop_back();

            Message * message = new Message(this->GetId(), NODE_CLIENT, this->GetEdgeServerId(), NODE_EDGE_SERVER, time(), message_wse);
            delay = this->SendMessage(message);
            unprocessed_message_stack.push_back(message);
        }

#ifdef USERS_GENERATE_QUERYS
        double sleep = arrival_time->value();
        sleep = sleep > delay ? sleep : delay;
        // cout << "Sleep: " << sleep << " - " << delay << endl;

        hold(sleep);
#else
        this->passivate();
#endif
    }
}

void Client::HaveToSendAMessage() {
    if (this->idle())
        this->activate();
}

int Client::GetEdgeServerId() {
    this->number_of_messages_sended_to_dns++;
    // return this->dns->GetEdgeServerId((arrival_time->value() * 3));
    return this->dns->GetEdgeServerId(this->GetId());
}

int Client::GetNumberOfMessagesSendedToDns() {
    return this->number_of_messages_sended_to_dns;
}

void Client::ResetCycle() {
    this->number_of_querys_sended_this_cycle = 0;
}

int Client::GetNumberOfQuerysSendedThisCycle() {
    return number_of_querys_sended_this_cycle;
}

void Client::AddMessageWse(MessageWSE * message_wse) {
    this->message_wse_stack.push_back(message_wse);
}

double Client::SendMessage(Message * message){
    this->querys_sended++;
    this->number_of_querys_sended_this_cycle++;
    Node::SendMessage(message);
}

unsigned int Client::GetQuerysSended(){
    return this->querys_sended;
}