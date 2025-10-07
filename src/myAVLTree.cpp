#include "myAVLTree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

// рекурсивная запись в файл (in-order)
void writeInOrder(NodeAVL* node, ofstream& out) {
    if(!node) return;
    writeInOrder(node->left, out);
    out << node->data << "\n";
    writeInOrder(node->right, out);
}

void saveToFileAVL(NodeAVL* root, const string& filename) {
    if(filename.empty()) return;

    ofstream out(filename, ios::trunc);
    if(!out.is_open()) {
        throw runtime_error("Cannot open AVL file for writing: " + filename);
    }

    writeInOrder(root, out);

    out.close();
}

void loadFromFileAVL(myAVL& tree, const string& filename) {
    tree.root = nullptr;
    if(filename.empty()) return;

    ifstream in(filename);
    if(!in.is_open()) return;

    vector<int> values;
    int val;
    while(in >> val) {
        values.push_back(val);
    }
    in.close();

    for(int v : values) {
        tree.root = insertAVL(tree.root, v);
    }
}

int maxValueAVL(int a, int b) {
    return a > b ? a : b;
}

int getHeightAVL(NodeAVL* node) {
    return node ? node->height : 0;
}

int getBalanceFactorAVL(NodeAVL* node) {
    return node ? getHeightAVL(node->left) - getHeightAVL(node->right) : 0;
}

NodeAVL* createNodeAVL(int value) {
    return new NodeAVL(value);
}

NodeAVL* leftRotateAVL(NodeAVL* node) {
    if (!node || !node->right)
    {
       return node; 
    }

    NodeAVL* rightChild = node->right;
    NodeAVL* tmpTree = rightChild->left;

    rightChild->left = node;
    node->right = tmpTree;

    node->height = 1 + maxValueAVL(getHeightAVL(node->left), getHeightAVL(node->right));
    rightChild->height = 1 + maxValueAVL(getHeightAVL(rightChild->left), getHeightAVL(rightChild->right));

    node->balanceFactor = getBalanceFactorAVL(node);
    rightChild->balanceFactor = getBalanceFactorAVL(rightChild);

    return rightChild;
}

NodeAVL* rightRotateAVL(NodeAVL* node) {
    if (!node || !node->left)
    {
        return node;
    }

    NodeAVL* leftChild = node->left;
    NodeAVL* tmpTree = leftChild->right;

    leftChild->right = node;
    node->left = tmpTree;

    node->height = 1 + maxValueAVL(getHeightAVL(node->left), getHeightAVL(node->right));
    leftChild->height = 1 + maxValueAVL(getHeightAVL(leftChild->left), getHeightAVL(leftChild->right));

    node->balanceFactor = getBalanceFactorAVL(node);
    leftChild->balanceFactor = getBalanceFactorAVL(leftChild);

    return leftChild;
}

NodeAVL* balanceAVL(NodeAVL* root) {
    if (!root)
    {
       return root; 
    }
    root->height = 1 + maxValueAVL(getHeightAVL(root->left), getHeightAVL(root->right));
    root->balanceFactor = getBalanceFactorAVL(root);

    if (root->balanceFactor > 1 && getBalanceFactorAVL(root->left) >= 0)
    {
        return rightRotateAVL(root);
    }

    if (root->balanceFactor > 1 && getBalanceFactorAVL(root->left) < 0) 
    {
        root->left = leftRotateAVL(root->left);
        return rightRotateAVL(root);
    }

    if (root->balanceFactor < -1 && getBalanceFactorAVL(root->right) <= 0)
    {
        return leftRotateAVL(root);
    }
        
    if (root->balanceFactor < -1 && getBalanceFactorAVL(root->right) > 0) 
    {
        root->right = rightRotateAVL(root->right);
        return leftRotateAVL(root);
    }

    return root;
}

NodeAVL* insertAVL(NodeAVL* root, int value) {
    if(!root)
    {
        return createNodeAVL(value);
    }

    if(value < root->data)
    {
        root->left = insertAVL(root->left, value);
    }
    else if(value > root->data)
    {
        root->right = insertAVL(root->right, value);
    }
    else
    {
        return root;
    }

    return balanceAVL(root);
}

NodeAVL* minValueNodeAVL(NodeAVL* node) {
    NodeAVL* current = node;
    while(current && current->left)
    {
        current = current->left;
    }

    return current;
}

NodeAVL* deleteNodeAVL(NodeAVL* root, int value) {
    if(!root) return root;

    if(value < root->data)
    {
        root->left = deleteNodeAVL(root->left, value);
    }

    else if(value > root->data)
    {
        root->right = deleteNodeAVL(root->right, value);
    }
    else 
    {
        if(!root->left || !root->right) 
        {
            NodeAVL* tmp = root->left ? root->left : root->right;
            if(!tmp) 
            {
                tmp = root;
                root = nullptr;
            } else 
            {
                *root = *tmp;
            }
            delete tmp;
        } 
        else 
        {
            NodeAVL* tmp = minValueNodeAVL(root->right);
            root->data = tmp->data;
            root->right = deleteNodeAVL(root->right, tmp->data);
        }
    }

    if(!root)
    {
        return nullptr;
    }

    return balanceAVL(root);
}

NodeAVL* searchAVL(NodeAVL* root, int value) {
    if(!root || root->data == value)
    {
        return root;
    }

    if(value < root->data)
    {
        return searchAVL(root->left, value);
    }

    return searchAVL(root->right, value);
}

void inOrderPrintAVL(NodeAVL* root) {
    if(!root)
    {
        return;
    }

    inOrderPrintAVL(root->left);
    cout << root->data << " ";
    inOrderPrintAVL(root->right);
}

void cleanAVL(NodeAVL* root) {
    if(!root)
    {
        return;
    }

    cleanAVL(root->left);
    cleanAVL(root->right);
    delete root;
}
