// The following function should be moved into your skiplist.cc file when you
// write that.  It implements the random bit generation.
#include <ctime>                // for time()
#include <cstdlib>              // for rand(), srand(), and RAND_MAX
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "skiplist.h"

snode* update[MAX_HEIGHT];

SkipList::SkipList() {
  header = new snode;
  header->value.clear();
  header->count = 0;
  header->height = MAX_HEIGHT;
  for(int i = 0; i < MAX_HEIGHT; i++) {
    header->next[i] = NULL;
  }
}

int SkipList::randBit(void) {             // return a "random" bit
  static int bitsUpperBd=0;
  static int bits;              // store bits returned by rand()
  if( bitsUpperBd == 0 ) {      // refresh store when empty
    bitsUpperBd = RAND_MAX;
    bits = rand();
  }
  int b = bits & 1;
  bits >>= 1;
  bitsUpperBd >>= 1;
  return b;
}

snode* SkipList::find(std::string word) {
  snode* curr = header;
  int h = curr->height - 1;

  for (int i = h; i >= 0; i--) {
    while (curr->next[i] != NULL && word.compare(curr->next[i]->value) > 0) {
      curr = curr->next[i];
    }
    update[i] = curr;
    if (curr->next[i] != NULL && !curr->next[i]->value.compare(word)) {
      return curr->next[i];
    }
  }
  return NULL;        // word doesn't exist.
}

void SkipList::insert(std::string word, int pageNum) {
  snode* existingNode = find(word);

  if(existingNode != NULL) {   // if word already exists
    existingNode->count = existingNode->count + 1;
    updatePage(word, pageNum);
    return;
  }

  // if doesn't exist
  snode* newNode = new snode;
  newNode->value = word;
  newNode->count = 1;

  int x;
  for(x = 1; x < MAX_HEIGHT; x++) {
    if(randBit() == 1) break;
  }

  newNode->height = x;

  snode* head = header;
  int h = head->height - 1;
  for(int i = h; i >= 0; i--) {
    while (head->next[i] != NULL && word.compare(head->next[i]->value) > 0) {
      head = head->next[i];
    }
  }

  for(int i = 0; i < newNode->height; i++) {
      newNode->next[i] = update[i]->next[i]; //initialize newNode's next pointers
      update[i]->next[i] = newNode; //update next pointers that change
  }
  newNode->pages.push_back(pageNum);
}

void SkipList::updatePage(std::string word, int page) {
  snode* node = find(word);

  if(std::find(node->pages.begin(), node->pages.end(), page) == node->pages.end()) {
    node->pages.push_back(page);
  }
}

void SkipList::printInOrder(std::ostream& output) {
  snode* node = header;
  while(node->next[0] != NULL) {
    std::vector<int> pV = node->next[0]->pages;

  /*  stringstream ss;

    for(size_t i = 0; i < pV.size(); i++) {
      if (i != 0) {
        ss << ",";
      }
      ss << pV[i];
    } */

    stringstream ss;
    
     ss << pV[0];
     int prev = pV[0];
     int intervalFlag = 0;
    
     for(size_t i = 1; i < pV.size(); i++) {
       if (pV[i] - prev == 1) {
         prev = pV[i];
         intervalFlag = 1;
        	if (i != pV.size() - 1)
        	continue;
       }
       if (pV[i] - prev != 1 && intervalFlag == 1) {
         ss << "-" << prev;
         if( prev == pV[i] && i == pV.size() - 1 )
         	continue;                            // if the pages were all consecutive  
         else if (prev != pV[i]) {
         prev = pV[i];                          // if there are another element after interval   
         ss << "," << prev;
         intervalFlag = 0;
         continue;
         }
       }
       if (pV[i] - prev != 1 && intervalFlag == 0) {
         prev = pV[i];
         ss << "," << prev;
         continue;
       }
     }

    std::string pageStr = ss.str();

    output << node->next[0]->value << " (" << node->next[0]->count << ") " <<
    pageStr << endl;

    node = node->next[0]; // to next node
  }
}
