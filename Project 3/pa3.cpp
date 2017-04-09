#include <iostream>
#include <fstream>
#include <string>
#include "pa3.h"

using namespace std;

int main() {

    bool validFile = false;
    while(!validFile) {
        try {
            cout << "Please enter the name of the input file: ";
            string input;
            cin >> input;
            ifstream code;
            code.open(input);
            validFile = true;
        }
        catch (exception) {
            cout << "Invalid file name, please try again.";
        }
    }

    cout << "The depth of the nested loop(s) is " + depth() + "\n\n";
    cout << "Keywords: " + keywords() + "\n" +
            "Identifier: " + identifier() + "\n" +
            "Constant: " + constant() + "\n" +
            "Operators: " + operators() + "\n" +
            "Delimiter: " + delimiter() + "\n\n" +
            "Syntax Error(s): " + errors();
    return 0;
}