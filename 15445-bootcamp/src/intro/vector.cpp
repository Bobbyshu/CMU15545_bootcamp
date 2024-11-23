#include <vector>
#include <algorithm>
#include <iostream>

void print_int_vector(const std::vector<int> &vec) {
  for (const int &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

int main() {
  std::vector<int> int_vector = {0, 1, 2, 3, 4, 5, 6};
  int_vector.push_back(7);
  // emplace_back faster
  int_vector.emplace_back(8);


  // erase specific number
  int_vector.erase(int_vector.begin() + 2);
  std::cout << "Printing the elements of int_vector after erasing "
               "int_vector[2] (which is 2)\n";
  print_int_vector(int_vector);

  // erase range number
  int_vector.erase(int_vector.begin() + 1, int_vector.end());
  std::cout << "Printing the elements of int_vector after erasing all elements "
               "from index 1 through the end\n";
  print_int_vector(int_vector);

  int_vector = {0, 1, 2, 3, 4, 5, 6};
  // remove in condition
  int_vector.erase(
        std::remove_if(int_vector.begin(), int_vector.end(),
                       [](int num) { return num % 2 != 0; }),
        int_vector.end());
  print_int_vector(int_vector);

  return 0;
}