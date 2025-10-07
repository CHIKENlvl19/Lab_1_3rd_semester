#include "myQueue.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

myQueue::myQueue(int initialCapacity)
    : data(nullptr), head(0), tail(0), size(0), capacity(0)
{
    if(initialCapacity <= 0)
    {
        initialCapacity = 4;
    }
    data = new string[initialCapacity];
    capacity = initialCapacity;
}

void myQueue::clean() {
    delete[] data;
    data = nullptr;
    head = 0;
    tail = 0;
    size = 0;
    capacity = 0;
}

myQueue::~myQueue() {
    clean();
}

void loadFromFile(myQueue& queue, const string& filename) {
    ifstream in(filename);
    if(!in.is_open()) 
    {
        queue.clean();
        queue.capacity = 4;
        queue.data = new string[queue.capacity];
        return;
    }

    vector<string> tmp;
    string line;
    while(getline(in, line))
    {
        tmp.push_back(line);
    }
    in.close();

    queue.clean();
    int cap = 4;
    while(cap < (int)tmp.size())
    {
        cap *= 2;
    }
    queue.capacity = cap;
    queue.data = new string[queue.capacity];
    queue.size = (int)tmp.size();
    queue.head = 0;
    queue.tail = queue.size;

    for(int i = 0; i < queue.size; ++i)
    {
        queue.data[i] = tmp[i];
    }
}

void saveToFile(const myQueue& queue, const string& filename) {
    ofstream out(filename, ios::trunc);
    if(!out.is_open())
    {
        throw runtime_error("Cannot open queue file for writing: " + filename);
    }
    for(int i = 0; i < queue.size; ++i) 
    {
        out << queue.data[(queue.head + i) % queue.capacity] << "\n";
    }

    out.close();
}

void push(myQueue& queue, const string& value, const string& filename) {
    loadFromFile(queue, filename);

    if(queue.size == queue.capacity)
    {
        int newCapacity = queue.capacity * 2;
        string* newData = new string[newCapacity];

        for(int i = 0; i < queue.size; ++i)
        {
            newData[i] = queue.data[(queue.head + i) % queue.capacity];
        }

        delete[] queue.data;
        queue.data = newData;
        queue.capacity = newCapacity;
        queue.head = 0;
        queue.tail = queue.size;
    }

    queue.data[queue.tail] = value;
    queue.tail = (queue.tail + 1) % queue.capacity;
    queue.size++;

    saveToFile(queue, filename);
}

void pop(myQueue& queue, const string& filename) {
    loadFromFile(queue, filename);

    if(queue.size == 0) 
    {
        cerr << "Error: queue is empty, nothing to delete!" << endl;
        return;
    }

    queue.head = (queue.head + 1) % queue.capacity;
    queue.size--;

    saveToFile(queue, filename);
}

void print(myQueue& queue) {
    if(queue.size == 0) 
    {
        cout << "Queue is empty!" << endl;
        return;
    }

    for(int i = 0; i < queue.size; i++)
    {
        cout << queue.data[(queue.head + i) % queue.capacity] << " ";
    }
    
    cout << endl;
}

int size(const myQueue& queue) {
    return queue.size;
}