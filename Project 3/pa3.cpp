#include <iostream>
#include <fstream>
#include <string>
#include "pa3.h"
#include <vector>

using namespace std;

int main() {

    cout << "Please enter the name of the input file: ";
    string input;
    cin >> input;
    ifstream file(input);

    if(!file){
        cout << "Invalid File.";
        return 1;
    }

    stack depth;
    stack constants;
    stack identifiers;
    stack badSyntaxs;

    bool comma = false;
    bool semicolon = false;
    bool plusplus = false;
    bool minusminus = false;
    bool minus = false;
    bool plus = false;
    bool equals = false;
    bool equalsequals = false;
    bool mult = false;
    bool div = false;
    bool begin = false;
    bool end = false;
    bool forr = false;

    //goes line by line and checks what is there
    int count = 0;
    string line;
    while( getline(file, line) ) {
        cout << "Line " << count++ << ": " << line << std::endl;


        //finds constants (numbers)
        for (unsigned i = 0; i < line.size(); i++) {
            if (isdigit(line.at(i))) {
                unsigned j = 0;
                while (i+j < line.size() && isdigit(line.at(i+j))) {
                    j++;
                }
                string constant = line.substr(i,j);
                constants.push(constant);
                i += j;
            }
        }

        //same as above but finds identifiers
        for (unsigned i = 0; i < line.size(); i++) {
            if (isupper(line.at(i))) {
                unsigned j = 0;
                while (i+j < line.size() && islower(line.at(i+j))) {
                    j++;
                }
                string indentifier = line.substr(i,j);
                identifiers.push(indentifier);
                i += j;
            }
        }

        //same as above but finds misspelled syntax
        for (unsigned i = 0; i < line.size(); i++) {
            if (isupper(line.at(i))) {
                unsigned j = 0;
                while (i+j < line.size() && isupper(line.at(i+j))) {
                    j++;
                }
                string badSyntax = line.substr(i,j);
                if(!badSyntax.compare("BEGIN") && !badSyntax.compare("FOR") && !badSyntax.compare("END")) {
                    badSyntaxs.push(badSyntax);
                }
                i += j;
            }
        }

        //finds delimiters and operators and keywords
        if(line.find("FOR") != string::npos){
            forr = true;
        }
        if(line.find("BEGIN") != string::npos){
            begin = true;
            depth.push("BEGIN");
        }
        if(line.find("END") != string::npos){
            end = true;
            depth.pop();
        }
        if(line.find(";") != string::npos){
            semicolon = true;
        }
        if(line.find(",") != string::npos){
            comma = true;
        }
        if(line.find("*") != string::npos){
            mult = true;
        }
        if(line.find("/") != string::npos){
            div = true;
        }
        if(line.find("+") != string::npos){
            if(line.find("++") != string::npos){
                plusplus = true;
            }
            else {
                plus = true;
            }
        }
        if(line.find("-") != string::npos){
            if(line.find("--") != string::npos){
                minusminus = true;
            }
            else {
                minus = true;
            }
        }
        if(line.find("=") != string::npos){
            if(line.find("==") != string::npos){
                equalsequals = true;
            }
            else {
                equals = true;
            }
        }
    }

    file.close();

    cout << "The depth of the nested loop(s) is ";
    cout << depth.nestedLoopCount();
    cout << "\n";
    cout << "Keywords: ";
    if(begin){
        cout << "BEGIN ";
    }
    if(end){
        cout << "END ";
    }
    if(forr){
        cout << "FOR ";
    }
    cout << "\n";
    cout << "Identifier: ";
    identifiers.removeDuplicates();
    while (identifiers.size()>0){
        cout << identifiers.pop() + " ";
    }
    cout << "\n";
    cout << "Constant: ";
    constants.removeDuplicates();
    while (constants.size()>0){
        cout << constants.pop() + " ";
    }
    cout << "\n";
    cout << "Operators: ";
    if(plus){
        cout << "+ ";
    }
    if(minus){
        cout << "- ";
    }
    if(mult){
        cout << "* ";
    }
    if(div){
        cout << "/ ";
    }
    if(minusminus){
        cout << "-- ";
    }
    if(plusplus){
        cout << "++ ";
    }
    if(equals){
        cout << "= ";
    }
    if(equalsequals){
        cout << "== ";
    }
    cout << "\n";
    cout << "Delimiter: ";
    if(semicolon){
        cout << "; ";
    }
    if (comma){
        cout << ", ";
    }
    cout << "\n\n";
    cout << "Syntax Error(s): ";
    badSyntaxs.removeDuplicates();
    while (badSyntaxs.size()>0){
        cout << badSyntaxs.pop() + " ";
    }
    return 0;
}