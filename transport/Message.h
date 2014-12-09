#ifndef MESSAGE
#define MESSAGE value

#include <string>
#include <cstdlib>
#include "../wse/MessageWSE.h"

using namespace std;

class Message {
    private:
        // from
        int id_from;
        int type_from;
        int id_unique_from;

        // to
        int id_to;
        int type_to;
        int id_unique_to;

        double creation_time;
        int * count_pointer;
        MessageWSE * message;
        unsigned long int id;
        static unsigned long int instances;
    public:
        /**
          *
          * - id_from: id del creador del mensaje.
          * - type_from: tipo del creador del mensaje.
          * - id_to: id del receptor del mensaje.
          * - type_to: tipo del receptor del mensaje.
          * - creation_time: cuando se crea el mensaje, esta variable se llama como time().
          * - message: Mensaje generado por gen_rnd (de tipo MessageWSE *) que contiene los datos
          *            necesarios para conocer la consulta y poder manejar un cache con ésta.
          * - 
          *
          **/
        Message(int id_from, int type_from, int id_to, int type_to, double creation_time, MessageWSE * message) {
            this->message = message;

            this->id_from = id_from;
            this->type_from = type_from;

            this->id_to = id_to;
            this->type_to = type_to;

            this->creation_time = creation_time;

            // Asigno un identificador único basado en el número de instancias
            // (Ej. de los valores que tomará: 0, 1, 2, 3, 4, 5, ...)
            this->id = Message::instances;
            Message::instances++;
        }
        
        Message(int id_unique_from, int id_unique_to, double creation_time, MessageWSE * message){
            this->id_unique_from = id_unique_from;
            
            this->id_unique_to   = id_unique_to;
            
            this->creation_time = creation_time;

            Message::instances++;
        }
        virtual ~Message() {
            free(message);
        }
        MessageWSE GetMessage(){ return * message; }
        inline MessageWSE * GetMessagePointer(){ return message; }
        int GetTypeFrom(){ return type_from; }
        int GetTypeTo(){ return type_to; }
        int GetIdFrom(){ return id_from; };
        int GetIdTo(){ return id_to; };
        int * GetCountPointer(){ return count_pointer; };
        double GetCreationTime(){ return creation_time ; }
        unsigned long int GetId(){ return this->id; }
};

#endif