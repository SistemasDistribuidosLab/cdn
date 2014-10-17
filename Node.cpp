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

void Node::SendMessage(Message *message) {
    (*transport)->AddMessage(message);
    if ((*transport)->idle()) {
        (*transport)->activate();
    }
}

int Node::GetIsp() {
    return this->isp;
}

void Node::SetIsp(int isp) {
	// cout << "Mi id es: " << this->id << " y tengo el isp: " << isp << endl;
    this->isp = isp;
}