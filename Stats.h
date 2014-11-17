#ifndef STATS
#define STATS

#include "cppsim.hh"
#include "Constants.h"
#include "Dns.h"

class EdgeServer;

class Stats : public process {
    private:
        handle<EdgeServer> * edge_servers;
        static unsigned int cycles;
        ofstream * received_querys_by_edge_servers;
        ofstream cache_hits_by_edge_servers;
        ofstream cache_usage_stream;
        int DURACION_SIMULACION;
        Dns * dns;
        int TIME_WINDOW;
    public:
        Stats(const string &name, int DURACION_SIMULACION, handle<EdgeServer> * edge_servers, Dns * dns, int TIME_WINDOW) : process(name) {
            this->edge_servers        = edge_servers;
            this->dns                 = dns;
            this->DURACION_SIMULACION = DURACION_SIMULACION;
            this->TIME_WINDOW         = TIME_WINDOW;
            
            received_querys_by_edge_servers = new ofstream();
            received_querys_by_edge_servers->open("charts/received_querys_by_edge_servers");


            /*    Cache Hits File */
            cache_hits_by_edge_servers.open("charts/cache_hits_by_edge_servers");
            cache_usage_stream.open("charts/cache_usage");
            /*// Cache Hits File */
            this->GenerateCommands();
        }
        ~Stats() {

        }
        void inner_body();
        unsigned int GetCycles() {
            return this->cycles;
        }
        void GenerateCommands(){
            ofstream comandos;
            comandos.open("charts/comandos");

            /*   Received Queries by Edge Servers Commands (Doesn't Include Total)*/
            comandos << "Received Queries By Edge Servers:" << endl;;
            comandos << "set title 'Received Queries By Edge Servers';";
            comandos << "set xlabel 'Time';";
            comandos << "set ylabel '#Received Queries / second';";
            comandos << "plot ";
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                comandos << "'charts/received_querys_by_edge_servers' using 1:" << (i + 2) << " with lines title \"EdgeServer " << i << "\", ";
            }
            /*-- Received Queries by Edge Servers Commands */
            comandos << endl;
            comandos << endl;

            /*    Cache Hits Commands */
            comandos << "Cache Hits By Edge Servers:" << endl;
            comandos << "set title 'Cache Hits By Edge Servers';";
            comandos << "set xlabel 'Time';";
            comandos << "set ylabel 'Cache Hits / second';";
            comandos << "plot ";
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i)
            {
                comandos << "'charts/cache_hits_by_edge_servers' using 1:" << (i+2) << " with lines title \"EdgeServer " << i << "\", ";
            }
            /* // Cache Hits Commands */
        }
        void CloseAll() {
            received_querys_by_edge_servers->close();
            cache_hits_by_edge_servers.close();
            cache_usage_stream.close();
        }

};

#endif
