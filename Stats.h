#ifndef STATS
#define STATS

#include "cppsim.hh"
#include "Constants.h"

class EdgeServer;

class Stats : public process
{
private:
    ofstream *output;
    handle<EdgeServer> *edge_servers;
    static unsigned int cycles;
    ofstream *received_querys_by_edge_servers;
    ofstream cache_hits_by_edge_servers;
    int DURACION_SIMULACION;
    unsigned int total_cache_hits_by_edge_servers = 0;
public:
    Stats(const string &name, int DURACION_SIMULACION, handle<EdgeServer> *edge_servers) : process(name)
    {
        this->DURACION_SIMULACION = DURACION_SIMULACION;
        this->edge_servers = edge_servers;
        received_querys_by_edge_servers = new ofstream();
        received_querys_by_edge_servers->open("charts/received_querys_by_edge_servers");

        /*    Cache Hits File */
        cache_hits_by_edge_servers.open("charts/cache_hits_by_edge_servers");
        /*// Cache Hits File */

        this->GenerateCommands();
    }
    ~Stats()
    {

    }
    void inner_body();
    unsigned int GetCycles()
    {
        return this->cycles;
    }
    void CloseAll()
    {
        received_querys_by_edge_servers->close();
        cache_hits_by_edge_servers.close();
        cout << "========================================= Cache Hits: " << total_cache_hits_by_edge_servers << endl;
    }

    void GenerateCommands(){
        ofstream comandos;
        comandos.open("charts/comandos");

        comandos << "Received Queries By Edge Servers:" << endl;;
        comandos << "set title 'Received Queries By Edge Servers';";
        comandos << "set xlabel 'Time';";
        comandos << "set ylabel 'Received Queries';";
        comandos << "plot ";
        for (int i = 0; i < NUM_EDGE_SERVERS; ++i)
        {
            comandos << "'charts/received_querys_by_edge_servers' using 1:" << (i + 2) << " with lines title \"EdgeServer " << i << "\", ";
        }
        comandos << "'charts/received_querys_by_edge_servers' using 1:" << (NUM_EDGE_SERVERS + 2) << " with lines title \"Total\", ";
        comandos << endl;
        comandos << endl;

        /*    Cache Hits Commands */
        comandos << "Cache Hits By Edge Servers:" << endl;
        comandos << "set title 'Cache Hits By Edge Servers';";
        comandos << "set xlabel 'Time';";
        comandos << "set ylabel 'Cache Hits';";
        comandos << "plot [0:" << DURACION_SIMULACION << "] [0:100]";
        int aux = 0;
        for (int i = 0; i < NUM_EDGE_SERVERS; ++i)
        {
            comandos << "'charts/cache_hits_by_edge_servers' using 1:" << (i + 2) << " with lines title \"EdgeServer Hits" << i << "\", ";
            // comandos << "'charts/cache_hits_by_edge_servers' using 1:" << (aux + 2) << " with lines title \"EdgeServer Hits" << i << "\", ";
            // comandos << "'charts/cache_hits_by_edge_servers' using 1:" << (aux + 3) << " with linespoints title \"EdgeServer Miss" << i << "\", ";
            aux += 2;
        }
        /* // Cache Hits Commands */
    }

};

#endif