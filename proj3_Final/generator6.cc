#include <iostream>
#include <cstdlib> // for atoi
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2){
    cerr << "Wrong number of arguments!" << endl;
    return 1;
  }

  int n = atoi(argv[1]);

  // In incrementing order, insert
  for(int i = 1; i <= n/4; i++) {
    cout << "I " << i << endl;
  }

  // find the middle number multiple times
  for(int i = 1; i <= n/4; i++) {
    cout << "F " << n/8 << endl;
  }

  // keep remove the one that wasn't inserted
  for(int i = 1; i <= n/4; i++) {
    cout << "F " << n+1 << endl;
  }

  // find in incrementing order
  for(int i = 1; i <= n/4; i++) {
    cout << "F " << i << endl;
  }

  return 0;
}
