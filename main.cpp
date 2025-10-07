#include <iostream>
#include <string>
#include <sstream>

#include "myArray.h"
#include "myStack.h"
#include "myQueue.h"
#include "mySinglyLinkedList.h"
#include "myDoublyLinkedList.h"
#include "myAVLTree.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 5) 
    {
        cerr << "Usage: ./dbms --file file.data --query 'cmd'" << endl;
        return 1;
    }

    string filename;
    string query;

    for(int i = 1; i < argc; ++i) 
    {
        string arg = argv[i];
        if(arg == "--file" && i + 1 < argc) 
        {
            filename = argv[++i];
        } 
        else if(arg == "--query" && i + 1 < argc)
        {
            query = argv[++i];
        }
    }

    if(filename.empty() || query.empty()) 
    {
        cerr << "Error: --file and --query are required" << endl;
        return 1;
    }

    stringstream ss(query);
    string cmd;
    ss >> cmd;

    try {
        // --- AVL commands ---
        if(cmd == "INSERTAVL") {
            int value; ss >> value;
            myAVL tree;
            loadFromFileAVL(tree, filename);
            tree.root = insertAVL(tree.root, value);
            saveToFileAVL(tree.root, filename); // передаём root
        } else if(cmd == "DELETEAVL") {
            int value; ss >> value;
            myAVL tree;
            loadFromFileAVL(tree, filename);
            tree.root = deleteNodeAVL(tree.root, value);
            saveToFileAVL(tree.root, filename); // передаём root
        } else if(cmd == "SEARCHAVL") {
            int value; ss >> value;
            myAVL tree;
            loadFromFileAVL(tree, filename);
            NodeAVL* found = searchAVL(tree.root, value);
            if(found) cout << "Found: " << found->data << endl;
            else cout << "-1" << endl;
        } else if(cmd == "PRINTAVL") {
            myAVL tree;
            loadFromFileAVL(tree, filename);
            inOrderPrintAVL(tree.root);
            cout << endl;
        }

        // --- existing commands ---
        else if(cmd == "SPUSH") { string value; ss >> value; Stack st; push(st, value, filename); }
        else if(cmd == "SPOP") { Stack st; pop(st, filename); }
        else if(cmd == "SPRINT") { Stack st; loadFromFile(st, filename); print(st); }

        else if(cmd == "APUSH") { string value; ss >> value; myArray arr; push_back(arr, value, filename); }
        else if(cmd == "AINSERT") { int index; string value; ss >> index >> value; myArray arr; insert(arr, index, value, filename); }
        else if(cmd == "APRINT") { myArray arr; loadFromFile(arr, filename); print(arr); }
        else if(cmd == "ADELETE") { int index; ss >> index; myArray arr; Delete(arr, index, filename); }

        else if(cmd == "QPUSH") { string value; ss >> value; myQueue q; push(q, value, filename); }
        else if(cmd == "QPOP") { myQueue q; pop(q, filename); }
        else if(cmd == "QPRINT") { myQueue q; loadFromFile(q, filename); print(q); }

        else if(cmd == "ADDHEADSL") { string value; ss >> value; SL_list list; addHeadSL(list, value, filename); }
        else if(cmd == "ADDTAILSL") { string value; ss >> value; SL_list list; addTailSL(list, value, filename); }
        else if(cmd == "ADDAFTERSL") { int index; string value; ss >> index >> value; SL_list list; addAfterSL(list, index, value, filename); }
        else if(cmd == "ADDBEFORESL") { int index; string value; ss >> index >> value; SL_list list; addBeforeSL(list, index, value, filename); }
        else if(cmd == "REMOVEHEADSL") { SL_list list; removeHeadSL(list, filename); }
        else if(cmd == "REMOVETAILSL") { SL_list list; removeTailSL(list, filename); }
        else if(cmd == "REMOVEAFTERSL") { int index; ss >> index; SL_list list; removeAfterSL(list, index, filename); }
        else if(cmd == "REMOVEBEFORESL") { int index; ss >> index; SL_list list; removeBeforeSL(list, index, filename); }
        else if(cmd == "DELETEBYVALUESL") { string value; ss >> value; SL_list list; deleteByValueSL(list, value, filename); }
        else if(cmd == "SEARCHBYVALUESL") { string value; ss >> value; SL_list list; int pos = searchByValueSL(list, value, filename); cout << pos << endl; }
        else if(cmd == "PRINTSL") { SL_list list; loadFromFileSL(list, filename); printSL(list); }

        else if(cmd == "ADDHEADDL") { string value; ss >> value; DL_list list; addHeadDL(list, value, filename); }
        else if(cmd == "ADDTAILDL") { string value; ss >> value; DL_list list; addTailDL(list, value, filename); }
        else if(cmd == "ADDAFTERDL") { int index; string value; ss >> index >> value; DL_list list; addAfterDL(list, index, value, filename); }
        else if(cmd == "ADDBEFOREDL") { int index; string value; ss >> index >> value; DL_list list; addBeforeDL(list, index, value, filename); }
        else if(cmd == "PRINTDL") { DL_list list; loadFromFileDL(list, filename); printDL(list); }
        else if(cmd == "BPRINTDL") { DL_list list; loadFromFileDL(list, filename); backwardsPrintDL(list); }
        else if(cmd == "SEARCHBYVALUEDL") { string value; ss >> value; DL_list list; int idx = searchByValueDL(list, value, filename); cout << idx << endl; }
        else if(cmd == "DELETEBYVALUEDL") { string value; ss >> value; DL_list list; removeByValueDL(list, value, filename); }

        else { cerr << "Unknown cmd: " << cmd << endl; return 1; }
    } catch(exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}