#include "myDoublyLinkedList.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

NodeDL::NodeDL(string v, NodeDL* n, NodeDL* p) : value(v), next(n), previous(p) {}

DL_list::DL_list() : head(nullptr), tail(nullptr), size(0) {}

DL_list::DL_list(const DL_list& other) : head(nullptr), tail(nullptr), size(0) {
    NodeDL* current = other.head;
    while(current) 
    {
        addTailDL(*this, current->value, "");
        current = current->next;
    }
}

DL_list& DL_list::operator=(const DL_list& other) {
    if(this == &other)
    {
        return *this;
    }

    clear();
    NodeDL* current = other.head;
    while(current) 
    {
        addTailDL(*this, current->value, "");
        current = current->next;
    }

    return *this;
}

DL_list::~DL_list() { clear(); }

void DL_list::clear() {
    NodeDL* current = head;
    while(current) 
    {
        NodeDL* tmp = current;
        current = current->next;
        delete tmp;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

void loadFromFileDL(DL_list& list, const string& filename) {

    if(filename.empty())
    {
        return;
    }
    
    ifstream in(filename);
    if(!in.is_open())
    {
        list.clear();
        return;
    }

    vector<string> vals;
    string line;
    while(getline(in, line))
    {
        vals.push_back(line);
    }

    in.close();
    list.clear();

    for(const auto& v : vals)
    {
        addTailDL(list, v, "");
    }
}

void saveToFileDL(const DL_list& list, const string& filename) {
    if(filename.empty())
    {
        return;
    }

    ofstream out(filename, ios::trunc);
    if(!out.is_open()) 
    {
        throw runtime_error("Cannot open DL_list file for writing: " + filename);
    }

    NodeDL* current = list.head;
    while(current) 
    {
        out << current->value << "\n";
        current = current->next;
    }

    out.close();
}

void addHeadDL(DL_list& list, const string& value, const string& filename) {
    loadFromFileDL(list, filename);

    NodeDL* newNode = new NodeDL(value, list.head, nullptr);
    if(list.head)
    {
        list.head->previous = newNode;
    }
    else
    {
        list.tail = newNode;
    }

    list.head = newNode;
    list.size++;
    saveToFileDL(list, filename);
}

void addTailDL(DL_list& list, const string& value, const string& filename) {
    loadFromFileDL(list, filename);

    NodeDL* newNode = new NodeDL(value, nullptr, list.tail);
    if(list.tail)
    {
        list.tail->next = newNode;
    }
    else
    {
        list.head = newNode;
    }

    list.tail = newNode;
    list.size++;
    saveToFileDL(list, filename);
}

void addAfterDL(DL_list& list, int index, const string& value, const string& filename) {
    loadFromFileDL(list, filename);

    if(index < 0 || index >= list.size) 
    {
        cerr << "Error: index out of range in addAfterDL\n";
        return;
    }

    NodeDL* current = list.head;
    for(int i=0; i<index; i++)
    {
        current = current->next;
    }

    NodeDL* newNode = new NodeDL(value, current->next, current);
    if(current->next)
    {
        current->next->previous = newNode;
    }
    else
    {
        list.tail = newNode;
    }

    current->next = newNode;
    list.size++;
    saveToFileDL(list, filename);
}

void addBeforeDL(DL_list& list, int index, const string& value, const string& filename) {
    loadFromFileDL(list, filename);

    if(index < 0 || index >= list.size) 
    {
        cerr << "Error: index out of range in addBeforeDL\n";
        return;
    }

    NodeDL* current = list.head;
    for(int i=0; i<index; i++)
    {
        current = current->next;
    }

    NodeDL* newNode = new NodeDL(value, current, current->previous);
    if(current->previous)
    {
        current->previous->next = newNode;
    }
    else
    {
        list.head = newNode;
    }

    current->previous = newNode;
    list.size++;
    saveToFileDL(list, filename);
}

void removeByValueDL(DL_list& list, const string& value, const string& filename) {
    loadFromFileDL(list, filename);

    NodeDL* current = list.head;
    while(current && current->value != value)
    {
        current = current->next;
    }
    if(!current)
    {
        cerr << "Value not found in removeByValueDL\n";
        return;
    }

    if(current->previous)
    {
        current->previous->next = current->next;
    }
    else
    {
        list.head = current->next;
    }

    if(current->next)
    {
        current->next->previous = current->previous;
    }
    else
    {
        list.tail = current->previous;
    }

    delete current;
    list.size--;
    saveToFileDL(list, filename);
}

int searchByValueDL(DL_list& list, const string& value, const string& filename) {
    loadFromFileDL(list, filename);

    NodeDL* current = list.head;

    int idx = 0;
    while(current) 
    {
        if(current->value == value)
        {
            return idx;
        }
        current = current->next;
        idx++;
    }
    return -1;
}

void printDL(DL_list& list) {
    NodeDL* current = list.head;

    cout << "[";
    while(current) 
    {
        cout << current->value;
        if(current->next)
        {
            cout << " <-> ";
        }
        current = current->next;
    }
    cout << "]" << endl;
}

void backwardsPrintDL(DL_list& list) {
    NodeDL* currentrent = list.tail;
    cout << "[";
    while(currentrent) 
    {
        cout << currentrent->value;
        if(currentrent->previous)
        {
            cout << " <-> ";
        }
        currentrent = currentrent->previous;
    }
    cout << "]" << endl;
}