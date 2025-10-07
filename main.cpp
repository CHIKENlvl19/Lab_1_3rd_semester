#include <iostream>
#include <string>
#include <sstream>

#include "header.h"
#include "myArray.h"
#include "myStack.h"
#include "myQueue.h"
#include "mySinglyLinkedList.h"
#include "myDoublyLinkedList.h"
#include "myAVLTree.h"

using namespace std;

Command getCommand(const string& cmdStr) {
    if(cmdStr == "INSERTAVL") return Command::INSERTAVL;
    if(cmdStr == "DELETEAVL") return Command::DELETEAVL;
    if(cmdStr == "SEARCHAVL") return Command::SEARCHAVL;
    if(cmdStr == "PRINTAVL") return Command::PRINTAVL;

    if(cmdStr == "SPUSH") return Command::SPUSH;
    if(cmdStr == "SPOP") return Command::SPOP;
    if(cmdStr == "SPRINT") return Command::SPRINT;

    if(cmdStr == "APUSH") return Command::APUSH;
    if(cmdStr == "AINSERT") return Command::AINSERT;
    if(cmdStr == "APRINT") return Command::APRINT;
    if(cmdStr == "ADELETE") return Command::ADELETE;

    if(cmdStr == "QPUSH") return Command::QPUSH;
    if(cmdStr == "QPOP") return Command::QPOP;
    if(cmdStr == "QPRINT") return Command::QPRINT;

    if(cmdStr == "ADDHEADSL") return Command::ADDHEADSL;
    if(cmdStr == "ADDTAILSL") return Command::ADDTAILSL;
    if(cmdStr == "ADDAFTERSL") return Command::ADDAFTERSL;
    if(cmdStr == "ADDBEFORESL") return Command::ADDBEFORESL;
    if(cmdStr == "REMOVEHEADSL") return Command::REMOVEHEADSL;
    if(cmdStr == "REMOVETAILSL") return Command::REMOVETAILSL;
    if(cmdStr == "REMOVEAFTERSL") return Command::REMOVEAFTERSL;
    if(cmdStr == "REMOVEBEFORESL") return Command::REMOVEBEFORESL;
    if(cmdStr == "DELETEBYVALUESL") return Command::DELETEBYVALUESL;
    if(cmdStr == "SEARCHBYVALUESL") return Command::SEARCHBYVALUESL;
    if(cmdStr == "PRINTSL") return Command::PRINTSL;

    if(cmdStr == "ADDHEADDL") return Command::ADDHEADDL;
    if(cmdStr == "ADDTAILDL") return Command::ADDTAILDL;
    if(cmdStr == "ADDAFTERDL") return Command::ADDAFTERDL;
    if(cmdStr == "ADDBEFOREDL") return Command::ADDBEFOREDL;
    if(cmdStr == "PRINTDL") return Command::PRINTDL;
    if(cmdStr == "BPRINTDL") return Command::BPRINTDL;
    if(cmdStr == "SEARCHBYVALUEDL") return Command::SEARCHBYVALUEDL;
    if(cmdStr == "DELETEBYVALUEDL") return Command::DELETEBYVALUEDL;

    return Command::UNKNOWN;
}

int main(int argc, char* argv[]) {
    if(argc < 5) 
    {
        cerr << "Usage: ./dbms --file file.data --query 'cmd'\n";
        return 1;
    }

    string filename, query;
    for(int i = 1; i < argc; ++i) 
    {
        string arg = argv[i];
        if(arg == "--file" && i+1 < argc)
        {
            filename = argv[++i];
        }
        else if(arg == "--query" && i+1 < argc)
        {
            query = argv[++i];
        }
    }

    if(filename.empty() || query.empty()) {
        cerr << "Error: --file and --query are required\n";
        return 1;
    }

    stringstream ss(query);
    string cmdStr;
    ss >> cmdStr;
    Command cmd = getCommand(cmdStr);

    try 
    {
        switch(cmd) {
            case Command::INSERTAVL: {
            int value; 
            ss >> value;
            myAVL tree;

            loadFromFileAVL(tree, filename);
            tree.root = insertAVL(tree.root, value);
            saveToFileAVL(tree.root, filename);
            break;
        }
        case Command::DELETEAVL: {
            int value; 
            ss >> value;
            myAVL tree;

            loadFromFileAVL(tree, filename);
            tree.root = deleteNodeAVL(tree.root, value);
            saveToFileAVL(tree.root, filename);
            break;
        }
        case Command::SEARCHAVL: {
            int value; 
            ss >> value;
            myAVL tree;

            loadFromFileAVL(tree, filename);
            NodeAVL* found = searchAVL(tree.root, value);
            if(found) cout << "Found: " << found->data << endl;
            else cout << "-1" << endl;
            break;
        }
        case Command::PRINTAVL: {
            myAVL tree;

            loadFromFileAVL(tree, filename);
            inOrderPrintAVL(tree.root);
            cout << endl;
            break;
        }

        case Command::SPUSH: {
            string value; 
            ss >> value;
            Stack st;

            push(st, value, filename);
            break;
        }
        case Command::SPOP: {
            Stack st; 

            pop(st, filename);
            break;
        }
        case Command::SPRINT: {
            Stack st;
            
            loadFromFile(st, filename);
            print(st);
            break;
        }

        case Command::APUSH: {
            string value; 
            ss >> value;
            myArray arr;

            push_back(arr, value, filename);
            break;
        }
        case Command::AINSERT: {
            int index;
            string value; 
            ss >> index >> value;
            myArray arr;

            insert(arr, index, value, filename);
            break;
        }
        case Command::APRINT: {
            myArray arr;

            loadFromFile(arr, filename);
            print(arr);
            break;
        }
        case Command::ADELETE: {
            int index; 
            ss >> index;
            myArray arr; 

            Delete(arr, index, filename);
            break;
        }

        case Command::QPUSH: {
            string value; 
            ss >> value;
            myQueue q;

            push(q, value, filename);
            break;
        }
        case Command::QPOP: {
            myQueue q;

            pop(q, filename);
            break;
        }
        case Command::QPRINT: {
            myQueue q;

            loadFromFile(q, filename);
            print(q);
            break;
        }

        case Command::ADDHEADSL: {
            string value; 
            ss >> value;
            SL_list list;

            addHeadSL(list, value, filename);
            break;
        }
        case Command::ADDTAILSL: {
            string value; 
            ss >> value;
            SL_list list;

            addTailSL(list, value, filename);
            break;
        }
        case Command::ADDAFTERSL: {
            int index;
            string value; 
            ss >> index >> value;
            SL_list list;

            addAfterSL(list, index, value, filename);
            break;
        }
        case Command::ADDBEFORESL: {
            int index;
            string value; 
            ss >> index >> value;
            SL_list list;

            addBeforeSL(list, index, value, filename);
            break;
        }
        case Command::REMOVEHEADSL: {
            SL_list list;

            removeHeadSL(list, filename);
            break;
        }
        case Command::REMOVETAILSL: {
            SL_list list;

            removeTailSL(list, filename);
            break;
        }
        case Command::REMOVEAFTERSL: {
            int index; 
            ss >> index;
            SL_list list;

            removeAfterSL(list, index, filename);
            break;
        }
        case Command::REMOVEBEFORESL: {
            int index; 
            ss >> index;
            SL_list list;

            removeBeforeSL(list, index, filename);
            break;
        }
        case Command::DELETEBYVALUESL: {
            string value; 
            ss >> value;
            SL_list list;

            deleteByValueSL(list, value, filename);
            break;
        }
        case Command::SEARCHBYVALUESL: {
            string value; 
            ss >> value;
            SL_list list;

            int pos = searchByValueSL(list, value, filename);
            cout << pos << endl;
            break;
        }
        case Command::PRINTSL: {
            SL_list list;

            loadFromFileSL(list, filename);
            printSL(list);
            break;
        }

        case Command::ADDHEADDL: {
            string value; 
            ss >> value;
            DL_list list;

            addHeadDL(list, value, filename);
            break;
        }
        case Command::ADDTAILDL: {
            string value; 
            ss >> value;
            DL_list list;

            addTailDL(list, value, filename);
            break;
        }
        case Command::ADDAFTERDL: {
            int index; string value; 
            ss >> index >> value;
            DL_list list;

            addAfterDL(list, index, value, filename);
            break;
        }
        case Command::ADDBEFOREDL: {
            int index;
            string value; 
            ss >> index >> value;
            DL_list list;

            addBeforeDL(list, index, value, filename);
            break;
        }
        case Command::PRINTDL: {
            DL_list list;

            loadFromFileDL(list, filename);
            printDL(list);
            break;
        }
        case Command::BPRINTDL: {
            DL_list list;

            loadFromFileDL(list, filename);
            backwardsPrintDL(list);
            break;
        }
        case Command::SEARCHBYVALUEDL: {
            string value; 
            ss >> value;
            DL_list list;

            int idx = searchByValueDL(list, value, filename);
            cout << idx << endl;
            break;
        }
        case Command::DELETEBYVALUEDL: {
            string value; 
            ss >> value;
            DL_list list;

            removeByValueDL(list, value, filename);
            break;
        }

        default:
            cerr << "Unknown command\n";
            break;
    }

    } 
    catch(exception& e) {
        cerr << e.what() << "\n";
    }

    return 0;
}