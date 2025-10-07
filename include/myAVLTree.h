#pragma once
#include <iostream>

using namespace std;

struct NodeAVL {
    int data;
    NodeAVL* left;
    NodeAVL* right;
    int height;
    int balanceFactor;

    NodeAVL(int value) : data(value), left(nullptr), right(nullptr), height(1), balanceFactor(0) {};
};

struct myAVL {
    NodeAVL* root = nullptr;
};

void writeInOrderAVL(NodeAVL* node, ofstream& out);
void saveToFileAVL(NodeAVL* root, const string& filename);
void loadFromFileAVL(myAVL& tree, const string& filename);

int maxValueAVL(int a, int b);
int getHeightAVL(NodeAVL* node);
int getBalanceFactorAVL(NodeAVL* node);
NodeAVL* createNodeAVL(int value);

NodeAVL* leftRotateAVL(NodeAVL* node);
NodeAVL* rightRotateAVL(NodeAVL* node);
NodeAVL* balanceAVL(NodeAVL* root);

NodeAVL* insertAVL(NodeAVL* root, int value);
NodeAVL* deleteNodeAVL(NodeAVL* root, int value);
NodeAVL* searchAVL(NodeAVL* root, int value);

void inOrderPrintAVL(NodeAVL* root);
void cleanAVL(NodeAVL* root);