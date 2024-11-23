// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the unordered_map container library header.
#include <unordered_map>
// Includes the C++ string library.
#include <string>
// Includes std::make_pair.
#include <utility>

int main() {
  std::unordered_map<std::string, int> map;
  
  // insert way
  map.insert({"foo", 2});
  map.insert(std::make_pair("jignesh", 445));
  // insert in list 
  map.insert({{"spam", 1}, {"eggs", 2}, {"garlic rice", 3}});
  map["bacon"] = 5;

  // same as set
  auto result = map.find("jignesh");
  // get value
  size_t count = map.count("spam");
  if (count == 1) {
    std::cout
        << "A key-value pair with key spam exists in the unordered map.\n";
  }

  // erase key or iterator
  map.erase("eggs");
  map.erase(map.find("garlic rice"));

  std::cout << "Printing the elements of the iterator with a for-each loop:\n";
  for (const std::pair<const std::string, int> &elem : map) {
    std::cout << "(" << elem.first << ", " << elem.second << "), ";
  }
  std::cout << "\n";

  // get key or value
  // we need to add & 
  // otherwise it will copy pair everytime
  // with & we can just get the reference
  for (const auto& [key, _] : map) {
        std::cout << "Key: " << key << std::endl;
    }

  for (const auto& [_, value] : map) {
      std::cout << "Value: " << value << std::endl;
  }

  return 0;
}