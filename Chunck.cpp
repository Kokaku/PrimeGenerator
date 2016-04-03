#include "Chunck.h"
#include "FileUtility.h"

// First number represented on the first chunck
#define FIRST_NUMBER 3
// Chunck size in bytes
#define BUFFER_SIZE 4194304
// Mask for bytes
#define MASK 0xFF

/*
    @author Kokaku
*/
Chunck::Chunck(unsigned long long number):number(number) {
    filename = "data/chunck"+std::to_string(number)+".bin";
    firstnumber = FIRST_NUMBER + number*BUFFER_SIZE*8*2;
    buffer = new char[BUFFER_SIZE];

    readBuffer();
    readPos = -1;
    findNextPrime();
}

Chunck::~Chunck() {
    delete [] buffer;
}

void Chunck::readBuffer() {
    if(fexists(filename)) {
        std::fstream* primeFile = new fstream(filename, ios::in | ios::binary);
        primeFile->read(buffer, BUFFER_SIZE);
        primeFile->close();
    } else {
        fill_n(buffer, BUFFER_SIZE, 0xFF);
    }
}

void Chunck::resolveChunck(unsigned long long primeChuckNum) {
    // If the given arg is the chunck id then call the specialized method to proccess itself
    // Otherwise read each prime number in the given chunck and process each read prime number.
    if(primeChuckNum == number) {
        this->resolve();
    } else {
        Chunck primeChuck (primeChuckNum);
        while(primeChuck.hasNextPrime()) {
            unsigned long long next = primeChuck.getNextPrime();
            this->resolve(next);
        }
    }
}

void Chunck::resolve(unsigned long long prime) {
    // index is the index of the first number in the chunck that is a multiple of the given prime number
    unsigned long long index = firstnumber / prime;
    if(firstnumber%prime != 0)
        index++;
    index *= prime;
    if(index == 0)
        index = FIRST_NUMBER*prime;
    else if(index == prime)
        index += 2*prime;
    else if(index%2 == 0)
        index += prime;
    index -= firstnumber;
    // end is the last index of the chunck
    unsigned long end = BUFFER_SIZE * 8;

    // Remove each multiple of the given prime in this chunck
    for(unsigned long i = index/2; i<end; i+=prime) {
        // bufferIndex is the index of the byte in the buffer corresponding to a multiple of the given prime number
        unsigned long bufferIndex = i/8;
        buffer[bufferIndex] = buffer[bufferIndex]&(1<<(i%8)^MASK);
    }
}

void Chunck::resolve() {
    for (unsigned long long i = 0; i < BUFFER_SIZE; ++i) {
        for (unsigned long j = 0; j < 8; ++j) {
            if((buffer[i]&(1<<j)) != 0) {
                this->resolve(firstnumber + i*8*2 + j*2);
            }
        }
    }
}

void Chunck::write() {
    std::fstream* primeFile = new fstream(filename, ios::out | ios::binary);
    primeFile->write (buffer, BUFFER_SIZE);
    primeFile->close();
}

void Chunck::findNextPrime() {
    ++readPos;
    while((readPos/8) < BUFFER_SIZE && (!this->getPrimeFromPos(readPos))) {
        readPos++;
    }

    if((readPos/8) >= BUFFER_SIZE) {
        nextPrime = 0;
    }
    else {
        nextPrime = firstnumber + 2*readPos;
    }
}

bool Chunck::getPrimeFromPos(unsigned long pos) {
    return buffer[pos/8] & (1<<(pos%8));
}

bool Chunck::hasNextPrime() {
    return nextPrime > 0 ;
}

unsigned long long Chunck::getNextPrime() {
    unsigned long long copy = nextPrime;
    this->findNextPrime();
    return copy;
}
