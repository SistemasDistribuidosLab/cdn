#include "Node.h"

Node::Node(int id, int type){
	this->id = id;
	this->type = type;
}

Node::~Node(){
}

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