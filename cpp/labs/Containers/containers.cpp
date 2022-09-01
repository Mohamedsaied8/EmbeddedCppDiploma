#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

int main() {

  // initialize a set of int type, doesn't allow duplication
  set<int> numbers = {1, 100, 10, 70, 100};

 // initialize an unordered_set of int type
  unordered_set<int> numbers = {1, 100, 10, 70, 100};

  // print the set
  cout << "Numbers are: ";
  for(auto &num: numbers) {
    cout << num << ", ";
  }

  return 0;
}