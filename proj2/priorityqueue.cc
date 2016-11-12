#include <string>
#include <vector>
#include <algorithm>
#include "priorityqueue.h"

PQueue::PQueue(int freq[256]) {
  for(int i = 0; i < 256; i++) {
    if(freq[i] != 0) {
      pnode newNode;
      pnode.ch = (char) i;
      pnode.freq = freq[i];
      heap.push_back(newNode);
    }
  }
  heapify(heap, heap.size());
}

// from binaryHeap.cp; edited so that heap now prioritizes high freq values.
void PQueue::swapDown(std::vector<pnode> heap, size_t i, size_t size) {
    size_t leftChild = 2 * i + 1;
    size_t rightChild = 2 * i + 2;
    size_t max = i;
    if (leftChild < size && heap[leftChild].freq > heap[max].freq)
        max = leftChild;
    if (rightChild < size && heap[rightChild].freq > heap[max].freq)
        max = rightChild;
    if (max != i) {
        std::swap(heap[i], heap[max]);
        swapDown(heap, max, size);
    }
}

// from binaryHeap.cp; edited so it can be used on vector
void PQueue::heapify(std::vector<pnode> heap, size_t size) {
    for (size_t i = (size - 2) / 2; i >= 0; i--)
        swapDown(heap, i, size);
}

pnode PQueue::deleteMin() {
    // TODO
}

bool PQueue::isEmpty() {
  return heap.empty();
}
