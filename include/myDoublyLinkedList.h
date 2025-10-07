#pragma once
#include <string>

using namespace std;

struct NodeDL {
    string value;
    NodeDL* next;
    NodeDL* previous;

    NodeDL(string v, NodeDL* n = nullptr, NodeDL* p = nullptr);
};

struct DL_list {
    NodeDL* head;
    NodeDL* tail;
    int size;

    DL_list();
    DL_list(const DL_list& other);
    DL_list& operator=(const DL_list& other);
    ~DL_list();

    void clear();
};

void loadFromFileDL(DL_list& list, const string& filename);
void saveToFileDL(const DL_list& list, const string& filename);

void addHeadDL(DL_list& list, const string& value, const string& filename);
void addTailDL(DL_list& list, const string& value, const string& filename);
void addAfterDL(DL_list& list, int index, const string& value, const string& filename);
void addBeforeDL(DL_list& list, int index, const string& value, const string& filename);

void removeByValueDL(DL_list& list, const string& value, const string& filename);

int searchByValueDL(DL_list& list, const string& value, const string& filename);

void printDL(DL_list& list);
void backwardsPrintDL(DL_list& list);
