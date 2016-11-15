#ifndef PHEAP_H
#define PHEAP_H

class PQueue {
public:
  PQueue(std::vector<ctNode>* heap, int freq[256]);
  void swapDown(std::vector<ctNode>* heap, int i, int size);
  void heapify(std::vector<ctNode>* heap, int size);
  void removeMin(std::vector<ctNode>* heap, ctNode minNode);
  ctNode deleteMin(std::vector<ctNode>* heap);
  void insertNode(std::vector<ctNode>* heap, ctNode* newNode);
  bool isEmpty(std::vector<ctNode>* heap);
};

#endif
