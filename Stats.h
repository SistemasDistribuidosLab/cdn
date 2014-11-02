#ifndef STATS
#define STATS

#include "cppsim.hh"

class EdgeServer;

class Stats : public process {
    private:
        ofstream * output;
        handle<EdgeServer> * edge_servers;
        static unsigned int cycles;
        ofstream * received_querys_by_edge_servers;
    public:
        Stats(const string &name, handle<EdgeServer> * edge_servers) : process(name) {
            this->output = output;
            this->edge_servers = edge_servers;
            received_querys_by_edge_servers = new ofstream();
            received_querys_by_edge_servers->open("charts/received_querys_by_edge_servers");
        }
        ~Stats() {

        }
        void inner_body();
        unsigned int GetCycles() {
            return this->cycles;
        }
        void CloseAll() {
            received_querys_by_edge_servers->close();
        }

};

#endif