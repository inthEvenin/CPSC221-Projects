#include <vector>
#include <algorithm>

struct pnode {
  char ch;
  int freq;
}

class PQueue {
public:
  PQueue(int freq[256]);
  void swapDown(int* heap, int i, int size);
  void heapify(int* heap, int size);
  pnode deleteMin(void);
  void insert(char ch, int freq);
  bool isEmpty();

private:
  std::vector<pnode> heap;
}
