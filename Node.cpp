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

void Node::SetTransport(handle<Transport> * transport) {
    this->transport = transport;
}

void Node::SendMessage(Message *message) {
    (*transport)->AddMessage(message);
}