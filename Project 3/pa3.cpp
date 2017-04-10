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


    stack parenthesis;
    stack identifier;
    stack constant;

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

    int count = 0;
    string line;
    while( getline(file, line) ) {
        cout << "Line " << count++ << ": " << line << std::endl;

        //finds delimiters and operators and keywords
        if(line.find("FOR") != string::npos){
            forr = true;
        }
        if(line.find("BEGIN") != string::npos){
            begin = true;
        }
        if(line.find("END") != string::npos){
            end = true;
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
        if(line.find("++") != string::npos){
            plusplus = true;
        }
        if(line.find("+") != string::npos){
            plus = true;
        }
        if(line.find("-") != string::npos){
            minus = true;
        }
        if(line.find("--") != string::npos){
            minusminus = true;
        }
        if(line.find("=") != string::npos){
            equals = true;
        }
        if(line.find("==") != string::npos){
            equalsequals = true;
        }
    }

    file.close();

    cout << "The depth of the nested loop(s) is ";
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
    cout << "\n";
    cout << "Constant: ";
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
    return 0;
}