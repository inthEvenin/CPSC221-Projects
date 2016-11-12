#include <iostream>
#include <string>
#include "priorityqueue.h"

struct ctNode {
  std::string str;
  int freq;
  ctNode* left;
  ctNode* right;
}

class codetree {
public:
  codetree(void);
  ctNode* find(char ch);
  void insert(char ch);
  void printChar(int ch);
  void printTree(void);
  void printTreeHelper(ctNode* r, std::string pre);

private:
  ctNode* root;
  PQueue* pQueue;
}
