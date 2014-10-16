#include <iomanip>
#include <iostream>

const char separator    = ' ';
const int nameWidth     = 6;
const int numWidth      = 8;

template<typename T> void printElement(T t, const int &width) {
    cout << left << setw(width) << setfill(separator) << t;
}