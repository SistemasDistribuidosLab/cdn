#ifndef STATS
#define STATS

#include "cppsim.hh"
#include "Constants.h"

class EdgeServer;

class Stats : public process {
    private:
        ofstream * output;
        handle<EdgeServer> * edge_servers;
        static unsigned int cycles;
        ofstream * received_querys_by_edge_servers;
        ofstream cache_hits_by_edge_servers;
        int DURACION_SIMULACION;
    public:
        Stats(const string &name, int DURACION_SIMULACION, handle<EdgeServer> * edge_servers) : process(name) {
            this->output = output;
            this->edge_servers = edge_servers;
            this->DURACION_SIMULACION = DURACION_SIMULACION;
            
            received_querys_by_edge_servers = new ofstream();
            received_querys_by_edge_servers->open("charts/received_querys_by_edge_servers");

            /*    Cache Hits File */
            cache_hits_by_edge_servers.open("charts/cache_hits_by_edge_servers");
            /*// Cache Hits File */
        }
        ~Stats() {

        }
        void inner_body();
        unsigned int GetCycles() {
            return this->cycles;
        }
        void CloseAll() {
            received_querys_by_edge_servers->close();
            cache_hits_by_edge_servers.close();

            ofstream comandos;
            comandos.open("charts/comandos");

            /*   Received Queries by Edge Servers Commands (Doesn't Include Total)*/
            comandos << "Received Queries By Edge Servers (Doesn't Include Total):" << endl;;
            comandos << "set title 'Received Queries By Edge Servers';";
            comandos << "set xlabel 'Time';";
            comandos << "set ylabel 'Received Queries';";
            comandos << "plot ";
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                comandos << "'charts/received_querys_by_edge_servers' using 1:" << (i + 2) << " with lines title \"EdgeServer " << i << "\", ";
            }
            /*-- Received Queries by Edge Servers Commands */
            comandos << endl;
            comandos << endl;

            /*   Received Queries by Edge Servers Commands (Include Total)*/
            comandos << "Received Queries By Edge Servers (Include Total):" << endl;;
            comandos << "set title 'Received Queries By Edge Servers';";
            comandos << "set xlabel 'Time';";
            comandos << "set ylabel 'Received Queries';";
            comandos << "plot ";
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                comandos << "'charts/received_querys_by_edge_servers' using 1:" << (i + 2) << " with lines title \"EdgeServer " << i << "\", ";
            }
            comandos << "'charts/received_querys_by_edge_servers' using 1:" << (NUM_EDGE_SERVERS + 2) << " with lines title \"Total\", ";
            /*-- Received Queries by Edge Servers Commands */
            comandos << endl;
            comandos << endl;

            /*    Cache Hits Commands */
            comandos << "Cache Hits By Edge Servers:" << endl;
            comandos << "set title 'Cache Hits By Edge Servers';";
            comandos << "set xlabel 'Time';";
            comandos << "set ylabel 'Cache Hits';";
            comandos << "plot ";
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i)
            {
                comandos << "'charts/cache_hits_by_edge_servers' using 1:" << (i+2) << " with lines title \"EdgeServer " << i << "\", ";
            }
            /* // Cache Hits Commands */
        }

};

#endif
