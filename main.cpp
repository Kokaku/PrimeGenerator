#include "State.h"
#include "Chunck.h"
#include "FileUtility.h"
#include <thread>
#include <chrono>
#include <omp.h>

/*
    This programm generate prime numbers up to 2^64 (size of unsigned long long)
    The method of computation is inspired by the sieve of Eratosthenes.
    However, the work is splited in Chuncks and Tasks in order to be parallelizable.

    Create two threads.
    One that listen to the keyboard and tell the program to stop generate tasks once the programm termination is asked.
    A second one that read the previous state on the disk and continue the prime generation.
    The prime generation is additionally parallelized with OpenMP.

    @author Kokaku
*/

void listenKeyboard();
void generatePrime();
char c = '0';

int main(int argc, char *argv[]) {

    std::string sPath = "data";
    if (!createDir(sPath)) {
        std::cerr << "Failed to create directory " << sPath << ".\n";
        return -1;
    }

    std::thread keyboard(listenKeyboard);
    std::thread generate(generatePrime);

    keyboard.join();
    generate.join();

    return 0;
}

void listenKeyboard() {

    while(c != 'q') {
        std::cin >> c;
    }

    std::cout << "Programm is exiting" << std::endl;
}

void generatePrime() {
    State state;
    #pragma omp parallel shared(state)
    {
        Task* currentTask = NULL;
        while(c != 'q') {
            #pragma omp critical
            {
                currentTask = state.getNextTask(currentTask);
            }
            if(currentTask) {
                currentTask->execute();
            } else {
                std::this_thread::sleep_for (std::chrono::seconds(1));
            }
        }
        #pragma omp critical
        {
            currentTask = state.getNextTask(currentTask);
        }
        if(currentTask) delete currentTask;
    }

    std::cout << "Finished" << std::endl;
}
