#ifndef MESSAGE
#define MESSAGE value

#include <string>
#include <cstdlib>

using namespace std;

class Message {
    private:
        string * message;

        // from
        int id_from;
        int type_from;

        // to
        int id_to;
        int type_to;

        double creation_time;
        int * count_pointer;
    public:
        Message(int id_from, int type_from, int id_to, int type_to, double creation_time, string * message) {
            this->message = message;

            this->id_from = id_from;
            this->type_from = type_from;

            this->id_to = id_to;
            this->type_to = type_to;

            this->creation_time = creation_time;
            this->count_pointer = count_pointer;
        }
        virtual ~Message() {
            free(message);
        }
        string GetMessage(){ return * message; }
        int GetTypeFrom(){ return type_from; }
        int GetTypeTo(){ return type_to; }
        int GetIdFrom(){ return id_from; };
        int GetIdTo(){ return id_to; };
        int * GetCountPointer(){ return count_pointer; };
        double GetCreationTime(){ return creation_time ; }
};

#endif