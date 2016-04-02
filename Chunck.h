#ifndef CHUNCK_H
#define CHUNCK_H

#include <iostream>
using namespace std;

class Chunck {
public:
    Chunck(unsigned long long number);
    ~Chunck();
    void resolveChunck(unsigned long long primeChuckNum);
    void write();
    bool hasNextPrime();
    unsigned long long getNextPrime();

private:
    void resolve();
    void resolve(unsigned long long prime);
    void readBuffer();
    bool getPrimeFromPos(unsigned long pos);
    void findNextPrime();
    unsigned long long number;
    string filename;
    char* buffer;
    unsigned long long firstnumber;
    long long nextPrime;
    long readPos;
};

#endif // CHUNCK_H