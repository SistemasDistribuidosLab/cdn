#include "Observer.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Constants.h"

// #include "transportLayer/redtubo.h"

// #include "applicationLayer/TlcProtocol.h"

void Observer::inner_body(void)
{

    stringstream outStream;

    s = outStream.str();
    cout << outStream.str();
    fflush(stdout);

    while (1)
    {


        hold(DELTA_O);

        // compute statistics
        outStream.str("");

        double avHop = 0;
        double avLatency = 0;

        if (nqueriesIn > 0)
        {
            avHop = (double)hops / nqueriesIn;
            avLatency = (double)latencia / nqueriesIn;
        }
        //  else
        // {
        // avHop=-1;
        // avLatency-1;
        // }

        double gini = Observer::getGini();
        iteracion++;

        outStream << " time nQueriesOut nQueriesIn hitLocal hitGlobal hitLCache miss avHop nReplicas Gini avLatency" << endl;
        outStream << setw(5) << this->time() << " " << setw(11) << nqueriesOut << " " << setw(10) << nqueriesIn << " " << setw(8) << hitLocal ;
        outStream << " "  << setw(9) <<  hitGlobal << " " << setw(9) << hitLCache << " " ;
        outStream << setw(4) << miss << " " << setw(5) << avHop << " " << setw(9) << nReplicas;
        outStream << " " << setw(4) << gini << " " << setw(9) << avLatency << endl;

        s.append(outStream.str());
        cout << outStream.str();
        fflush(stdout);
        // limpia variables
        nqueriesIn = 0;
        nqueriesOut = 0;
        hitLocal = 0;
        hitGlobal = 0;
        hitLCache = 0;
        miss = 0;
        hops = 0;
        latencia = 0;
        nReplicas = 0;

        for (int i = 0; i < np; i++)
        {
            load[i] = 0;
        }

        double time = 0.0;
        double MaxT  = 0.0;

        // for ( int i = 0 ; i < (int)Peers.size() ; i ++)
        // {
        //     if ( MaxT < (*Peers[i])->getTrabajo() ) MaxT += (*Peers[i])->getTrabajo();
        //     if ( time < (*Peers[i])->getTime() ) time = (*Peers[i])->getTime();
        //     (*Peers[i])->resetTrabajo();
        // }
        // if ( time < (*transport)->getTime() ) time = (*transport)->getTime();
        // cout << "XXX Red: " << (*transport)->getTrabajo() << " "
             // << DELTA_O << " " << ((*transport)->getTrabajo()) / DELTA_O << endl;
        cout << "XXX CPU: " << MaxT << " " << DELTA_O << " " << MaxT / DELTA_O << endl;


        iter++;
        // TRed += ((*transport)->getTrabajo()) / DELTA_O;
        TCPU += MaxT / DELTA_O;
        cout << "ACUMULADO CPU: " << TCPU / iter << endl;
        cout << "ACUMULADOR RED: " << TRed / iter << endl;
        cout << endl;
        // (*transport)->resetTrabajo();

        // dormir
        if(ends){
            passivate();
        }
    }
}



double Observer::getGini()
{
    double l = 0;
    double gini = 0;
    double mean = 0;

    for (int i = 0; i < np ; i++){
        l = l + load[i];
    }

    mean = l / np;

    sort(load.begin(), load.end() );

    for (int i = 0; i < np; i++){
        int j = i + 1;
        gini = gini + (( 2 * j - ( np - 1 )) * load[i] );
    }

    if (mean > 0){
        gini = gini / (np * np * mean);
    }

    return gini;
}

int Observer::getIteracion(){
    return iteracion;
}


