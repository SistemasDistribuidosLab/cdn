#ifndef _MSG_WSE_H
#define _MSG_WSE_H

#include "../glob.h"
#include "ClientWSE.h"

// Message sent by WSE

class MessageWSE {

    public:

        handle<ClientWSE> *src;
        string key;
        int *query;

        int version;

        int source;//peer or user


        ~MessageWSE() {
            free( src);
            free(query);
            // BN_free(query);
        }

        MessageWSE(handle<ClientWSE> *_src,  int *_query, string _key, int _srcK) {
            src    = _src;
            // query  = BN_dup(_query);
            query = new int(*_query);
            key.assign(_key);
            source = _srcK;
        }

        string getKey() {
            return key;
        }
        int *getQuery() {
            return query;
        }

        void setAnswer(int _version) {
            version = version;
        }

        int getVersion() {
            return version;
        }

};


#endif
