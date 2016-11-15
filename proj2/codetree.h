#ifndef CODETREE_H
#define CODETREE_H

struct ctNode {
  int ch;
  int freq;
  ctNode* left;
  ctNode* right;
};

class codetree {
public:
  codetree(int freq[256], std::vector<ctNode>* heap);
  ctNode* makeCodeTree(int freq[256], std::vector<ctNode>* heap);
  void printChar(int ch);
  void printTreeHelper(ctNode* root, std::string pre);
  void printTree(void);
  void printCodeHelper(ctNode* root, std::string pre);
  void printCode(void);

private:
  ctNode* root;
};

#endif
