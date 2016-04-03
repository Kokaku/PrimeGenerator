#include "Task.h"

/*
    @author Kokaku
*/
Task::Task(unsigned long long proccedChunckFrom, unsigned long long proccedChunckTo,
    unsigned long long primeChunckFrom, unsigned long long primeChunckTo):
    proccedChunckFrom(proccedChunckFrom), proccedChunckTo(proccedChunckTo),
    primeChunckFrom(primeChunckFrom), primeChunckTo(primeChunckTo) {

    finished = false;
}

Task::~Task() {
}

void Task::execute() {
    for(unsigned long long proccedChunckId = proccedChunckFrom; proccedChunckId < proccedChunckTo; ++proccedChunckId) {
        Chunck chunck (proccedChunckId);
        // Only proccess up to chunck = id/2 since the first multiple of any number is at least 2 times itself
        unsigned long long primeChunckLimit = primeChunckTo<=proccedChunckId/2 ? primeChunckTo : proccedChunckId/2;
        for (unsigned long long primeChunckId = primeChunckFrom; primeChunckId <= primeChunckLimit; ++primeChunckId) {
            chunck.resolveChunck(primeChunckId);
        }
        chunck.write();
    }
    finished = true;
}

bool Task::isFinished() {
    return finished;
}

unsigned long long Task::getProccedChunckFrom() {
    return proccedChunckFrom;
}

unsigned long long Task::getProccedChunckTo() {
    return proccedChunckTo;
}

unsigned long long Task::getPrimeChunckFrom() {
    return primeChunckFrom;
}

unsigned long long Task::getPrimeChunckTo() {
    return primeChunckTo;
}