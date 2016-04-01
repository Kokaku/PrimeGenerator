#include "State.h"
#include "Chunck.h"
#include <thread>

void listenKeyboard();
void generatePrime();
char c = '0';

int main(int argc, char *argv[])
{
    /*
    std::thread keyboard(listenKeyboard);
    std::thread generate(generatePrime);

    keyboard.join();
    generate.join();
    // */

    //*
    unsigned long long primeID = 1;
    int chuckNum = 0;
    if (argc > 1)
        chuckNum = std::stoi(argv[1]);
    
    for (int i = 0; i<=chuckNum; ++i) {
        Chunck* chunck = new Chunck(i);
        unsigned long long prime = 0;
        while(chunck->hasNextPrime()) {
            prime = chunck->getNextPrime();
            ++primeID;
            /*cout<<"prime: "<<prime<<endl;
             if (prime >= 110)
             break;*/
        }
        cout<<"last found prime "<<primeID<<":"<<prime<<endl;
        delete chunck;
    }
    // */
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
    Chunck* cChunck;
    while(c != 'q') {
        int currentChunck = state->getNextChunck();
        chunck = new Chunck(currentChunck);
        for (int i = 0; i < currentChunck; ++i) {
            cChunck = new Chunck(i);
            if(c == 'q')
                cout << i << "/" << currentChunck-1 << endl;
            while(cChunck->hasNextPrime()) {
                unsigned long long next = cChunck->getNextPrime();
                chunck->resolve(next);
            }
            delete cChunck;
        }
        chunck->resolve();
        chunck->write();
        state->inc();
        delete chunck;
    }
    delete state;

    std::cout << "Finished" << std::endl;
}
