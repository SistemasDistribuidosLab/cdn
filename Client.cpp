#include "Client.h"
#include "Constants.h"

#include <iostream>
using namespace std;

void Client::inner_body(void) {
    int edge_server_to;
    while (1) {
        double sleep = arrival_time->value();
        cout << this->GetId() << "Dormire por: " << sleep << endl  ;
        string *message_str = new string();
        *message_str = "Hola desde ";
        *message_str +=  this->GetIdString();

        // edge_server_to = this->GetEdgeServer();
        edge_server_to = 0;
        this->SendMessage(new Message(this->GetId(), NODE_CLIENT, edge_server_to, NODE_EDGE_SERVER, time(), message_str));


        hold(sleep);
    }
}