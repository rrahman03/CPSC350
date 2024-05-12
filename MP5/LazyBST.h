#ifndef LAZY_BST_H
#define LAZY_BST_H

#include <iostream>
#include <fstream>
#include "Student.h"
#include "Faculty.h"


template<typename T>
class TreeNode {
public:
    T key; // key value type T stored in TreeNode
    TreeNode<T> *left; // pointer to the left child
    TreeNode<T> *right; // pointer to the right child

    // constructor
    TreeNode(T k) : key(k), left(nullptr), right(nullptr) {}
};

template<typename T>
class LazyBST {
private:
    TreeNode<T> *root; // pointer to the root node
    TreeNode<T>* getMin(TreeNode<T>* node) const; // function to get the minimum node starting from a given node
    TreeNode<T>* insert(TreeNode<T> *node, T value); // insert function
    TreeNode<T>* remove(TreeNode<T> *node, T key, bool &removed); // remove function
    TreeNode<T>* find(TreeNode<T> *node, T value) const; // find function
    void inOrderTraversal(TreeNode<T>* node, T* arr, int &index); // function to perform in-order traversal
    TreeNode<T>* buildBalancedTree(T* arr, int start, int end); // function to build a balanced tree from an array
    int depth(TreeNode<T> *node); // function to calculate the depth of the tree
    void clear(TreeNode<T>* node); // function to clear the tree
    void printTree(TreeNode<T>* node) const; // recursive function to print the tree
    void printTree(TreeNode<T>* node, std::ofstream& outfile) const; // print tree to a file

public:
    // constructor
    LazyBST() : root(nullptr) {}
    // destructor
    ~LazyBST();

    void insert(T value); // insert value into BST
    bool remove(T value); // remove value from BST
    TreeNode<T>* find(T value) const; // find value in BST
    void printTree() const; // print tree to standard output
    void printTree (std::ofstream& outfile) const; // print tree to a file
    void rebalance(); // function to rebalance the tree
};

#include "LazyBST.cpp"

#endif
