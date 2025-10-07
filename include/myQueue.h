#pragma once

#include <string>
using namespace std;

struct myQueue {
    string* data;
    int head;
    int tail;
    int size;
    int capacity;

    myQueue(int initialCapacity = 4);
    ~myQueue();

    void clean();
};

void loadFromFile(myQueue& queue, const string& filename);
void saveToFile(const myQueue& queue, const string& filename);

void push(myQueue& queue, const string& value, const string& filename);
void pop(myQueue& queue, const string& filename);
void print(myQueue& queue);
int size(const myQueue& queue);