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
            Message * message = this->GetMessage();

            // cout << time() << " - Edge Server " << this->GetId() << ": Mensaje Enviado en tiempo " << message->GetCreationTime() << " desde el cliente " << message->GetIdFrom() << ": " << message->GetMessage() << endl;
            hold(processing_time_per_query);

            this->SumToBusyTime( time() - time_aux );

            if (message->GetTypeFrom() == NODE_CLIENT) {
                this->ReceiveANewMessageFromClient( message->GetIdFrom() );

                this->AddANewUnprocessedMessage(message);

                this->SendMessage(new Message(this->GetId(), this->GetType(), 0,
                                              NODE_ORIGIN_SERVER, message->GetCreationTime(), message->GetMessagePointer()));
                this->SumToProcessedQuerys(1);
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
        this->SumToIdleTime( time() - time_aux );
    }
}

void EdgeServer::SumToIdleTime(double add_time) {
    this->idle_time += add_time;
}

void EdgeServer::SumToBusyTime(double add_time) {
    this->busy_time += add_time;
}

void EdgeServer::SumToProcessedQuerys(int add_value) {
    this->processed_querys += add_value;
}

void EdgeServer::ReceiveANewMessageFromClient(int id_from) {
    this->received_querys_from_count[ id_from ]++;
}

void EdgeServer::AddANewUnprocessedMessage(Message * message) {
    this->unprocessed_message_stack.push_back(message);
}

Message * EdgeServer::GetMessage() {
    Message * message = this->message_stack.back();
    this->message_stack.pop_back();
    return message;
}