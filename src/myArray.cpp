#include "myArray.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;


void loadFromFile(myArray& arr, const string& filename) {
    ifstream in(filename);
    if(!in.is_open()) 
    {
        if (arr.data == nullptr) 
        {
            arr.capacity = 4;
            arr.data = new string[arr.capacity];
        }
        arr.size = 0;
        return;
    }

    vector<string> tmp;
    string line;
    while(getline(in, line)) 
    {
        tmp.push_back(line);
    }
    in.close();

    arr.clean();
    int cap = 4;
    while(cap < (int)tmp.size())
    {
        cap *= 2;
    } 

    arr.capacity = cap;
    arr.data = new string[arr.capacity];
    arr.size = (int)tmp.size();

    for(int i = 0; i < arr.size; ++i)
    {
        arr.data[i] = tmp[i];
    }
}

void saveToFile(const myArray& arr, const string& filename) {
    ofstream out(filename, ios::trunc);
    if(!out.is_open())
    {
        throw runtime_error("Cannot open array file for writing: " + filename);
    }

    for(int i = 0; i < arr.size; ++i) 
    {
        out << arr.data[i] << "\n";
    }
    out.close();
}

myArray::myArray(int initialCapacity)
    : data(nullptr), size(0), capacity(0)
{
    if(initialCapacity <= 0)
    {
        initialCapacity = 4;
    }
    data = new string[initialCapacity];
    capacity = initialCapacity;
}

myArray::myArray(const myArray& other)
    : data(nullptr), size(other.size), capacity(other.capacity)
{
    data = new string[capacity];
    for(int i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

myArray& myArray::operator=(const myArray& other) {
    if(this == &other) return *this;

    string* newData = new string[other.capacity];
    for(int i = 0; i < other.size; ++i)
    {
        newData[i] = other.data[i];
    }

    delete[] data;
    data = newData;
    size = other.size;
    capacity = other.capacity;
    return *this;
}

void myArray::clean() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

myArray::~myArray() {
    clean();
}

void push_back(myArray& arr, string value, const string& filename) {
    loadFromFile(arr, filename);

    if(arr.size >= arr.capacity) 
    {
        int newCapacity = arr.capacity > 0 ? arr.capacity * 2 : 4;
        string* newData = new string[newCapacity];

        for(int i = 0; i < arr.size; ++i)
        {
            newData[i] = arr.data[i];
        }

        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCapacity;
    }

    arr.data[arr.size++] = value;
    saveToFile(arr, filename);
}

void insert(myArray& arr, int index, string value, const string& filename) {
    loadFromFile(arr, filename);

    if (index < 0 || index > arr.size) {
        throw out_of_range("Error: inserting failed due to invalid index.");
    }

    if(arr.size >= arr.capacity) {
        int newCapacity = arr.capacity > 0 ? arr.capacity * 2 : 4;
        string* newData = new string[newCapacity];
        for(int i = 0; i < arr.size; ++i) newData[i] = arr.data[i];
        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCapacity;
    }

    for(int i = arr.size; i > index; --i)
    {
        arr.data[i] = arr.data[i - 1];
    }
    arr.data[index] = value;
    arr.size++;
    saveToFile(arr, filename);
}

string getElement(const myArray& arr, int index) {
    if(index < 0 || index >= arr.size)
    {
        throw out_of_range("Error: getting an element failed due to invalid index.");
    }
    return arr.data[index];
}

void Delete(myArray& arr, int index, const string& filename) {
    loadFromFile(arr, filename);

    if(index < 0 || index >= arr.size)
    {
        throw out_of_range("Error: deleting an element failed due to invalid index.");
    }

    for(int i = index; i < arr.size - 1; ++i)
    {
        arr.data[i] = arr.data[i + 1];
    }
    
    arr.size--;
    saveToFile(arr, filename);
}

void swapElements(myArray& arr, int index, string value, const string& filename) {
    loadFromFile(arr, filename);

    if(index < 0 || index >= arr.size)
    {
        throw out_of_range("Error: swapping an element failed due to invalid index.");
    }

    arr.data[index] = value;
    saveToFile(arr, filename);
}

int size(const myArray& arr) {
    return arr.size;
}

void print(const myArray& arr) {
    cout << "[";
    for(int i = 0; i < arr.size; ++i)
    {
        cout << arr.data[i];
        if(i < arr.size - 1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}