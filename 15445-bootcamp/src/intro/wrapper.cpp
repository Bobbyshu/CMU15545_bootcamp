#include <iostream>
#include <utility>

class IntPtrManager {
  public:
    IntPtrManager() {
      // allocate int memory in heap
      ptr_ = new int;
      *ptr_ = 0;
    }

    IntPtrManager(int val) {
      ptr_ = new int;
      *ptr_ = val;
    }

    ~IntPtrManager() {
      if (ptr_) {
        delete ptr_;
      }
    }

    // move constructor
    IntPtrManager(IntPtrManager&& other) {
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }

    // move assignment operator
    IntPtrManager &operator=(IntPtrManager &&other) {
      if (ptr_ == other.ptr_) {
        return *this;
      }
      if (ptr_) {
        delete ptr_;
      }
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
      return *this;
    }

    // We delete the copy constructor and the copy assignment operator,
    // so this class cannot be copy-constructed. 
    IntPtrManager(const IntPtrManager &) = delete;
    IntPtrManager &operator=(const IntPtrManager &) = delete;

    // Setter function.
    void SetVal(int val) {
      *ptr_ = val;
    }

    // Getter function.
    int GetVal() const {
      return *ptr_;
    }

  private:
    int *ptr_;
};

int main() {
  // We initialize an instance of IntPtrManager. After it is initialized, this
  // class is managing an int pointer.
  IntPtrManager a(445);

  // Getting the value works as expected.
  std::cout << "1. Value of a is " << a.GetVal() << std::endl;

  // Setting the value goes through, and the value can retrieved as expected.
  a.SetVal(645);
  std::cout << "2. Value of a is " << a.GetVal() << std::endl;

  // Now, we move the instance of this class from the a lvalue to the b lvalue
  // via the move constructor.
  IntPtrManager b(std::move(a));

  // Retrieving the value of b works as expected because b is now managing the
  // data originally constructed by the constructor that created a. Note that
  // calling GetVal() on a will segfault, and a is supposed to effectively be
  // empty and unusable in this state.
  std::cout << "Value of b is " << b.GetVal() << std::endl;

  // Once this function ends, the destructor for both a and b will be called.
  // a's destructor will note that the ptr_ it is managing has been set to 
  // nullptr, and will do nothing, while b's destructor should free the memory
  // it is managing.

  return 0;
}