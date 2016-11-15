#include <iostream>
#include <sstream>
#include <vector>
#include "codetree.h"
#include "priorityqueue.h"

// class constructor
codetree::codetree(int freq[256], std::vector<ctNode>* heap) {
    root = makeCodeTree(freq, heap);
}

// helper method to create codetree
// picks two nodes with lowest priority and join them together to a new parent
// parent node replaces the two children nodes
ctNode* codetree::makeCodeTree(int freq[256], std::vector<ctNode>* heap) {
    PQueue* pQueue = new PQueue(heap, freq); // to use PQueue methods

    int freqSum = 0;
    ctNode* rootNode = new ctNode;
    while(heap->size() > 1) {
        ctNode* child1 = new ctNode;
        ctNode* child2 = new ctNode;
        *child1 = pQueue->deleteMin(heap); // #1 node with lowest priority
        *child2 = pQueue->deleteMin(heap); // #2 node with lowest priority

        ctNode* newParent = new ctNode; // parent node to replace 2 childs

        freqSum = child1->freq + child2->freq;

        newParent->ch = -1;  // inserting dummy value for character
        newParent->freq = freqSum;
        newParent->right = child2;
        newParent->left = child1;

        pQueue->insertNode(heap, newParent); // insert new parent to heap
        rootNode = newParent;
    }
    return rootNode; // return created codetree
}

// provided code
void codetree::printChar( int ch ) {
if( ch < 16 ) {
  std::cout << "x0" << std::hex << ch;
} else if( ch < 32 || ch > 126 ) {
  std::cout << "x" << std::hex << ch;
} else {
  std::cout << "\"" << (char)ch << "\"";
}
}

// provided code
void codetree::printTreeHelper(ctNode* root, std::string pre) {
  if(root == NULL) {
    return;
  }
  if(root->right == NULL) { // implies r->left == NULL
    printChar(root->ch);
    std::cout << std::endl;
  } else {
    std::cout << "." << std::endl;
    std::cout << pre << "|`1-";
    printTreeHelper(root->right, pre + "|   ");
    std::cout << pre + "|   " << std::endl;
    std::cout << pre << "`-0-";
    printTreeHelper(root->left, pre + "    ");
  }
}

// print out the codetree in tree form
void codetree::printTree() {
  printTreeHelper(root, "");
}

// helper method to print Huffman encoding for each character
void codetree::printCodeHelper(ctNode* root, std::string pre) {
  if(root == NULL) {
    return;
  }
  if(root->right == NULL) { // implies r->left == NULL
    printChar(root->ch);
    std::cout << ":" << pre << std::endl;
  } else {
    printCodeHelper(root->left, pre + "0"); // left-subtree with "0" prefix
    printCodeHelper(root->right, pre + "1"); // right-subtree with "1" prefix
  }
}

// print out each character with their Huffman encoding
void codetree::printCode() {
  printCodeHelper(root, "");
}
