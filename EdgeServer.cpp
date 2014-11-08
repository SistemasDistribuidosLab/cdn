#include <iostream>
#include "EdgeServer.h"
#include "Constants.h"
#include "Client.h"
#include "wse/MessageWSE.h"
#include "wse/Answer.h"
#include "wse/Lru.h"

using namespace std;

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
            Message *message = this->GetMessageFromMessageStack();

            // cout << time() << " - Edge Server " << this->GetId() << ": Mensaje Enviado en tiempo " << message->GetCreationTime() << " desde el cliente " << message->GetIdFrom() << ": " << message->GetMessage() << endl;
            hold(processing_time_per_query);

            this->SumToBusyTime( time() - time_aux );

            MessageWSE *message_wse = message->GetMessagePointer();

            int ttl;
            Entry *a = ANSWERS->check( message_wse->getQuery() );

            if (message->GetTypeFrom() == NODE_CLIENT)
            {
                this->ReceiveANewMessageFromClient( message->GetIdFrom() );
                this->AddANewUnprocessedMessage(message);
                this->SumToProcessedQuerys();
                if (a != NULL && a->old( time() ))
                {
                    ANSWERS->remove(a);
                    a = NULL;
                }
                if (a == NULL)
                {
                    this->AddANewCacheMiss();
                    this->SendMessage(
                        new Message(
                            this->GetId(),
                            this->GetType(),
                            0,
                            NODE_ORIGIN_SERVER,
                            message->GetCreationTime(),
                            message_wse)
                    );
                }
                else
                {
                    this->AddANewCacheHit();
                    this->SendMessage(
                        new Message(
                            this->GetId(),
                            this->GetType(),
                            message->GetIdFrom(),
                            message->GetTypeFrom(),
                            message->GetCreationTime(),
                            message_wse)
                    );
                }
            }

            else if (message->GetTypeFrom() == NODE_ORIGIN_SERVER)
            {
                int id_message = GetUnprocessedMessageId(message->GetMessagePointer());
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

int EdgeServer::GetUnprocessedMessageId(MessageWSE *message_pointer)
{
    for (int id = 0; id < unprocessed_message_stack.size(); ++id)
    {
        if (unprocessed_message_stack.at(id)->GetMessagePointer() == message_pointer)
        {
            return id;
        }
    }
    return -1;
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
    this->received_queries_by_clients++;
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

Message *EdgeServer::GetMessageFromMessageStack()
{
    Message *message = this->message_stack.back();
    this->message_stack.pop_back();
    return message;
}

unsigned int EdgeServer::GetReceivedQueriesByClients()
{
    return this->received_queries_by_clients;
}

unsigned int EdgeServer::GetReceivedQueriesByClientsCycle()
{
    return this->received_queries_by_clients_cycle;
}

void EdgeServer::AddANewCacheHit()
{
    this->cache_hits_received_queries_by_clients_cycle++;
}

void EdgeServer::AddANewCacheMiss()
{
    this->cache_miss_received_queries_by_clients_cycle++;
}

unsigned int EdgeServer::GetCacheHitsReceivedQueriesByClientsCycle()
{
    return this->cache_hits_received_queries_by_clients_cycle;
}

unsigned int EdgeServer::GetCacheMissReceivedQueriesByClientsCycle()
{
    return this->cache_miss_received_queries_by_clients_cycle;
}

void EdgeServer::ResetCycle()
{
    this->received_queries_by_clients_cycle            = 0;
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

/* ========== GETTERS AND SETTERS ========== */

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