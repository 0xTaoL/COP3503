#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "pa2.h"

using namespace std;

void program(int n);
int numPages(int kilobytes);

Memory mem;

int main(int argc, char ** argv) {
    if(argc != 2){
        cout << "Wrong number of Arguments.";
        return -1;
    }
    if(string(argv[1]) == "best"){
        cout << "Using best fit algorithm\n";
        program(1);
        return 0;
    }
    if(string(argv[1]) == "worst"){
        cout << "Using worst fit algorithm\n";
        program(2);
        return 0;
    }
    else{
        cout << "Invalid Parameter.";
        return -1;
    }
}

Memory::Memory(){
    head = NULL;
    curr = NULL;
}

void Memory::addNodeToEnd(bool dtrFree, string name) {
    nodePtr n = new node;
    n->next = NULL;
    n->free = dtrFree;
    n->programName = name;
    if(head != NULL){
        curr = head;
        while(curr->next != NULL){
            curr = curr ->next;
        }
        curr-> next = n;
    }
    else{
        head = n;
    }
}

void Memory::printMemory() {
    int counter = 1;
    curr = head;
    while(curr != NULL){
        cout << curr-> programName << "\t";
        curr = curr->next;
        if(counter%8 == 0){
            cout << "\n";
        }
        counter++;
    }
}

Memory::~Memory() {
    nodePtr delPtr = NULL;
    curr = head;
    while(curr != NULL){
        delPtr = curr;
        delete delPtr;
        curr = curr->next;
    }
}

//checks if program is already running in memory
bool Memory::alreadyRunning(string name){
    nodePtr first;
    first = head;
    if(first-> programName.compare(name) == 0){
        return true;
    }
    while(first-> programName.compare(name) != 0) {
        first = first -> next;
        if(first-> programName.compare(name) == 0){
            return true;
        }
        if(first->next == NULL){
            break;
        }
    }
    return false;
}

bool Memory::full(){
    nodePtr cu = head;
    while(cu->next !=NULL){
        if(!cu->free){
            cu = cu->next;
        }
        if(cu->free){
            return false;
        }
    }
    return true;
}

//returns where to start putting the program as well as the number of fragments
//alg 1 is best, 2 is worst, 3 is number of fragments
//the value returned is the index of the first node of a free chunk, number returned depends on alg
//also returns the number of fragments as this method indexes all free chunks
int Memory::chunks(int alg, int pages){
    if(full()){
        if(alg == 1 || alg ==2){
            cout << "Error, Not enough memory for the requested Program";
            return -1;
        }
        else{
            return 0;
        }
    }
    int indexCounter = 0;       //index of node
    int freeChunkSize = 0;
    nodePtr first = head;
    nodePtr second = head;
    nodePtr temp = head;
    vector<int> index;
    index.clear();
    vector<int> size;
    size.clear();
    int i = 0;
    while(first != NULL && second != NULL) {
        freeChunkSize = 0;
        first=temp;
        while(!first->free){   //moves first and second pointer to first free block or the last block
            first = first->next;
            second = first;
            if(first == NULL){
                break;
            }
            indexCounter++;        //First free block
        }
        if(first == NULL){      //special case when on unpopulated last node

//            code below commented because it is checked later on (redundancy)
//            if(alg == 1 || alg == 2){
//                cout << "Error, Not enough memory for the requested Program1";
//                return -1;
//            }

            if(alg == 3){
                if(i==0) {
                    return 0;
                }
                else{
                    break;
                }
            }
        }
        index.push_back(indexCounter);  //pushes the nth position of a free space
        while (second->free) {
            second = second->next;
            freeChunkSize++;
            if(second == NULL){
                break;
            }
            indexCounter++;
        }
        //stops second pointer at the end or at the start of a program
        temp = second;
        size.push_back(freeChunkSize);
        i++;
        if(indexCounter == 31){ //special case when at end of node and on last node that is populated
            break;
        }
    }

    //checks if there is enough available free space
    int vectorSize = size.size();
    int sumOfFreeSpace = 0;
    for(int j = 0; j < vectorSize; j++) {
        sumOfFreeSpace += size[j];
    }
    if(pages>sumOfFreeSpace){
        cout << "Error, Not enough memory for the requested Program";
        return -1;
    }
    //checks if there is a chunk that is big enough to hold the program
    bool sizeFound = false;
    for (int k = 0;k<vectorSize; k++){
        if(size[k]>=pages){
            sizeFound = true;
            break;
        }
    }
    if(!sizeFound){
        cout << "Error, Not enough memory for the requested Program";
        return -1;
    }

	//returns the smallest memory chunk that can fit the requested program
    if(alg == 1){
        int numErased = 1;
        vector<int>::iterator min = min_element(size.begin(), size.end());
        while (*min<pages){
            index.erase(index.begin() + distance(size.begin(),min));
            size.erase(size.begin() + distance(size.begin(),min));
            min = min_element(size.begin(), size.end());
            numErased++;
        }
        return index[distance(size.begin(),min)];
    }
    
    //returns the largest memory chunk that can fit the requested program
    if(alg == 2){
        vector<int>::iterator max = max_element(size.begin(), size.end());
        return index[distance(size.begin(), max)];
    }
    
    //returns the number of fragments
    if(alg == 3){
        return i;
    }
    else{
        return -2;
    }
}

//adds program to memory depending on requested alg
void Memory::add(string name, int pages, int alg){
    nodePtr current = head;
    if(mem.alreadyRunning(name)){
        cout << "Error, Program " << name << " already running.";
        return;
    }
    int startAdd = chunks(alg, pages);
    if(startAdd == -1){
        return;
    }
    if(startAdd != 0) {
        for (int i = 0; i < startAdd; i++) {   //iterates to first free node of free chunk specified by chunks
            current = current->next;
        }
    }
    for(int i = 0; i<pages; i++){      //iterates to replace nodes (pages) amount of times and goes to next node
        current->free = false;          //no need to check for null because space has already been checked
        current->programName = name;
        current = current->next;
    }
    cout << "Program " << name << " added successfully, " << pages << " page(s) used.";
}

//kill request program
int Memory::killProgram(string name){
    int pagesFreed = 0;
    nodePtr current;
    current = head;
    while(true){
        if(current == NULL){
            cout <<"\nError, Program not found!" << endl;
            return 0;
        }
        if(current->programName.compare(name) == 0 && !current->free){
            break;
        }
        current=current->next;
    }
    while(current != NULL && current->programName.compare(name) == 0 && !current->free) {
            current->programName = "Free";
            current->free = true;
            current = current->next;
            pagesFreed++;
    }
    return pagesFreed;
}

//converts kilobytes to the number of pages needed
int numPages(int kilobytes){
    int pages = kilobytes/4;
    if((kilobytes%4)>0){
        pages++;
    }
    return pages;
}

void program(int n) {
    for(int i = 0; i<32; i++){
        mem.addNodeToEnd(true, "Free");
    }
    cout << "1. Add program\n"
            "2. Kill program\n"
            "3. Fragmentation\n"
            "4. Print memory\n"
            "5. Exit\n";
    while(true) {
        cout << "\nchoice - ";
        int option;
        cin >> option;
        while(option<1 || option>5){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid option. Please Try Again.\n";
            cout << "1. Add program\n"
                    "2. Kill program\n"
                    "3. Fragmentation\n"
                    "4. Print memory\n"
                    "5. Exit\n"
                    "choice - ";
            cin >> option;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        string name = "";
        switch (option){
            case 1: {
                cout << "\nProgram name - ";
                cin >> name;
                cin.clear();
				cin.ignore(10000, '\n');
                int size;
                cout << "\nProgram size (KB) - ";
                cin >> size;
                while(size<=0 ) {
                    cout << "Please enter a valid program size - ";
					cin.clear();
                    cin.ignore(10000, '\n');
                    cin >> size;
                }
				cin.clear();
                cin.ignore(10000, '\n');
                if (n == 1) {
                    mem.add(name, numPages(size),1);
                }
                if (n == 2) {
                    mem.add(name, numPages(size),2);
                }
            }
                break;
            case 2: {
                cout << "\nProgram name - ";
                cin >> name;
                cin.clear();
				cin.ignore(10000, '\n');
                int reclaimed = mem.killProgram(name);
                if (reclaimed != 0) {
                    cout << "\nProgram " << name << " successfully killed, " << reclaimed << " pages(s) reclaimed.";
                }
            }
                break;
            case 3: {
                cout << "\nThere are " << mem.chunks(3,0) << " fragment(s).";
            }
                break;
            case 4: {
                mem.printMemory();
            }
                break;
            case 5:
                return;
            default:
                return;
        }
    }
}