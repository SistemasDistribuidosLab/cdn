#include <iostream>
#include "EdgeServer.h"
#include "Constants.h"
#include "Client.h"
#include "wse/MessageWSE.h"
#include "wse/Answer.h"
#include "wse/Lru.h"

using namespace std;

double EdgeServer::GetIdleTime()
{
    return this->idle_time;
}
double EdgeServer::GetBusyTime()
{
    return this->busy_time;
}
double EdgeServer::GetProcessedQuerys()
{
    return this->processed_querys;
}
int EdgeServer::GetQuerysByClient(int j)
{
    return received_querys_from_count[ j ];
}

void EdgeServer::inner_body(void)
{
    double time_aux;
    double processing_time_per_query = 0.01;
    int ttl;
    // cout << fixed << setprecision(4);
    while (1)
    {
        // ===== BUSY TIME START =====
        while (!message_stack.empty())
        {
            time_aux = time();
            Message *message = this->GetMessage();

            // cout << time() << " - Edge Server " << this->GetId() << ": Mensaje Enviado en tiempo " << message->GetCreationTime() << " desde el cliente " << message->GetIdFrom() << ": " << message->GetMessage() << endl;
            hold(processing_time_per_query);

            this->SumToBusyTime( time() - time_aux );

            MessageWSE *message_wse = message->GetMessagePointer();


            // cout << "=========================== " << time() << " ========================" << endl;
            int ttl;
            // if (message->GetTypeFrom() == NODE_ORIGIN_SERVER)
            // {
            //     cout << "WSE: ";
            // }
            // cout << message_wse->getKey() << endl;
            cout << "====================-------------------------------" << endl;
            cout << "Query: " << BN_bn2dec(message_wse->getQuery()) << endl;
            Entry *a = ANSWERS->check( message_wse->getQuery() );

            // lru_cache::const_iterator it = cache->find( message_wse->getQuery() );
            // lru_cache::const_iterator it = cache->mru_begin();
            // cache->find( message_wse->getQuery() );

            // if (it != cache->end())
            // {
            //     cout << "HIT" << endl;
            // }
            // if (a != NULL)
            //     cout << "Ttl: " << a->getTimeOut() << endl;
            if (message->GetTypeFrom() == NODE_CLIENT)
            {
                this->ReceiveANewMessageFromClient( message->GetIdFrom() );
                this->AddANewUnprocessedMessage(message);
                this->SumToProcessedQuerys();
                // cout << "A" << endl;
                if (a != NULL && a->old( time() ))
                {
                    // cout << "B" << endl;
                    ANSWERS->remove(a);
                    a = NULL;
                }
                if (a == NULL)
                {
                    // cout << "C" << endl;
                    this->AddANewCacheMiss();
                    // message_wse->setAnswer( a->getVersion() );
                    this->SendMessage(new Message(this->GetId(), this->GetType(), 0,
                                                  NODE_ORIGIN_SERVER, message->GetCreationTime(), message_wse));
                }
                else
                {
                    // cout << "D" << endl;
                    this->AddANewCacheHit();
                    this->SendMessage(new Message(this->GetId(), this->GetType(), message->GetIdFrom(),
                                                  message->GetTypeFrom(), message->GetCreationTime(), message_wse));
                }
            }

            else if (message->GetTypeFrom() == NODE_ORIGIN_SERVER)
            {
                int id_message = -1;
                for (int id = 0; id < unprocessed_message_stack.size(); ++id)
                {
                    if (unprocessed_message_stack.at(id)->GetMessagePointer() == message->GetMessagePointer())
                    {
                        id_message = id;
                        break;
                    }
                }
                Message *original = unprocessed_message_stack.at(id_message);
                unprocessed_message_stack.erase(unprocessed_message_stack.begin() + id_message);

                /*                ttl = (this->time()) + TTL_WSE;
                                Answer *tmp = new Answer(this->time(), message_wse->getKey(), message_wse->getQuery(), ttl, 1, SIZE_ANSWER);
                                ANSWERS->insertAnswer(tmp);
                                a = tmp;
                                message_wse->setAnswer( a->getVersion() );*/

                Entry *newEntry = new Entry(this->time(), message_wse->getKey(), message_wse->getQuery(),  message_wse->getVersion(), SIZE_ANSWER, getTTL( message_wse->getQuery() ));

                ANSWERS->insertEntry(newEntry);

                this->SendMessage(new Message(this->GetId(), this->GetType(),
                                              original->GetIdFrom(), original->GetTypeFrom(), time(), message_wse));
            }
        }
        // ===== BUSY TIME END =====

        time_aux = time();
        this->passivate();
        this->SumToIdleTime( time() - time_aux );
    }
}

void EdgeServer::SumToIdleTime(double add_time)
{
    this->idle_time += add_time;
}

void EdgeServer::SumToBusyTime(double add_time)
{
    this->busy_time += add_time;
}

void EdgeServer::SumToProcessedQuerys()
{
    this->processed_querys++;
    this->received_queries_by_clients_cycle++;
}

void EdgeServer::ReceiveANewMessageFromClient(int id_from)
{
    this->received_querys_from_count[ id_from ]++;
}

void EdgeServer::AddANewUnprocessedMessage(Message *message)
{
    this->unprocessed_message_stack.push_back(message);
}

Message *EdgeServer::GetMessage()
{
    Message *message = this->message_stack.back();
    this->message_stack.pop_back();
    return message;
}

unsigned int EdgeServer::GetReceivedQueriesByClients()
{
    return this->received_queries_by_clients_cycle;
}

void EdgeServer::AddANewCacheHit()
{
    cout << "HIT" << endl;
    this->cache_hits_received_queries_by_clients_cycle++;
}

void EdgeServer::AddANewCacheMiss()
{
    cout << "MISS" << endl;
    this->cache_miss_received_queries_by_clients_cycle++;
}

unsigned int EdgeServer::GetCacheHitsCycle()
{
    return this->cache_hits_received_queries_by_clients_cycle;
}

unsigned int EdgeServer::GetCacheMissCycle()
{
    return this->cache_miss_received_queries_by_clients_cycle;
}

void EdgeServer::ResetCycle()
{
    this->cache_hits_received_queries_by_clients_cycle = 0;
    this->cache_miss_received_queries_by_clients_cycle = 0;
}

long int EdgeServer::getTTL(BIGNUM *b)
{
    long int query_TTL;
    long int last_TTL;
    // Entry *old = (*tlc)->RCACHE->check(b);
    Entry *old = ANSWERS->check( b );
    if (old == NULL)
    {
        query_TTL = MIN_TTL;
    }
    else
    {
        last_TTL = old->getTimeOut();
        query_TTL = this->getTimeIncremental(last_TTL);

    }
    return query_TTL;
}

long int EdgeServer::getTimeIncremental(long int last_TTL)
{
    //   cout << " incremental" << endl;
    // TODO: Search function!!!!
    last_TTL = this->time() + last_TTL + STATIC_TIMEOUT;
    if ((last_TTL - this->time()) > MAX_TTL)
        last_TTL = this->time() + MAX_TTL;
    return last_TTL;
}