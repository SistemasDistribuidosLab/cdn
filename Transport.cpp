#include "Constants.h"
#include "Transport.h"
#include "Client.h"
#include "EdgeServer.h"

void Transport::AddMessage(Message *message) {
    this->message_stack.push_back(message);
}

void Transport::SetEdgeServers(handle<EdgeServer> *edge_servers) {
    this->edge_servers = edge_servers;
}
void Transport::SetClients(handle<Client> *clients) {
    this->clients = clients;
}

// Node *servidor;

//     cout << "Nuevo mensaje: " << message->GetIdFrom() << " para " << message->GetIdTo() << endl;

//     switch (message->GetTypeTo()) {
//     case NODE_CLIENT:
//         cout << "Asigne clientes " << clients[0]->GetId() << endl;
//         break;
//     case NODE_EDGE_SERVER:
//         cout << "Edgeeeeeeeeeeee" << endl;
//         servidor = edge_servers[ message->GetIdTo() ];
//         break;
//     case NODE_ORIGIN_SERVER:
//         cout << "Origiiiiiiiiiim" << endl;
//         break;
//     }

//     // handle<EdgeServer> edge_server = edge_servers[ message->GetIdTo() ];
//     servidor->AddMessage(message);
//     if (servidor->idle()) {
//         servidor->activate();
//     }

void Transport::inner_body(void) {
    while (1) {
        // ===== BUSY TIME START =====
        // time_aux = time();
        while(!message_stack.empty()){
            Message * message = message_stack.back();
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
        	hold(0.001);
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