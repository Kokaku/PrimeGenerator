#include "State.h"
#include "Chunck.h"
#include "FileUtility.h"
#include <thread>

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
    State* state = new State();
    Chunck* chunck;
    while(c != 'q') {
        int currentChunck = state->getNextChunck();
        chunck = new Chunck(currentChunck);
        for (int i = 0; i < currentChunck; ++i) {
            if(c == 'q')
                cout << i << "/" << currentChunck-1 << endl;
            chunck->resolveChunck(i);
        }
        chunck->resolve();
        chunck->write();
        state->inc();
        delete chunck;
    }
    delete state;

    std::cout << "Finished" << std::endl;
}
