#ifndef MIDNS
#define MIDNS

#include "Constants.h"

class MIDNS {
    public:
        MIDNS(){}
        ~MIDNS(){}
        int Get(int id){
        	return id % NUM_EDGE_SERVERS;
        }
};

#endif