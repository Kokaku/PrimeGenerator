#include "State.h"

static const std::string FILENAME = "data/state";

State::State() {
    jobSize = 10;
    completed = -1;

    if(fexists(FILENAME)) {
        readState();
    } else {
        this->writeState();
    }
}

State::~State() {
    this->writeState();
    chunckState.clear();
    taskState.clear();
}

Task* State::getNextTask(Task* previousResult) {
    if(previousResult) {
        if(previousResult->isFinished()) {
            for(unsigned long long i = previousResult->getProccedChunckFrom(); i < previousResult->getProccedChunckTo(); ++i) {
                taskState.erase(i);
                setChunckState(i, previousResult->getPrimeChunckTo());
            }
            delete previousResult;
        } else {
            delete previousResult;
            return NULL;
        }
    }

    if(completed < 0 && taskState.count(0)) return NULL; 

    long long nextChunck = completed+1;
    long long primeChunckFrom = getChunckState(nextChunck);
    while(taskState.count(nextChunck) ||
        (primeChunckFrom >= 0 && primeChunckFrom > completed)) {
        ++nextChunck;
        primeChunckFrom = getChunckState(nextChunck);
    }

    unsigned long long nextChunckTo = nextChunck;
    for(++nextChunckTo; nextChunckTo < nextChunck+jobSize; ++nextChunckTo) {
        if(getChunckState(nextChunckTo) != primeChunckFrom || taskState.count(nextChunckTo)) break;
    }

    time_t timer;
    time(&timer);
    if(primeChunckFrom < 0) primeChunckFrom = 0;
    unsigned long long primeChunckTo = primeChunckFrom + jobSize;
    for(unsigned long long i = nextChunck; i < nextChunckTo; ++i) {
        taskState[i] = std::make_tuple(primeChunckTo, timer);
    }

    return new Task(nextChunck, nextChunckTo, primeChunckFrom, primeChunckTo);
}

long long State::getChunckState(unsigned long long chunckId) {
    if(!chunckState.count(chunckId)) return -1;
    return chunckState[chunckId];
}

void State::setChunckState(unsigned long long chunckId, unsigned long long status) {
    chunckState[chunckId] = status;
    if(completed+1 == chunckId) {
        long long checkChunckId = chunckId;
        long long checkState = status;
        while(checkState >= checkChunckId/2) {
            chunckState.erase(checkChunckId);
            ++completed;
            ++checkChunckId;
            std::cout<<"Completed : "<<completed<<std::endl;
            checkState = getChunckState(checkChunckId);
        }
        //this->writeState();
    }
}

void State::readState() {
    std::fstream stateFile (FILENAME, std::fstream::in | std::fstream::out | std::fstream::binary);
    if (stateFile) {
        stateFile.seekp(0);
        stateFile.read((char*)(&completed), sizeof(completed));
        std::cout<<(completed+1)<<" chucks completed."<<std::endl;
        unsigned long long mapSize = 0;
        stateFile.read((char*)(&mapSize), sizeof(unsigned long long));
        for (unsigned long long i = 0; i < mapSize; ++i) {
            unsigned long long chunckId = completed + i;
            stateFile.read((char*)(&(chunckState[chunckId])), sizeof(unsigned long long));
        }
    } else {
        std::cout << "Failed to read state file." << std::endl;
    }
    stateFile.close();
}

void State::writeState() {
    std::fstream stateFile (FILENAME, std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
    stateFile.seekp(0);
    stateFile.write((char*)(&completed), sizeof(completed));
    unsigned long long mapSize = chunckState.size();
    stateFile.write((char*)(&mapSize), sizeof(mapSize));
    unsigned long long chunckId = completed+1;
    long long status = getChunckState(chunckId);
    while(status >= 0) {
        unsigned long long uStatus = (unsigned long long)status;
        stateFile.write((char*)(&uStatus), sizeof(unsigned long long));
        ++chunckId;
        status = getChunckState(chunckId);
    }
    stateFile.close();
}
