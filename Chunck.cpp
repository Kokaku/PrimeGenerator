#include "Chunck.h"
#include "FileUtility.h"

#define FIRST_NUMBER 3
#define BUFFER_SIZE 4194304
//#define BUFFER_SIZE 10
#define MASK 0xFF

Chunck::Chunck(int number):number(number) {
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

void Chunck::resolveChunck(int primeChuckNum) {
    Chunck primeChuck (primeChuckNum);
    while(primeChuck.hasNextPrime()) {
        unsigned long long next = primeChuck.getNextPrime();
        this->resolve(next);
    }
}

void Chunck::resolve(long prime) {
    unsigned long long index = (firstnumber / prime);
    if(firstnumber%prime != 0)
        index++;
    index *= prime;
    if(index == 0)
        index = 3*prime;
    else if(index == prime)
        index += 2*prime;
    else if(index%2 == 0)
        index += prime;
    index -= firstnumber;
    long end = BUFFER_SIZE * 8;
    unsigned long long i = index/2;
    for(long i = index/2; i<end; i+=prime) {
        int bufferIndex = i/8;
        buffer[bufferIndex] = buffer[bufferIndex]&(1<<(i%8)^MASK);
    }
}

void Chunck::resolve() {
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        for (int j = 0; j < 8; ++j) {
            if((buffer[i]&(1<<j)) != 0) {
                //cout << firstnumber+ i*8*2 + j*2 << endl;
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

bool Chunck::getPrimeFromPos(long pos) {
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
