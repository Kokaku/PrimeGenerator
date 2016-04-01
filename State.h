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
    int getNextChunck();
private:
    void writeState();

    std::fstream* stateFile;
    int completed;
    std::map <int, int> chunckState;
};

#endif // STATE_H