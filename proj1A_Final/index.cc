#include <iostream>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cctype>       // provides isalpha() and tolower()
#include <vector>       // provides vector
#include <algorithm>


using namespace std;

// The following function should be moved into your skiplist.cc file when you
// write that.  It implements the random bit generation.
#include <ctime>                // for time()
#include <cstdlib>              // for rand(), srand(), and RAND_MAX


// structs an entry with string value, word count, and vector of pages.
struct Entry {
  string value;
  int count;
  vector<int> pages;
};

vector<Entry> index; // vector to store entries

// iterates through the entries and returns true if it contains the entry
// with given word string. Implemented linear search algorithm
bool find(string word, vector<Entry> entries) {
  for(size_t i = 0; i < entries.size(); i++) {
    if(entries[i].value == word) {
      return true;
    }
  }
  return false;
}

// another version of linear search. if num exists in int vector v returns true.
// false otherwise.
bool find(int num, vector<int> v) {
  for(size_t i = 0; i < v.size(); i++) {
    if(v[i] == num) {
      return true;
    }
  }
  return false;
}

// interate through the index and increments the count and add page nuumbers
void updateEntry(string word, int pageNum) {
  for(size_t i = 0; i < index.size(); i++) {
    if(index[i].value == word) {
      index[i].count = index[i].count + 1;
      if (!find(pageNum, index[i].pages)) {
        index[i].pages.push_back(pageNum);
      }
    }
  }
}

// alphabetically sorting option for sort fx
bool compareEntry(const Entry& lhs, const Entry& rhs) {
  return lhs.value < rhs.value;
}

// Adds entry and keep it sorted
void insert(string word, int pageNum) {
  if(find(word, index)) {
    updateEntry(word, pageNum);
  } else {
    Entry entry;
    entry.value = word;
    entry.count = 1;
    entry.pages.push_back(pageNum);

    index.push_back(entry);

    sort(index.begin(), index.end(), compareEntry);
  }
}

int randBit(void) {             // return a "random" bit
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


// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
          it == line.begin() || it+1 == line.end() ||
          !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
        *it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}

// helper method to create pages string given vector of ints
string pagesString(vector<int> pages) {
  stringstream ss;

  for(size_t i = 0; i < pages.size(); i++) {
    if (i != 0) {
      ss << ",";
    }
    ss << pages[i];
  }

  return ss.str();
}

// writes the index into the output textfile.
void printInOrder(ostream & output, vector<Entry> entries) {
  for(size_t i = 0; i < entries.size(); i++) {
    string pagesNum = pagesString(entries[i].pages);
    output << entries[i].value << " (" << entries[i].count << ") "
    << pagesNum << endl;
  }
}

int main(int argc, char *argv[]) {

  if( argc != 3 ) {
    cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
    exit(1);
  }

  ifstream fin;
  fin.open(argv[1]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }

  ofstream fout;
  fout.open(argv[2]);
  if( !fout.is_open() ) {
    cerr << "Unable to open " << argv[2] << endl;
    exit(3);
  }

  string line, word;
  int numLines = 0;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    ++numLines;
    int numPage = numLines/40 + 1;
    while( iss >> word ) {
      insert(word, numPage);
    }
  }
  printInOrder(fout, index);
}
