#ifndef STATE_H
#define STATE_H

#include "FileUtility.h"
#include <iostream>
#include <map>

class State {
public:
    State();
    ~State();
    void inc();
    long long getNextChunck();
private:
    void writeState();

    std::fstream* stateFile;
    long long completed;
    std::map <long long, long long> chunckState;
};

#endif // STATE_H