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
    // cout << fixed << setprecision(4);
    while (1) {
        // ===== BUSY TIME START =====
        time_aux = time();
        for (int i = 0; i < message_stack.size(); ++i) {
            //cout << time() << " - Edge Server " << this->GetId() << ": Mensaje Enviado en tiempo " << message_stack.at(i)->GetCreationTime() << " desde el cliente " << message_stack.at(i)->GetIdFrom() << ": " << message_stack.at(i)->GetMessage() << endl;
            received_querys_from_count[ message_stack.at(i)->GetIdFrom() ]++;
            processed_querys++;
            hold(0.001);
            //fflush(stdout);
        }
        hold(0.001);
        busy_time += time() - time_aux;
        // ===== BUSY TIME END =====

        time_aux = time();
        this->passivate();
        idle_time += time() - time_aux;
    }
}