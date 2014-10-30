#include <iostream>
#include "EdgeServer.h"
#include "Client.h"
#include "wse/MessageWSE.h"

using namespace std;

double EdgeServer::GetIdleTime() {
    return this->idle_time;
}
double EdgeServer::GetBusyTime() {
    return this->busy_time;
}
double EdgeServer::GetProcessedQuerys() {
    return this->processed_querys;
}
int EdgeServer::GetQuerysByClient(int j) {
    return received_querys_from_count[ j ];
}

void EdgeServer::inner_body(void) {
    double time_aux;
    double processing_time_per_query = 0.01;
    // cout << fixed << setprecision(4);
    while (1) {
        // ===== BUSY TIME START =====
        while (!message_stack.empty()) {
            time_aux = time();
            Message *message = message_stack.back();
            message_stack.pop_back();
            // cout << time() << " - Edge Server " << this->GetId() << ": Mensaje Enviado en tiempo " << message->GetCreationTime() << " desde el cliente " << message->GetIdFrom() << ": " << message->GetMessage() << endl;
            received_querys_from_count[ message->GetIdFrom() ]++;
            processed_querys++;
            hold(processing_time_per_query);
            busy_time += time() - time_aux;

            if (message->GetTypeFrom() == NODE_CLIENT) {
                this->unprocessed_message_stack.push_back(message);
                this->SendMessage(new Message(this->GetId(), this->GetType(), 0,
                                              NODE_ORIGIN_SERVER, message->GetCreationTime(), message->GetMessagePointer()));
            } else if (message->GetTypeFrom() == NODE_ORIGIN_SERVER) {
                int id_message = -1;
                for (int id = 0; id < unprocessed_message_stack.size(); ++id) {
                    if (unprocessed_message_stack.at(id)->GetMessagePointer() == message->GetMessagePointer()) {
                        id_message = id;
                        break;
                    }
                }
                Message * original = unprocessed_message_stack.at(id_message);
                unprocessed_message_stack.erase(unprocessed_message_stack.begin() + id_message);
                this->SendMessage(new Message(this->GetId(), this->GetType(), 
                    original->GetIdFrom(), original->GetTypeFrom(), time(), original->GetMessagePointer()));
            }
        }
        // ===== BUSY TIME END =====

        time_aux = time();
        this->passivate();
        idle_time += time() - time_aux;
    }
}