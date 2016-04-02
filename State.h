#ifndef STATE_H
#define STATE_H

#include "Task.h"
#include "FileUtility.h"
#include <iostream>
#include <map>
#include <time.h>

class State {
public:
    State();
    ~State();
    Task* getNextTask(Task* previousResult);
private:
    long long getChunckState(unsigned long long chunckId);
    void setChunckState(unsigned long long chunckId, unsigned long long status);
	void readState();
    void writeState();

    long long completed;
    unsigned int jobSize;
    std::map <unsigned long long, unsigned long long> chunckState;
    std::map <unsigned long long, std::tuple<unsigned long long, time_t>> taskState;
};

#endif // STATE_H