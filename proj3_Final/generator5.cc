#include <iostream>
#include <cstdlib> // for atoi
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2){
    cerr << "Wrong number of arguments!" << endl;
    return 1;
  }

  int n = atoi(argv[1]);

  // In incrementing order, insert even numbers
  for(int i = 2; i <= n/2; i = i+2) {
    cout << "I " << i << endl;
  }

  // In incrementing order, remove odd numbers
  for(int i = 1; i <= n/2; i = i+2) {
    cout << "R " << i << endl;
  }

  return 0;
}
