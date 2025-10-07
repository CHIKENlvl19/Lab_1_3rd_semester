#pragma once

#include <string>
using namespace std;

struct NodeSL {
    string value;
    NodeSL* next;
    NodeSL(string v, NodeSL* n = nullptr);
};

struct SL_list {
    NodeSL* head;
    int size;
    SL_list();
    SL_list(const SL_list& other);
    SL_list& operator=(const SL_list& other);
    ~SL_list();
    void clean();
};

void loadFromFileSL(SL_list& list, const string& filename);
void saveToFileSL(const SL_list& list, const string& filename);

void addHeadSL(SL_list& list, const string& value, const string& filename);
void addTailSL(SL_list& list, const string& value, const string& filename);
void addAfterSL(SL_list& list, int index, const string& value, const string& filename);
void addBeforeSL(SL_list& list, int index, const string& value, const string& filename);

void removeHeadSL(SL_list& list, const string& filename);
void removeTailSL(SL_list& list, const string& filename);
void removeAfterSL(SL_list& list, int index, const string& filename);
void removeBeforeSL(SL_list& list, int index, const string& filename);

void deleteByValueSL(SL_list& list, const string& value, const string& filename);

int searchByValueSL(SL_list& list, const string& searchKey, const string& filename);
void printSL(SL_list& list);