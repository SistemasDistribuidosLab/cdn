#include "cppsim.hh"
#include "Constants.h"
#include "Dns.h"
#include "Transport.h"
#include "Client.h"
#include "EdgeServer.h"
#include "Funciones.h"
#include "prueba.h"

#include <vector>

using namespace std;

int NUM_CLIENTS;
int NUM_EDGE_SERVERS;
int DURACION_SIMULACION;
int ARRIVAL_TIME;

double isps[3][3] = {
    {0.1, 0.5, 0.5},
    {0.5, 0.1, 0.5},
    {0.5, 0.5, 0.1},
};

// vector< handle<Client> > clients;
handle<Client> *clients;
handle<EdgeServer> *edge_servers;

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
                edge_servers[ i ] = new EdgeServer("edge_server", i, NODE_EDGE_SERVER);
            }

            // Iniciar Clientes
            clients = new handle<Client>[ NUM_CLIENTS ];
            for (int i = 0; i < NUM_CLIENTS; ++i) {
                clients[ i ] = new Client("cliente", i, NODE_CLIENT, arrival_time);
            }

            // Iniciar Transporte
            handle<Transport> transport = new Transport("transporte", 0, 0);
            transport->SetClients(clients);
            transport->SetEdgeServers(edge_servers);
            Transport::SetIsps(isps);
            transport->activate();

            Dns *dns = new Dns();

            for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
                edge_servers[ i ]->SetTransport(&transport);
                edge_servers[ i ]->SetIsp( ((double)i / (double)NUM_EDGE_SERVERS) * NUM_ISP );
                edge_servers[ i ]->activate();
            }
            for (int i = 0; i < NUM_CLIENTS; ++i) {
                clients[ i ]->SetTransport(&transport);
                clients[ i ]->SetIsp( ((double)i / (double)NUM_CLIENTS) * NUM_ISP );
                clients[ i ]->SetDns(dns);
                clients[ i ]->activate();
            }

            hold(10);
            end_simulation( );
        }
};

void GenerateGraph();

int main(int argc, char const *argv[]) {
    NUM_CLIENTS = argc > 1 ? atoi(argv[1]) : 100;
    NUM_EDGE_SERVERS = argc > 2 ? atoi(argv[2]) : 5;
    DURACION_SIMULACION = argc > 3 ? atoi(argv[3]) : 100;
    ARRIVAL_TIME = argc > 4 ? atoi(argv[4]) : 1;

    cout << "NUM_CLIENTS:         " << NUM_CLIENTS << endl;
    cout << "NUM_EDGE_SERVERS:    " << NUM_EDGE_SERVERS << endl;
    cout << "DURACION_SIMULACION: " << DURACION_SIMULACION << endl;

    simulation *sim = simulation::instance();
    sim->begin_simulation( new sqsDll() );

    handle<Simulation> simulation_handle = new Simulation( "source" );
    simulation_handle->activate();

    sim->run();
    sim->end_simulation();

    cout << "Enf of Simulation" << endl;
    cout << "===== Statistics =====" << endl;
    cout << "Edge Servers:" << endl;
    double total_idle_time_percentage  = 0;
    double total_busy_time_percentage  = 0;

    streamsize default_precision = cout.precision();
    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        cout << fixed << setprecision(2);
        double idle_time = edge_servers[ i ]->GetIdleTime();
        double busy_time = edge_servers[ i ]->GetBusyTime();
        double total_time = idle_time + busy_time;

        double idle_time_percentage = total_time == 0 ? -1 : ( (idle_time / total_time) * 100 );
        double busy_time_percentage = total_time == 0 ? -1 : ( (busy_time / total_time) * 100 );

        total_idle_time_percentage += idle_time_percentage;
        total_busy_time_percentage += busy_time_percentage;
        cout << "\tEdge Server " << i << endl;
        cout << "\t\tIdle Percentage:  " << idle_time_percentage << " %" << endl;
        cout << "\t\tBusy Percentage:  " << busy_time_percentage << " %" << endl;
        cout << fixed << setprecision(0);
        cout << "\t\tProcessed Querys: " << edge_servers[ i ]->GetProcessedQuerys() << endl;
    }
    cout << endl;
    cout << "\tAverage Idle Percentage: " << ( (total_idle_time_percentage / NUM_EDGE_SERVERS) ) << "%" << endl;
    cout << "\tAverage Processing Time: " << ( (total_busy_time_percentage / NUM_EDGE_SERVERS) ) << "%" << endl;
    cout << endl;

    cout << "Clients:" << endl;

    // Total consultas enviadas
    unsigned int total_num_messages_sended = 0;
    for (int i = 0; i < NUM_CLIENTS; ++i) {
        total_num_messages_sended += clients[ i ]->GetNumMessagesSended();
    }
    cout << "\tTotal querys sended:   " << total_num_messages_sended << endl;
    cout << fixed << setprecision(2);
    cout << "\tAverage querys sended: " << (double)total_num_messages_sended / (double)NUM_CLIENTS << endl;

    GenerateGraph();

    return 0;
}

string GetColor(int, int);
string GetColorNode(int, int);

void GenerateGraph() {
    int total_edge_querys = 0;
    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        total_edge_querys += edge_servers[ i ]->GetProcessedQuerys();
    }

    ofstream grafo;
    grafo.open ("grafo.dot");
    grafo << "digraph G {" << endl;
    grafo << "\tsplines=false;" << endl;

    double alto = 0.3;
    double ancho = 0.3;
    string string_tamano = ",height=0.30, width=0.30, fixedsize=true,";

    for (int i = 0; i < NUM_CLIENTS; ++i) {
        grafo << "\tc" << i << "[shape=circle, color=lightblue,style=filled " << string_tamano << "];" << endl;
    }
    for (int i = 0; i < NUM_EDGE_SERVERS; ++i) {
        grafo << "\te" << i << "[shape=box, color=\"" << GetColorNode(edge_servers[ i ]->GetProcessedQuerys(), total_edge_querys) << "\",style=filled " << string_tamano << "];" << endl;
    }
    // grafo << "\tDNS[shape=box, color=orange,style=filled " << string_tamano << "];" << endl;


    int max_querys = 0;
    int total;
    int total_total = 0;
    int total_querys[ NUM_CLIENTS ];

    for (int i = 0; i < NUM_CLIENTS; ++i) {
        total = 0;
        for (int j = 0; j < NUM_EDGE_SERVERS; ++j) {
            total += edge_servers[ j ]->GetQuerysByClient(i);
        }
        if (total > max_querys)
            max_querys = total;
        total_querys[ i ] = total;
        total_total += total;
    }

    // Clients -> EdgeServers
    for (int i = 0; i < NUM_CLIENTS; ++i) {
        for (int j = 0; j < NUM_EDGE_SERVERS; ++j) {
            if (edge_servers[ j ]->GetQuerysByClient(i) > 0)
                grafo << "\t" << "\"c" << i << "\" -> \"e" << j << "\"[color=\"" << GetColor(edge_servers[ j ]->GetQuerysByClient(i), max_querys) << "\"];" << endl;
        }
    }

    // Clients -> DNS
    for (int i = 0; i < NUM_CLIENTS; ++i) {
        for (int j = 0; j < NUM_EDGE_SERVERS; ++j) {
            if (edge_servers[ j ]->GetQuerysByClient(i) > 0) {
                // grafo << "\t" << "\"c" << i << "\" -> \"DNS\"" << endl;
            }
        }
    }

    grafo << "}";
    grafo.close();
}

string GetColor(int querys, int total_querys) {
    // rdylgn11 color scheme
    // http://www.graphviz.org/doc/info/colors.html#brewer
    vector<string> colors;
    colors.push_back("#006837");
    colors.push_back("#1a9850");
    colors.push_back("#66bd63");
    colors.push_back("#a6d96a");
    colors.push_back("#d9ef8b");
    colors.push_back("#ffffbf");
    colors.push_back("#fee08b");
    colors.push_back("#fdae61");
    colors.push_back("#f46d43");
    colors.push_back("#d73027");
    colors.push_back("#a50026");
    // cout << querys << " / " << total_querys << endl;
    // cout << ((double)querys / (double)total_querys * 10) << endl;
    return colors.at( ((double)querys / (double)total_querys * (colors.size() - 1 ) ) );
}

string GetColorNode(int querys, int total_querys) {
    // rdylgn11 color scheme
    // http://www.graphviz.org/doc/info/colors.html#brewer
    vector<string> colors;
    colors.push_back("#edf8fb");
    colors.push_back("#b3cde3");
    colors.push_back("#8c96c6");
    colors.push_back("#8856a7");
    colors.push_back("#810f7c");
    if (total_querys == 0)
        return colors.at(0);
    // cout << querys << " / " << total_querys << endl;
    // cout << ((double)querys / (double)total_querys * 10) << endl;
    return colors.at( ((double)querys / (double)total_querys * (colors.size() - 1 ) ) );
}