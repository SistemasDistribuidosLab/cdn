#include "Transport.h"
#include "EdgeServer.h"

void Transport::SendMessage(Message *message) {
    //cout << "Transporte -> ";
    
    handle<EdgeServer> edge_server = edge_servers[ message->GetIdTo() ];
    if (edge_server->idle()) {
        edge_server->activate();
    }
    edge_server->AddMessage(message);

}