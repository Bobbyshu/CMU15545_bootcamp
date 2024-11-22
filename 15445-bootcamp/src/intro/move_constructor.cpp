#include <iostream>
// Includes the utility header for std::move.
#include <utility>
// Includes the C++ string library.
#include <string>
// Includes the header for uint32_t.
#include <cstdint>
#include <vector>

class Person {
  public:
    // default constructor
    Person(): age_(0), nicknames_({}), valid_(true) {}

    // constructor
    // && for rvalue reference 
    Person(uint32_t age, std::vector<std::string> &&nicknames)
      : age_(age), nicknames_(std::move(nicknames)), valid_(true) {}

    // Move constructor
    Person(Person &&person) 
      : age_(person.age_), nicknames_(std::move(person.nicknames_)), valid_(true) {
        std::cout << "Calling the move constructor for class Person." << std::endl;
        person.valid_ = false;
    }

    Person &operator=(Person &&other) {
      std::cout << "Calling the move assignment operator for class Person.\n";
      age_ = other.age_;
      nicknames_ = std::move(other.nicknames_);
      valid_ = true;

      // The moved object's validity tag is set to false.
      other.valid_ = false;
      return *this;
    }

    // We delete the copy constructor and the copy assignment operator,
    // so this class cannot be copy-constructed.
    // delete copy function
    Person(const Person &) = delete;
    Person &operator=(const Person &) = delete;


    uint32_t GetAge() {
      return age_;
    }

    std::string &GetNicknameAtI(size_t i) { return nicknames_[i]; }

    void PrintValid() {
      if (valid_) {
        std::cout << "Object is valid." << std::endl;
      } else {
        std::cout << "Object is invalid." << std::endl;
    }
  }
  private:
    uint32_t age_;
    std::vector<std::string> nicknames_;
    bool valid_;
};

int main() {
  Person bobby(23, {"Bobbyshu", "Yunmu Shu"});
  std::cout << "Bobby's validity: ";
  bobby.PrintValid();

  // To move the contents of the andy object to another object, we can use
  // std::move in a couple ways. This method calls the move assignment operator.
  Person shu;
  shu = std::move(bobby);

  std::cout << "Printing bobby's validity: ";
  bobby.PrintValid();
  std::cout << "Printing shu's validity: ";
  shu.PrintValid();

  Person Yunmu(std::move(shu));
  std::cout << "Printing bobby's validity: ";
  bobby.PrintValid();
  std::cout << "Printing shu's validity: ";
  shu.PrintValid();
  std::cout << "Printing Yunmu's validity: ";
  Yunmu.PrintValid();


  // However, note that because the copy assignment operator is deleted, this code 
  // will not compile. The first line of this code constructs a new object via the
  // default constructor, and the second line invokes the copy assignment operator
  // to re-initialize andy3 with the deep-copied contents of andy2. Try uncommenting
  // these lines of code to see the resulting compiler errors.
  // Person bobby3;
  // bobby3 = bobby;

  // Because the copy constructor is deleted, this code will not compile. Try
  // uncommenting this code to see the resulting compiler errors.
  // Person bobby4(bobby);

  return 0;
}