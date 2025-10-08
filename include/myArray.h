#pragma once

#include <string>
using namespace std;

struct myArray {
    string* data;
    int size;
    int capacity;

    myArray(int initialCapacity = 4);
    myArray(const myArray& other);
    myArray& operator=(const myArray& other);
    ~myArray();

    void clean();
};

void loadFromFileA(myArray& arr, const string& filename);
void saveToFile(const myArray& arr, const string& filename);

void push_back(myArray& arr, string value, const string& filename);
void insert(myArray& arr, int index, string value, const string& filename);
string getElement(const myArray& arr, int index);
void Delete(myArray& arr, int index, const string& filename);
void swapElements(myArray& arr, int index, string value, const string& filename);
int size(const myArray& arr);
void print(const myArray& arr);