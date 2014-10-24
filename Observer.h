#ifndef _OBSERVER_h
#define _OBSERVER_h

#include "glob.h"
#include "cppsim.hh"

// class RedTubo;
// class TlcProtocol;

class Observer: public process{
    private:
        string s;
        double TRed, TCPU;
        double iter;

        int miss;
        int hitLocal;
        int hitGlobal;
        int hitLCache;

        int nqueriesIn;
        int nqueriesOut;
        int np;

        int hops;
        double latencia;
        double deltaT;
        bool busy, ends;

        int nReplicas;
        int iteracion;

        // handle< RedTubo                 > * transport;
        // vector< handle< TlcProtocol > * > Peers;
        vector< int                     > load;

    public:

        ~Observer(){

        }

        Observer(int _np, const string &name): process(name){
            TRed = 0.0; TCPU = 0.0;
            iter = 0.0;

            np = _np;
            miss = 0;
            hitLocal = 0;
            hitGlobal = 0;
            hitLCache = 0;
            nqueriesIn = 0;
            nqueriesOut = 0;
            hops = 0;
            latencia = 0.0;
            deltaT = 0.1;
            ends = false;
            busy = false;
            nReplicas = 0;
            iteracion = 0;

            for (int i = 0; i < np ; i++){
                load.push_back(0);
            }

        }

        // void setPeer(handle<TlcProtocol> *p){ // ============================
        //     Peers.push_back(p);
        // }
        // void setTransport(  handle<RedTubo> *_transport ) // ============================
        // {
        //     transport = _transport;
        // }

        void inner_body( void );

        void addMiss()
        {
            miss++;
        }

        bool isBusy()
        {
            return busy;
        }

        void setBusy(bool p)
        {
            busy = p;
        }

        void addHitLocal()
        {
            hitLocal++;
        }

        void addHitGlobal()
        {
            hitGlobal++;
        }

        void addHitLCache()
        {
            hitLCache++;
        }

        void addReplicas()
        {
            nReplicas++;
        }

        void addNQueriesIn()
        {
            nqueriesIn++;
        }

        void addNQueriesOut()
        {
            nqueriesOut++;
        }

        void addHops(int h)
        {
            hops = hops + h;
        }

        void addLatencia(double t)
        {
            latencia = latencia + t;
        }
        void end()
        {
            ends = true;
        }

        void print()
        {
            cout << s << endl;
        }

        void addLoad(int ip)
        {
            load[ip]++;
        }

        double getGini();

        int getIteracion();
};

#endif
