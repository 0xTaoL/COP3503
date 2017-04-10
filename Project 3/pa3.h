#include <iostream>
#include <string>
#include <vector>

using namespace std;

class stack {
    vector<string> vect;
public:
    void push(std::string data) {
        vect.push_back(data);
    }
    string pop() {
        string data;
        data = vect.back();
        vect.pop_back();
        return data;
    }
    int depth() {
        return vect.size();
    }
};