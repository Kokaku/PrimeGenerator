#ifndef TASK_H
#define TASK_H

#include "Chunck.h"

class Task {
public:
    Task(unsigned long long proccedChunckFrom, unsigned long long proccedChunckTo,
        unsigned long long primeChunckFrom, unsigned long long primeChunckTo);
    ~Task();
    void execute();
    bool isFinished();
    unsigned long long getProccedChunckFrom();
    unsigned long long getProccedChunckTo();
    unsigned long long getPrimeChunckFrom();
    unsigned long long getPrimeChunckTo();

private:
    unsigned long long proccedChunckFrom;
    unsigned long long proccedChunckTo;
    unsigned long long primeChunckFrom;
    unsigned long long primeChunckTo;

    bool finished;
};

#endif // TASK_H