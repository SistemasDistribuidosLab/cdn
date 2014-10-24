#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include "../glob.h"
// #include "../p2pLayer/NodeEntry.h"

using namespace std;

class UTIL {

    public:

        static int *EMPTY;
        static int *MAX;
        static int *MIN;
        static int BNZERO;

        UTIL();

        ~UTIL();

        static char *obtain_terms ( vector<string> t );

        static void Tokenize ( const string &,
                               vector<string> &,
                               const string &);

        static bool startWith( int *, char );

        static bool startWith( const char *, char );

        // static string truncateNodeId( NodeEntry *);

        static string truncateNodeId( int *);

        static int chartoIndex( char );

        static char getDigit( int );

        // static int prefixLen( int *, NodeEntry *);

        // static const char *myBN2HEX( int *);

        // static const char *myBN2HEX2( int *);

        static int charSize(const char *);

        static bool hasDigitAt( int *, int, char );

        static bool hasDigitAt( const char *, int, char );
};

#endif
