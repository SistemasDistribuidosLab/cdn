#include <iostream>
#include "EdgeServer.h"
#include "Client.h"

using namespace std;

double EdgeServer::GetIdleTime() {
    return this->idle_time;
}
double EdgeServer::GetBusyTime() {
    return this->busy_time;
}
double EdgeServer::GetProcessedQuerys() {
    return this->processed_querys;
}
int EdgeServer::GetQuerysByClient(int j) {
    return received_querys_from_count[ j ];
}