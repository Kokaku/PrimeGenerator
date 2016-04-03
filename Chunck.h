#ifndef CHUNCK_H
#define CHUNCK_H

#include <iostream>
using namespace std;

/*
    A Chunck represent a span of numbers.
    Once completly processed we know  for every number in the span if they are prime number or not.

    @author Kokaku
*/
class Chunck {
public:
    // Read (or create if not existing) the chunck with given number as id (chunckId change the span)
    Chunck(unsigned long long number);
    ~Chunck();
    // Proccess chunck with id primeChuckNum. Remove prime from this that are a multiple of prime's from primeChuckNum chunck.
    void resolveChunck(unsigned long long primeChuckNum);
    // Write chunck on the disk
    void write();
    // Return true if the chunck has a next prime to be read and false otherwise.
    bool hasNextPrime();
    // Return the next prime to be read.
    unsigned long long getNextPrime();

private:
    // Proccess its own primes. Remove multiple of prime from the prime's list
    void resolve();
    // Remove all multiple of the given prime of the prime's list
    void resolve(unsigned long long prime);
    // Read the chunck from the disk
    void readBuffer();
    // Read the primality of a given number
    bool getPrimeFromPos(unsigned long pos);
    // Find the next prime in the chunck
    void findNextPrime();

    // Chunck id
    unsigned long long number;
    // Filename to store/read the chunck on the disk
    string filename;
    // Buffered chunck
    char* buffer;
    // First number represented by this chunck
    unsigned long long firstnumber;
    // Next prime to be read/returned
    long long nextPrime;
    // Current reading position
    long readPos;
};

#endif // CHUNCK_H