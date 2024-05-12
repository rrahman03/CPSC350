#ifndef LAZY_BST_CPP
#define LAZY_BST_CPP
#include <iostream>
#include "LazyBST.h"
#include <algorithm>

template<typename T>
TreeNode<T>* LazyBST<T>::insert(TreeNode<T> *node, T value) {
    if (!node) return new TreeNode<T>(value); // if no node exists, create a new node with the given value

    if (value < node->key) // if the value is less than the current node's key
        node->left = insert(node->left, value); // insert into left subtree
    else if (value > node->key) // if value is greater than the current node's key
        node->right = insert(node->right, value); // recursively into the right subtree

    int n = depth (node->left); // calculate the depth of the left subtree
    int m = depth (node->right); // calculate the depth of the right subtree

    if (depth(node->left) > 1.5 * depth(node->right) || depth(node->right) > 1.5 * depth(node->left))
        rebalance(); // rebalance the tree if the depths differ significantly 

    // return root of the subtree
    return root;
}

template<typename T>
TreeNode<T>* LazyBST<T>::find(T value) const {

    TreeNode<T>* node;
    node = find (root, value); // search for the value starting from the root
    if (node != nullptr) {
        std::cout << node->key << " "; // if found, print the node's key
    }
    // return find(root, value;
    return node;
}

template<typename T>
TreeNode<T>* LazyBST<T>::find(TreeNode<T> *node, T value) const {
    if (!node) return nullptr; // if current node is null, return null
    if (value == node->key) return node; // if value matches, return current node
    else if (value < node->key) return find(node->left, value); // recurse left if the value is less
    else return find(node->right, value); // recurse right if the value is more
}

template<typename T>
void LazyBST<T>::insert(T value) {
    root = insert(root, value); // start insertion from the root
}

template<typename T>
bool LazyBST<T>::remove(T value) {
    bool removed = false;
    //root = remove(root, value, removed);
    remove(root, value, removed); // remove the value starting from the root
    return removed; // return true if removal was successful
}

template<typename T>
TreeNode<T>* LazyBST<T>::getMin(TreeNode<T>* node) const {
    while (node && node->left) { // traverse to the leftmost node 
        node = node->left;
    }
    return node; // return the leftmost node
}

template<typename T>
TreeNode<T>* LazyBST<T>::remove(TreeNode<T> *node, T key, bool &removed) {
    if (!node) return nullptr; // if node is null, return null

    if (key < node->key) { // if key to remove is less than current node key
        node->left = remove(node->left, key, removed); // recursively call remove on left subtree
    } else if (key > node->key) { // if key to remove is greater than current node key
        node->right = remove(node->right, key, removed); // recursively call remove on right subtree
    } else {
        removed = true; // node will be removed because removed to true
        if (!node->left && !node->right) { // if node is a leaf
            delete node; // delete the node
            return nullptr;
        } else if (!node->left) { // if node only has a right child
            TreeNode<T>* temp = node->right; // temporarily store the right child
            delete node;
            return temp;
        } else if (!node->right) { // if node only has left child
            TreeNode<T>* temp = node->left; // temporarily store left child
            delete node;
            return temp;
        } else { // if the node has both children
            TreeNode<T>* temp = getMin(node->right); // find minimum node in subtree
            node->key = temp->key; // replace node's key with minimum node's key
            node->right = remove(node->right, temp->key, removed); // recursively remove swapped node
        }
    }

    if (depth(node->left) > 1.5 * depth(node->right) || depth(node->right) > 1.5 * depth(node->left))
        rebalance(); // rebalance the tree if necessary based on subtree depths

    return node; // return the updated node
}


template<typename T>
void LazyBST<T>::printTree() const {
    printTree(root); // start recursive tree printing from the root
    std::cout << std::endl; // print a newline at the end
}

template<typename T>
void LazyBST<T>::printTree(std::ofstream& outfile) const {
    printTree(root, outfile); // start recursive tree printing from the root directed to a file
    outfile << std::endl;
}

template<typename T>
void LazyBST<T>::printTree(TreeNode<T>* node) const {
    if (!node) return; // base case: if node is null, return
    printTree(node->left); // print left subtree
    std::cout << node->key << " "; // print the current node's key
    printTree(node->right); // print the right subtree
}

template<typename T>
void LazyBST<T>::printTree(TreeNode<T>* node, std::ofstream& outfile) const {
    if (!node) return; // base case: if node is null, return
    printTree(node->left, outfile); // recursively print the left subtree to file
    outfile << node->key << " "; // output current node's key to file
    printTree(node->right, outfile); // print right subtree to file
}

template<typename T>
void LazyBST<T>::rebalance() {
    T* arr = new T[1000]; // assuming maximum 1000 elements
    int index = 0;
    inOrderTraversal(root, arr, index); // collect elements in an array in order
    clear(root); // clear existing tree
    root = buildBalancedTree(arr, 0, index - 1); // rebuild balanced tree from array
    delete[] arr; // delete the temporary array
}

template<typename T>
void LazyBST<T>::inOrderTraversal(TreeNode<T>* node, T* arr, int &index) { // traverse left subtree
    if (node) {
        inOrderTraversal(node->left, arr, index); // traverse left subtree
        arr[index++] = node->key; // store current node's key
        inOrderTraversal(node->right, arr, index); // traverse right subtree
    }
}

template<typename T>
TreeNode<T>* LazyBST<T>::buildBalancedTree(T* arr, int start, int end) {
    if (start > end) return nullptr; // base case: if stard > end, return null
    int mid = (start + end) / 2; // calculate mid index
    TreeNode<T>* node = new TreeNode<T>(arr[mid]); // create a node at mid index
    node->left = buildBalancedTree(arr, start, mid - 1); // recursively build left subtree
    node->right = buildBalancedTree(arr, mid + 1, end); // recursively build right subtree
    return node; // return newly created node
}

template<typename T>
// deconstructor 
// clears the tree
LazyBST<T>::~LazyBST() {
    clear(root);
}

template<typename T>
void LazyBST<T>::clear(TreeNode<T>* node) {
    if (node) {
        clear(node->left); // recursively clear left subtree
        clear(node->right); // recursively clear right subtree
        delete node; // delete current node
    }
}

template<typename T>
int LazyBST<T>::depth(TreeNode<T> *node) {
    if (!node) return 0; // if node is null, depth is 0
    int retVal;
    retVal = std::max(depth(
        node->left), depth(node->right)) + 1; // calculate maximum depth
    return retVal; // return calculated depth
}
#endif