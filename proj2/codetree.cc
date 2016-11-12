#include <iostream>
#include <sstream>
#include <string>
#include "priorityqueue.h"

codetree::codetree(int freq[256]) {
  pQueue = new PQueue(freq);
  root = new ctNode;
  root->freq = counter;
  root->left = NULL;
  root->right = NULL;
}

void codetree::find(char ch) {

}

void codetree::insert

void codetree::printChar( int ch ) {
if( ch < 16 ) {
  std::cout << "x0" << std::hex << ch;
} else if( ch < 32 || ch > 126 ) {
  std::cout << "x" << std::hex << ch;
} else {
  std::cout << "\"" << (char)ch << "\"";
}
}

void codetree::printTree() {
  printTreeHelper(root, "");
}

void codetree::printTreeHelper( ctNode* r, std::string pre ) {
  if( r == NULL ) {
    return;
  }
  if( r->right == NULL ) { // implies r->left == NULL
    printChar(r->ch);
    std::cout << std::endl;
  } else {
    std::cout << "." << std::endl;
    std::cout << pre << "|`1-";
    printTreeHelper(r->right, pre + "|   ");
    std::cout << pre + "|   " << std::endl;
    std::cout << pre << "`-0-";
    printTreeHelper(r->left, pre + "    ");
  }
}
