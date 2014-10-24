#include <iostream>
#include "EdgeServer.h"
#include "Client.h"

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
        while(!message_stack.empty()){
            time_aux = time();
            Message * message = message_stack.back();
            message_stack.pop_back();
            // cout << time() << " - Edge Server " << this->GetId() << ": Mensaje Enviado en tiempo " << message->GetCreationTime() << " desde el cliente " << message->GetIdFrom() << ": " << message->GetMessage() << endl;
            received_querys_from_count[ message->GetIdFrom() ]++;
            processed_querys++;
            hold(processing_time_per_query);
            busy_time += time() - time_aux;

            string * respuesta = new string("respuestaaaaa !!!!!!!");
            this->SendMessage(new Message(this->GetId(), this->GetType(), message->GetIdFrom(), message->GetTypeFrom(), message->GetCreationTime(), respuesta));
        }
        // ===== BUSY TIME END =====

        time_aux = time();
        this->passivate();
        idle_time += time() - time_aux;
    }
}