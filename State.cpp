#include "State.h"

State::State() {
    std::string filename = "data/state";
    completed = -1;

    if(fexists(filename)) {
        stateFile = new std::fstream(filename, std::fstream::in | std::fstream::out | std::fstream::binary);
        stateFile->seekp(0);
        stateFile->read((char*)(&completed), sizeof(completed));
        std::cout<<(completed+1)<<" chucks completed."<<std::endl;
    } else {
        stateFile = new std::fstream(filename, std::fstream::in | std::fstream::out | std::fstream::app | std::fstream::binary);
        this->writeState();
        stateFile->close();
        stateFile = new std::fstream(filename, std::fstream::in | std::fstream::out | std::fstream::binary);
    }
}

State::~State() {
    this->writeState();
    stateFile->close();
    stateFile = NULL;
}

void State::inc() {
    completed++;
    std::cout<<"Completed : "<<completed<<std::endl;
    this->writeState();
}

int State::getNextChunck() {
    return completed+1;
}

void State::writeState() {
    stateFile->seekp(0);
    stateFile->write((char*)(&completed), sizeof(completed));
}
