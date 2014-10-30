#ifndef WSE_H
#define WSE_H

#include "../glob.h"
#include "../Node.h"
#include "MessageWSE.h"
#include "LruA.h"
#include "../Constants.h"

//#define WSECACHESIZE 8000

class WSE: public Node {

    private:
        // ID_PAGE , (TTL, VERSION)
        //   map<int*, pair<long int,int> > answers;

        list<MessageWSE *> queue_in;

        bool busy;
        LRUA *ANSWERS;
    public:
        WSE ( const string &name ): Node ( name, 0, NODE_ORIGIN_SERVER ) {
            busy = false;
            int cacheSize = WSECACHESIZE;
            ANSWERS = new LRUA(&cacheSize);
        }

        ~WSE() {
            //  answers.clear();
            delete ANSWERS;
        }


        void inner_body ( void );

        void add_request ( MessageWSE *bn ) {
            queue_in.push_back(bn);
        }

        bool get_busy() {
            return busy;
        }

        void print() {
            cout << "WSE" << endl;
        }

        long int getTTL(int *);
        //int getVersion(int*);
        int getVersion(string, int *);
        long int randomTTL();
};


#endif