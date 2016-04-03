#ifndef TASK_H
#define TASK_H

#include "Chunck.h"

/*
    A Task represent a job to be executed by a thread.
    This is a small portion of the job that is independent of any other Task that may exists at the same time.

    @author Kokaku
*/
class Task {
public:
    // Create a new Task to proccess chunck from proccedChunckFrom (inclusive) to chunck proccedChunckTo (exclusive)
    // with prime numbers from chunck primeChunckFrom (inclusive) to chunck primeChunckTo (exclusive)
    Task(unsigned long long proccedChunckFrom, unsigned long long proccedChunckTo,
        unsigned long long primeChunckFrom, unsigned long long primeChunckTo);
    ~Task();
    // Execute this task
    void execute();
    // Return true once this task have been executed
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