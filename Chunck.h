#ifndef CHUNCK_H
#define CHUNCK_H

#include <iostream>
#include <gmpxx.h>
using namespace std;

class Chunck {
public:
    Chunck(mpz_class number);
    ~Chunck();
    void resolveChunck(mpz_class primeChuckNum);
    void resolve();
    void write();
    bool hasNextPrime();
    mpz_class getNextPrime();

private:
    void resolve(mpz_class prime);
    void readBuffer();
    bool getPrimeFromPos(unsigned long pos);
    void findNextPrime();
    mpz_class number;
    string filename;
    char* buffer;
    mpz_class firstnumber;
    mpz_class nextPrime;
    unsigned long readPos;
};

#endif // CHUNCK_H