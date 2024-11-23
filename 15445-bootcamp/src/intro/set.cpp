// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the set container library header.
#include <set>

int main() {
  std::set<int> int_set;
  for (int i = 1; i <= 5; ++i) {
    int_set.insert(i);
  }

  for (int i = 6; i <= 10; ++i) {
    int_set.emplace(i);
  }

  // find by iterator
  auto search = int_set.find(2);
  if (search != int_set.end()) {
    std::cout << "Element 2 is in int_set.\n";
  }

  // count also can check
  if (int_set.count(11) == 0) {
    std::cout << "Element 11 is not in the set.\n";
  }
  if (int_set.count(3) == 1) {
    std::cout << "Element 3 is in the set.\n";
  }

  // erase one
  int_set.erase(int_set.begin());
  // erase range
  int_set.erase(int_set.find(9), int_set.end());

  std::cout << "Printing the elements of the iterator with a for-each loop:\n";
  for (const int &elem : int_set) {
    std::cout << elem << " ";
  }
  std::cout << "\n";

  return 0;
}