#include "cppsim.hh"
#include "Constants.h"
#include "Transport.h"
#include "Client.h"
#include "EdgeServer.h"
#include "Funciones.h"

#include <vector>

using namespace std;

int NUM_CLIENTS;
int NUM_EDGE_SERVERS;
int DURACION_SIMULACION;
int ARRIVAL_TIME;

// vector< handle<Client> > clients;
handle<Client> *clients;
handle<EdgeServer> * edge_servers;

class Simulation : public process {
    public:
        Simulation(const string &name) : process(name) { }
        ~Simulation() { }
        void inner_body() {


            rng<double> *arrival_time;
            rng<double> *random_client;

            arrival_time = new rngExp( "Arrive Time", ARRIVAL_TIME );
            random_client = new rngUniform("SelectSource", 0, 100);

            // Iniciar Edge Servers
            edge_servers = new handle<EdgeServer>[NUM_EDGE_SERVERS];
            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                edge_servers[i] = new EdgeServer("edge_server", i, NODE_EDGE_SERVER);
            }

            // Iniciar Clientes
            clients = new handle<Client>[ NUM_CLIENTS ];
            for (int i = 0; i < NUM_CLIENTS; ++i) {
                clients[i] = new Client("cliente", i, NODE_CLIENT, arrival_time);
            }

            // Iniciar Transporte
            Transport * transport = new Transport();
            transport->SetEdgeServers(edge_servers);
            transport->SetClients(edge_servers);

            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                clients[i]->SetTransport(transport);
                edge_servers[i]->activate();
            }
            for (int i = 0; i < NUM_CLIENTS; ++i) {
                clients[i]->SetTransport(transport);
                clients[i]->activate();
            }

            hold(10);
            end_simulation( );
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