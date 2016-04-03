#ifndef STATE_H
#define STATE_H

#include "Task.h"
#include "FileUtility.h"
#include <iostream>
#include <map>
#include <time.h>

/*
	State is a class that represent teh state of computation.
	It knows which chunck has finish to proccess and at which stage of processing are each chuncks.

    @author Kokaku
*/
class State {
public:
    State();
    ~State();
    /*
	Give back the previously executed task as argument and return the next task to be executed.
	Be carefull, the given executed task will be deleted during the call.
	The previously executed task and the returned next task may be NULL.
	If the returned next task is NULL, this indicate that the thread should wait a short time before asking for a new task.
    */
    Task* getNextTask(Task* previousResult);
private:
	// Return the state of the given chunck. The state is the chunck id of the next chunck it needs to be proccessed
    long long getChunckState(unsigned long long chunckId);
    // Set the new state of the given chunck
    void setChunckState(unsigned long long chunckId, unsigned long long state);
    // Read chuncks state and global state on the disk
	void readState();
    // Write chuncks state and global state on the disk
    void writeState();

    // Number of chuncks that are completly proccessed
    long long completed;
    // Size of Task generated
    unsigned int jobSize;
    // State of every chunck that are not completed but yet created
    std::map <unsigned long long, unsigned long long> chunckState;
    // Future state of every chunck that are assigned to a Task after its corresponding task is finished
    std::map <unsigned long long, std::tuple<unsigned long long, time_t>> taskState;
};

#endif // STATE_H