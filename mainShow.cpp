#include "Chunck.h"

/*
    Alternative main class that read completed chuncks
    And print the last prime number of each chunck and its corresponding id

    @author Kokaku
*/
int main(int argc, char *argv[])
{
    unsigned long long primeID = 1;
    unsigned long long chuckNum = 0;
    if (argc > 1)
        chuckNum = std::stoull(argv[1]);
    
    for (unsigned long long i = 0; i<=chuckNum; ++i) {
        Chunck* chunck = new Chunck(i);
        unsigned long long prime = 0;
        while(chunck->hasNextPrime()) {
            prime = chunck->getNextPrime();
            ++primeID;
        }
        cout<<"last found prime "<<primeID<<":"<<prime<<endl;
        delete chunck;
    }
    return 0;
}
