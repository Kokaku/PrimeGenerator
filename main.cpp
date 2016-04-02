#include "State.h"
#include "Chunck.h"
#include "FileUtility.h"
#include <thread>
#include <chrono>
#include <omp.h>

bool createResultDir(std::string sPath);
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
