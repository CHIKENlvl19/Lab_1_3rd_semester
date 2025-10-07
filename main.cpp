#include <iostream>
#include <string>
#include <sstream>
#include "myArray.h"
#include "myStack.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 5) {
        cerr << "Usage: ./dbms --file file.data --query 'COMMAND'" << endl;
        return 1;
    }

    string filename;
    string query;

    for(int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if(arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if(arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if(filename.empty() || query.empty()) {
        cerr << "Error: --file and --query are required" << endl;
        return 1;
    }

    stringstream ss(query);
    string cmd;
    ss >> cmd;

    try {
        if(cmd == "SPUSH") {
            string value;
            ss >> value;
            Stack st;
            push(st, value, filename);
        } else if(cmd == "SPOP") {
            Stack st;
            pop(st, filename);
        } else if(cmd == "SPRINT") {
            Stack st;
            loadFromFile(st, filename);
            print(st);
        }

        else if(cmd == "APUSH") {
            string value;
            ss >> value;
            myArray arr;
            push_back(arr, value, filename);
        } else if(cmd == "AINSERT") {
            int index;
            string value;
            ss >> index >> value;
            myArray arr;
            insert(arr, index, value, filename);
        } else if(cmd == "APRINT") {
            myArray arr;
            loadFromFile(arr, filename);
            print(arr);
        } else if(cmd == "ADELETE") {
            int index;
            ss >> index;
            myArray arr;
            Delete(arr, index, filename);
        } else {
            cerr << "Unknown command: " << cmd << endl;
            return 1;
        }
    } catch(exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
