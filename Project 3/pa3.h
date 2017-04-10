#include <iostream>
#include <string>
#include <vector>

using namespace std;

class stack {
    vector<string> vect;
    int max = 0;
    unsigned current = 0;
public:
    void push(string data) {
        vect.push_back(data);
        current++;
        if(max < current)
            max++;
    }

    string pop() {
        if(vect.empty()){
            current--;
            return "Empty Stack";
        }
        string data;
        data = vect.back();
        vect.pop_back();
        current--;
        return data;
    }

    int size(){
        vect.size();
    }

    int nestedLoopCount(){
        return max - vect.size();
    }
};