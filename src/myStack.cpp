#include "myStack.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

const int MAX_STACK_SIZE = 1000;


Stack::Stack() : head(nullptr), size(0) {}

Stack::Stack(const Stack& other) : head(nullptr), size(0) {
    vector<string> buf;
    NodeStack* cur = other.head;
    while(cur)
    {
        buf.push_back(cur->value); cur = cur->next;
    }

    for(int i = (int)buf.size() - 1; i >= 0; --i) 
    {
        NodeStack* n = new NodeStack{buf[i], head};
        head = n;
        size++;
    }
}

Stack& Stack::operator=(const Stack& other) {
    if(this == &other) return *this;
    clean();
    vector<string> buf;
    NodeStack* cur = other.head;

    while(cur)
    {
        buf.push_back(cur->value); cur = cur->next; 
    }

    for(int i = (int)buf.size() - 1; i >= 0; --i) 
    {
        NodeStack* n = new NodeStack{buf[i], head};
        head = n;
        size++;
    }
    return *this;
}

void Stack::clean() {
    while(head) 
    {
        NodeStack* tmp = head;
        head = head->next;
        delete tmp;
    }
    size = 0;
}

Stack::~Stack() {
    clean();
}

void loadFromFile(Stack& myStack, const string& filename) {
    ifstream in(filename);
    if(!in.is_open()) 
    {
        myStack.clean();
        return;
    }

    vector<string> lines;
    string line;
    while(getline(in, line))
    {
        lines.push_back(line);
    }
    in.close();

    myStack.clean();
    for(int i = (int)lines.size() - 1; i >= 0; --i) 
    {
        NodeStack* n = new NodeStack{lines[i], myStack.head};
        myStack.head = n;
        myStack.size++;
    }
}

void saveToFile(const Stack& myStack, const string& filename) {
    ofstream out(filename, ios::trunc);
    if(!out.is_open())
    {
        throw runtime_error("Cannot open stack file for writing: " + filename);
    }

    NodeStack* cur = myStack.head;
    while(cur) 
    {
        out << cur->value << "\n";
        cur = cur->next;
    }

    out.close();
}

void push(Stack& myStack, const string& value, const string& filename) {
    loadFromFile(myStack, filename);

    if(myStack.size >= MAX_STACK_SIZE)
    {
        throw overflow_error("Error: stack is full! Overflow might happen.");
    }

    NodeStack* newNodeStack = new NodeStack{value, myStack.head};
    myStack.head = newNodeStack;
    myStack.size += 1;

    saveToFile(myStack, filename);
}

void pop(Stack& myStack, const string& filename) {
    loadFromFile(myStack, filename);

    if(myStack.size == 0)
    {
        throw underflow_error("Error: stack is empty! Nothing to delete.");
    }

    NodeStack* toDelete = myStack.head;
    myStack.head = myStack.head->next;
    delete toDelete;
    myStack.size -= 1;

    saveToFile(myStack, filename);
}

void print(Stack& myStack) {
    if(myStack.size == 0) 
    {
        cout << "Stack is empty!" << endl;
        return;
    }

    NodeStack* current = myStack.head;
    cout << "nullptr";
    while(current != nullptr) 
    {
        cout << " <- " << current->value;
        current = current->next;
    }
    cout << endl;
}

int size(const Stack& myStack) {
    return myStack.size;
}
