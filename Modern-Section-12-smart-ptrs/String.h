#include <iostream>

using std::cout, std::endl;

class String
{
public:
  String(int size) : size_(size), data_{new char[size]}, counter_{new int{0}}
  {
    ++*counter_; // "this" has been bound - increment the counter
    cout << "Constructor: data = " << static_cast<void *>(data_) << ", counter = " << counter_ << ", count = " << *counter_ << endl;
  }

  ~String() noexcept
  {
    cout << "Destructor: data = " << (void *)data_ << ", counter = " << counter_;
    if (counter_)
    {
      cout << ", count = " << *counter_ << endl;
      // Any other code needed to clean up the object
      --*counter_; // An object has been unbound - decrement the counter
      if (*counter_ == 0)
      { // If we are the last bound object, release the memory
        cout << "Deleting shared memory at " << static_cast<void *>(data_) << endl;
        cout << "Deleting counter at " << static_cast<void *>(counter_) << endl;
        delete counter_;
        delete[] data_;
      }
    }
    else
      cout << endl;
  }

  String(const String &arg);
  String(String &&arg) noexcept;

  String &operator=(const String &arg);
  String &operator=(String &&arg) noexcept;

  int length() const { return size_; }
  int count() const { return *counter_; }

  friend void swap(String &l, String &r) noexcept;

  void print() const;

private:
  int size_;
  char *data_;
  int *counter_; // The reference counter - also allocated on the heap
};

inline void swap(String &l, String &r) noexcept
{
  using std::swap;

  swap(l.size_, r.size_);
  swap(l.data_, r.data_);
  swap(l.counter_, r.counter_);
}
