#include "Client.h"
#include "Constants.h"

#include <iostream>
#include <iomanip>
using namespace std;

void Client::inner_body(void) {
    int edge_server_to;
    cout << fixed << setprecision(4);
    while (1) {

        while(!message_stack.empty()){
            Message * message = message_stack.back();
            cout << time() << " - Cliente " << setw(3) << this->GetId() << ": recibi respuesta a mi consulta " << message->GetMessage() << " enviada en tiempo " << message->GetCreationTime() << " hacia el servidor " << message->GetIdFrom() << endl;
            message_stack.pop_back();
            // string * respuesta = new string("respuestaaaaa !!!!!!!");
            // this->SendMessage(new Message(this->GetId(), this->GetType(), message->GetIdFrom(), message->GetTypeFrom(), time(), respuesta));
        }

        double sleep = arrival_time->value();
        // cout << this->GetId() << "Dormire por: " << sleep << endl  ;
        string *message_str = new string();
        *message_str = "Hola desde ";
        *message_str +=  this->GetIdString();

        // edge_server_to = this->GetEdgeServer();
        edge_server_to = 0;
        this->SendMessage(new Message(this->GetId(), NODE_CLIENT, edge_server_to, NODE_EDGE_SERVER, time(), message_str));


        hold(sleep);
    }
}