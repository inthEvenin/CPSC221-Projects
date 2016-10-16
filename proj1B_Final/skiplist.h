#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>                // for time()
#include <cstdlib>              // for rand(), srand(), and RAND_MAX

#define MAX_HEIGHT 16

using namespace std;

struct snode {
  string value;
  int count;
  int height;
  vector<int> pages;
  snode* next[MAX_HEIGHT];
};

// skiplist class
class SkipList {
public:
  int randBit(void);
  SkipList(void);
  snode* find(std::string word);
  void insert(std::string word, int page);
  void updatePage(std::string word, int page);
  void printInOrder(ostream& output);

private:
  snode* header;
};
