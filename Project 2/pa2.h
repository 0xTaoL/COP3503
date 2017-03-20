#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class Memory{
private:
    typedef struct node{
        bool free;
        string programName;
        node* next;
    }* nodePtr;
    nodePtr head;
    nodePtr curr;
public:
    Memory();
    int killProgram(string name);
    void addNodeToEnd(bool dtrFree, string name);
    void add(string name, int pages, int alg);
    void printMemory();
    bool full();
    int chunks(int alg, int pages);
    bool alreadyRunning(string name);
    ~Memory();
};

