#ifndef STATS
#define STATS

#include "cppsim.hh"

class EdgeServer;

class Stats : public process {
    private:
        ofstream * output;
        handle<EdgeServer> * edge_servers;
        static unsigned int cycles;
    public:
        Stats(const string &name, ofstream * output, handle<EdgeServer> * edge_servers) : process(name) {
            this->output = output;
            this->edge_servers = edge_servers;
        }
        ~Stats() {

        }
        void inner_body();
        unsigned int GetCycles() {
            return this->cycles;
        }

};

#endif