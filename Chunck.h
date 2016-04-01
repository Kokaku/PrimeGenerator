#ifndef CHUNCK_H
#define CHUNCK_H

#include <iostream>
using namespace std;

class Chunck {
public:
    Chunck(int number);
    ~Chunck();
    void resolveChunck(int primeChuckNum);
    void resolve(long prime);
    void resolve();
    void write();
    bool hasNextPrime();
    unsigned long long getNextPrime();

private:
    void readBuffer();
    bool getPrimeFromPos(long pos);
    void findNextPrime();
    int number;
    string filename;
    char* buffer;
    unsigned long long firstnumber;
    unsigned long long nextPrime;
    long readPos;
};

#endif // CHUNCK_H