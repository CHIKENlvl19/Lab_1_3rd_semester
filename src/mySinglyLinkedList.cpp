#include "mySinglyLinkedList.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

NodeSL::NodeSL(string v, NodeSL* n) : value(v), next(n) {}

SL_list::SL_list() : head(nullptr), size(0) {}

SL_list::SL_list(const SL_list& other) : head(nullptr), size(0) {
    NodeSL* current = other.head;
    while(current)
    {
        addTailSL(*this, current->value, "");
        current = current->next;
    }
}

SL_list& SL_list::operator=(const SL_list& other) {
    if(this == &other)
    {
        return *this;
    }

    clean();
    NodeSL* current = other.head;
    while(current) 
    {
        addTailSL(*this, current->value, "");
        current = current->next;
    }

    return *this;
}

SL_list::~SL_list() { clean(); }

void SL_list::clean() {
    while(head) 
    {
        NodeSL* tmp = head;
        head = head->next;
        delete tmp;
    }

    head = nullptr;
    size = 0;
}

void loadFromFileSL(SL_list& list, const string& filename) {
    if(filename.empty())
    {
        return;
    }

    ifstream in(filename);
    if(!in.is_open())
    { 
        list.clean();
        return;
    }

    vector<string> tmp;
    string line;
    while(getline(in, line))
    {
        tmp.push_back(line);
    }

    in.close();
    list.clean();
    for(const auto& val : tmp)
    {
        addTailSL(list, val, "");
    }
}

void saveToFileSL(const SL_list& list, const string& filename) {
    if(filename.empty())
    {
        return;
    }
    
    ofstream out(filename, ios::trunc);
    if(!out.is_open())
    {
        throw runtime_error("Cannot open list file for writing: " + filename);
    }
    
    NodeSL* current = list.head;
    while(current)
    {
        out << current->value << "\n";
        current = current->next;
    }

    out.close();
}

void addHeadSL(SL_list& list, const string& value, const string& filename) {
    loadFromFileSL(list, filename);
    
    list.head = new NodeSL(value, list.head);
    list.size++;
    
    saveToFileSL(list, filename);
}

void addTailSL(SL_list& list, const string& value, const string& filename) {
    loadFromFileSL(list, filename);
    
    NodeSL* newNodeSL = new NodeSL(value);
    if(!list.head)
    {
        list.head = newNodeSL;
    }
    else 
    {
        NodeSL* current = list.head;
        while(current->next)
        {
            current = current->next;
        }
        current->next = newNodeSL;
    }

    list.size++;
    saveToFileSL(list, filename);
}

void addAfterSL(SL_list& list, int index, const string& value, const string& filename) {
    loadFromFileSL(list, filename);
    
    NodeSL* current = list.head;
    for(int i = 0; i < index; ++i) 
    {
        if(!current)
        {
            cerr << "Error: index out of range!";
            return;
        }
        current = current->next;
    }

    if(current)
    {
        NodeSL* newNodeSL = new NodeSL(value, current->next);
        current->next = newNodeSL;
        list.size++;
    }

    saveToFileSL(list, filename);
}

void addBeforeSL(SL_list& list, int index, const string& value, const string& filename) {
    loadFromFileSL(list, filename);
    
    if(index <= 0)
    {
        list.head = new NodeSL(value, list.head);
        list.size++;
    }
    else 
    {
        NodeSL* prev = list.head;
        
        for(int i = 0; i < index-1; ++i)
        {
            if(!prev)
            {
                cerr << "Error: index out of range!";
                return;
            } 
            prev = prev->next;
        }
        
        NodeSL* newNodeSL = new NodeSL(value, prev->next);
        prev->next = newNodeSL;
        list.size++;
    }
    saveToFileSL(list, filename);
}

void removeHeadSL(SL_list& list, const string& filename) {
    loadFromFileSL(list, filename);

    if(list.head)
    {
        NodeSL* tmp = list.head;
        list.head = list.head->next;
        delete tmp;
        list.size--;
    }

    saveToFileSL(list, filename);
}

void removeTailSL(SL_list& list, const string& filename) {
    loadFromFileSL(list, filename);
    
    if(!list.head)
    {
        saveToFileSL(list, filename);
        return;
    }
    
    if(!list.head->next)
    {
        delete list.head;
        list.head = nullptr;
        list.size--;
        saveToFileSL(list, filename);
        return;
    }

    NodeSL* current = list.head;
    while(current->next->next)
    {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
    list.size--;
    saveToFileSL(list, filename);
}

void removeAfterSL(SL_list& list, int index, const string& filename) {
    loadFromFileSL(list, filename);

    NodeSL* current = list.head;
    for(int i = 0; i < index; ++i)
    {
        if(!current)
        {
            cerr << "Error: index out of range!";
            return;
        } 
        current = current->next;
    }
    
    if(current && current->next)
    {
        NodeSL* tmp = current->next;
        current->next = tmp->next;
        delete tmp;
        list.size--;
    }

    saveToFileSL(list, filename);
}

void removeBeforeSL(SL_list& list, int index, const string& filename) {
    loadFromFileSL(list, filename);

    if(index <= 0 || !list.head || !list.head->next)
    {   
        saveToFileSL(list, filename);
        return;
    }

    if(index == 1)
    {
        NodeSL* tmp = list.head;
        list.head = list.head->next;
        delete tmp;
        list.size--;
    }
    else 
    {
        NodeSL* prev = list.head;
        
        for(int i = 0; i < index-2; ++i)
        {
            if(!prev)
            {
                saveToFileSL(list, filename);
                return;
            } 
            
            prev = prev->next;
        }
        
        NodeSL* tmp = prev->next;
        if(tmp)
        {
            prev->next = tmp->next;
            delete tmp;
            list.size--;
        }
    }

    saveToFileSL(list, filename);
}

void deleteByValueSL(SL_list& list, const string& value, const string& filename) {
    loadFromFileSL(list, filename);

    if(!list.head)
    {
        saveToFileSL(list, filename); 
        return;
    }

    if(list.head->value == value) 
    {
        NodeSL* tmp = list.head;
        list.head = list.head->next;
        delete tmp;
        list.size--;
        
        saveToFileSL(list, filename);
        return;
    }
    
    NodeSL* current = list.head;
    while(current->next && current->next->value != value)
    {
        current = current->next;
    }
    if(current->next) 
    {
        NodeSL* tmp = current->next;
        current->next = tmp->next;
        delete tmp;
        list.size--;
    }

    saveToFileSL(list, filename);
}

int searchByValueSL(SL_list& list, const string& searchKey, const string& filename) {

    loadFromFileSL(list, filename);

    NodeSL* current = list.head;
    int idx = 0;
    while(current)
    {
        if(current->value == searchKey)
        {
            return idx;
            
        }
        current = current->next;
        idx++;
    }
    return -1;
}

void printSL(SL_list& list) {
    NodeSL* current = list.head;
    cout << "[";
    while(current)
    {
        cout << current->value;
        if(current->next) cout << " -> ";
        current = current->next;
    }
    cout << "]" << endl;
}
