#pragma once

#include <string>
using namespace std;

struct NodeStack {
    string value;
    NodeStack* next;
};

struct Stack {
    NodeStack* head;
    int size;

    Stack();
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    ~Stack();

    void clean();
};

void loadFromFile(Stack& myStack, const string& filename);
void saveToFile(const Stack& myStack, const string& filename);

void push(Stack& myStack, const string& value, const string& filename);
void pop(Stack& myStack, const string& filename);
void print(Stack& myStack);
int size(const Stack& myStack);

