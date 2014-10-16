#include "cppsim.hh"
#include "Client.h"
#include "EdgeServer.h"

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int NUM_CLIENTS;
int NUM_EDGE_SERVERS;
int DURACION_SIMULACION;
int ARRIVAL_TIME;

class Simulation : public process {
    public:
        Simulation(const string &name) : process(name) { }
        ~Simulation() { }
        void inner_body() {

        }

};

void GenerateGraph();

int main(int argc, char const *argv[]) {
    NUM_CLIENTS = argc > 1 ? atoi(argv[1]) : 30;

    NUM_EDGE_SERVERS = argc > 2 ? atoi(argv[2]) : 10;

    DURACION_SIMULACION = argc > 3 ? atoi(argv[3]) : 10;

    ARRIVAL_TIME = argc > 4 ? atoi(argv[4]) : 10;

    cout << "NUM_CLIENTS:         " << NUM_CLIENTS << endl;
    cout << "NUM_EDGE_SERVERS:    " << NUM_EDGE_SERVERS << endl;
    cout << "DURACION_SIMULACION: " << DURACION_SIMULACION << endl;

    simulation *sim = simulation::instance();
    sim->begin_simulation( new sqsDll() );

    handle<Simulation> simulation_handle = new Simulation( "source" );
    simulation_handle->activate();

    sim->run();
    sim->end_simulation();

    return 0;
}