#include "Constants.h"
#include "Transport.h"
#include "Client.h"
#include "EdgeServer.h"

double Transport::isps[3][3];

void Transport::AddMessage(Message *message) {
    this->message_stack.push_back(message);
}

void Transport::SetIsps(double ptr_isps[][3]) {
    // isps = ptr_isps;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            isps[ i ][ j ] = ptr_isps[ i ][ j ];
        }
    }
}

void Transport::SetEdgeServers(handle<EdgeServer> *edge_servers) {
    this->edge_servers = edge_servers;
}
void Transport::SetClients(handle<Client> *clients) {
    this->clients = clients;
}

Node *Transport::GetServer(int id, int type) {
    if (type == NODE_CLIENT)
        return clients[ id ];
    if (type == NODE_EDGE_SERVER)
        return edge_servers[ id ];
    if (type == NODE_ORIGIN_SERVER)
        return NULL;
    return NULL;
}

int Transport::GetNumOfServers(int type) {
    if (type == NODE_CLIENT)
        return NUM_CLIENTS;
    if (type == NODE_EDGE_SERVER)
        return NUM_EDGE_SERVERS;
    if (type == NODE_ORIGIN_SERVER)
        return 0;
    return 0;
}

void Transport::inner_body(void) {
    while (1) {
        // ===== BUSY TIME START =====
        // time_aux = time();
        while (!message_stack.empty()) {
            Message *message = message_stack.back();
            message_stack.pop_back();
            // cout << time() << " - Transporte " << this->GetId() << ": Mensaje Enviado en tiempo " << message->GetCreationTime() << " desde el cliente " << message->GetIdFrom() << ": " << message->GetMessage() << endl;
            Node *servidor;
            switch (message->GetTypeTo()) {
            case NODE_CLIENT:
                servidor = clients[ message->GetIdTo() ];
                break;
            case NODE_EDGE_SERVER:
                servidor = edge_servers[ message->GetIdTo() ];
                break;
            case NODE_ORIGIN_SERVER:
                cout << "Origiiiiiiiiiim" << endl;
                break;
            }

            // handle<EdgeServer> edge_server = edge_servers[ message->GetIdTo() ];
            servidor->AddMessage(message);
            // hold(0.001);
            if (servidor->idle()) {
                servidor->activate();
            }
        }
        // busy_time += time() - time_aux;
        // ===== BUSY TIME END =====

        // time_aux = time();
        this->passivate();
        // idle_time += time() - time_aux;
    }
}