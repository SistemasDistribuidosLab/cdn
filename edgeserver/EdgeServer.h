#ifndef EDGE_SERVER
#define EDGE_SERVER

#include "../Node.h"
#include "../Constants.h"
#include "../wse/Lru.h"

using namespace std;

// class Client;
class MessageWSE;

class EdgeServer : public Node
{
private:
    double idle_time;
    double busy_time;
    unsigned int *received_querys_from_count;
    unsigned int received_queries_by_clients;
    unsigned int cache_hits_received_queries_by_clients;
    unsigned int cache_miss_received_queries_by_clients;
    unsigned int processed_queries;
    LRU *ANSWERS;
    vector<double> cache_hits_vector;
public:
    EdgeServer(const string &name, int id, int type, int WSECACHESIZE) : Node(name, id, type)
    {
        idle_time = 0;
        busy_time = 0;
        received_querys_from_count = new unsigned int[ NUM_CLIENTS ];
        for (int i = 0; i < NUM_CLIENTS; ++i)
        {
            received_querys_from_count[ i ] = 0;
        }

        this->received_queries_by_clients                  = 0;
        this->cache_hits_received_queries_by_clients       = 0;
        this->cache_miss_received_queries_by_clients       = 0;
        this->processed_queries                            = 0;

        int * cacheSize = new int(WSECACHESIZE);
        ANSWERS = new LRU(cacheSize);
        cache_hits_vector.push_back(0);
    }
    ~EdgeServer()
    {
        delete ANSWERS;
    }
    vector<double> GetCacheHitsVector(){
        return this->cache_hits_vector;
    }
    int GetUnprocessedMessageId(MessageWSE *);
    double GetIdleTime();
    double GetBusyTime();
    double GetProcessedQuerys();
    int GetQuerysByClient(int j);
    void inner_body(void);
    void SumToIdleTime(double);
    void SumToBusyTime(double);
    void SumToProcessedQuerys();
    void ReceiveANewMessageFromClient(int);
    Message *GetMessageFromMessageStack();
    void AddANewUnprocessedMessage(Message *);
    unsigned int GetReceivedQueriesByClients();
    int getVersion(string, int *);
    void AddANewCacheHit();
    void AddANewCacheMiss();
    long int getTTL(BIGNUM *);
    long int getTimeIncremental(long int);
    unsigned int GetCacheHitsReceivedQueriesByClients();
    unsigned int GetCacheMissReceivedQueriesByClients();
    void AddANewProcessedQuery();
    unsigned int GetProcessedQueries();
    int GetUsedCache(){
        return ANSWERS->GetUsedCache();
    }
};
#endif