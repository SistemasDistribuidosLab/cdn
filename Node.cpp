#include "Node.h"
#include "Transport.h"

int Node::GetId() {
    return this->id;
}
string Node::GetIdString() {
    return "Hola";
    // return IntToString(this->id);
}
int Node::GetType() {
    return type;
}

void Node::SetTransport(handle<Transport> *transport) {
    this->transport = transport;
}

double Node::GetIspDelay(int isp_from, int id_to, int type_to) {
    return (*transport)->GetIspDelay(isp_from, id_to, type_to);
}

double Node::SendMessage(Message *message) {
    this->num_messages_sended++;
    double delay = this->GetIspDelay(this->GetIsp(), message->GetIdTo(), message->GetTypeTo());
    (*transport)->AddMessage(message);
    if ((*transport)->idle()) {
        (*transport)->activate();
    }
    return delay;
}

int Node::GetIsp() {
    return this->isp;
}

void Node::SetIsp(int isp) {
    // cout << "Mi id es: " << this->id << " y tengo el isp: " << isp << endl;
    this->isp = isp;
}

void Node::AddMessage(Message *message) {
    this->num_messages_received++;
    message_stack.push_back(message);
}

void Node::SumDelayAcum(double delay){
    this->delay_acum += delay;
    this->num_messages_sended++;
}
