#include <string>
#include <vector>
#include "codetree.h"
#include "priorityqueue.h"

// class constructor
PQueue::PQueue(std::vector<ctNode>* heap, int freq[256]) {
  for(int i = 0; i < 256; i++) {
    if(freq[i] != 0) {
      ctNode* newNode = new ctNode;
      newNode->ch = i;  // index as character value
      newNode->freq = freq[i]; // freq stored at that index
      newNode->left = NULL; // initializing
      newNode->right = NULL; // initializing
      insertNode(heap, newNode); // insert new node to heap
    }
  }
}

// from binaryHeap.cp; edited so that heap now prioritizes high freq values.
void PQueue::swapDown(std::vector<ctNode>* heap, int i, int size) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int max = i;
    if (leftChild < size && heap->at(leftChild).freq > heap->at(max).freq)
        max = leftChild;
    if (rightChild < size && heap->at(rightChild).freq > heap->at(max).freq)
        max = rightChild;
    if (max != i) {
        std::swap(heap->at(i), heap->at(max));
        swapDown(heap, max, size);
    }
}

// from binaryHeap.cp; edited so it can be used on vector
void PQueue::heapify(std::vector<ctNode>* heap, int size) {
    for (int i = (size - 2) / 2; i >= 0; i--)
        swapDown(heap, i, size);
}

// helper method to remove the lowest priority node in heap
void PQueue::removeMin(std::vector<ctNode>* heap, ctNode minNode) {
    size_t i;
    for (i = 0; i < heap->size(); i++) {  // iterate heap to find matching node
        if(heap->at(i).ch == minNode.ch && heap->at(i).freq == minNode.freq) {
            break;
        }
    }
    std::swap(heap->at(i), heap->at(heap->size() - 1)); // swap with last node
    heap->pop_back(); // pop the last node
    heapify(heap, heap->size()); // heapify
}

// deletes the node with lowest priority
ctNode PQueue::deleteMin(std::vector<ctNode>* heap) {
    ctNode minNode;
    minNode = heap->at(0); // assume first heap is the smallest
    for(size_t i = 1; i < heap->size(); i++) {  // iterate heap to find lowest freq
        if (heap->at(i).freq < minNode.freq) {
            minNode = heap->at(i);
        }
    }
    removeMin(heap, minNode); // call to helper method
    return minNode;
}

// inserts node into the heap
void PQueue::insertNode(std::vector<ctNode>* heap, ctNode* newNode) {
    heap->push_back(*newNode);
    heapify(heap, heap->size());
}

// check if the heap is empty
bool PQueue::isEmpty(std::vector<ctNode>* heap) {
    return heap->empty();
}
