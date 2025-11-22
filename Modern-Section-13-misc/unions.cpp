#include <iomanip>
#include <iostream>
#include <variant>

using std::cout, std::endl;

union bytes8
{
  uint8_t bytes[8];
  long l;
  double d;
};

enum ValueType
{
  Bytes,
  Long,
  Double
};

class BytesWrapper
{
public:
  void set_bytes(uint8_t *b)
  {
    memcpy(value_.bytes, b, 8);
    current_ = Bytes;
  }

  void set_double(double d)
  {
    value_.d = d;
    current_ = Double;
  }

  void set_long(long l)
  {
    value_.l = l;
    current_ = Long;
  }

  void get_bytes(char *b) const
  {
    if (current_ == Double)
      memcpy(b, value_.bytes, 8);
    else
      throw std::invalid_argument("Bytes member not current");
  }

  double get_double() const
  {
    if (current_ == Double)
      return value_.d;
    else
      throw std::invalid_argument("Double member not current");
  }

  long get_long() const
  {
    if (current_ == Long)
      return value_.l;
    else
      throw std::invalid_argument("Long member not current");
  }

  void set_current(ValueType v)
  {
    current_ = v;
  }

private:
  bytes8 value_;
  ValueType current_ = Bytes;
};

int main()
{
  bytes8 value;

  value.d = 6'138'297'456.465'523;

  cout << "d:     " << std::fixed << value.d << endl;
  cout << "l:     " << value.l << endl;
  cout << "bytes: ";

  for (size_t i = 0; i < sizeof(bytes8); ++i)
    cout << std::hex << std::setw(2) << std::setfill('0') << (int)value.bytes[i] << ' ';

  cout << std::dec << std::setfill(' ') << endl;

  // It seems to me that the most useful feature of a union is being hamstrung,
  // both by the BytesWrapper and std::variant.

  BytesWrapper b;

  b.set_double(113'654'876'876.345678);

  try
  {
    cout << "\nBytesWrapper double = " << b.get_double() << endl;
    cout << "BytesWrapper long = " << b.get_long() << endl;
  }
  catch (std::invalid_argument &e)
  {
    cout << "Cannot access long: " << e.what() << endl;
  }

  b.set_current(Long);

  cout << "\nBytesWrapper long = " << b.get_long() << endl;

  // std::variant<char[8], int, double> var;   // Not possible
  std::variant<long, double> var;

  var = 143'684'826'856.348678;

  if (std::holds_alternative<double>(var))
    cout << "\nVariant: " << get<double>(var) << endl;

  if (std::holds_alternative<long>(var))
    cout << "Variant: " << get<0>(var) << endl;
  else
    cout << "Variant is not a long at the moment\n";
}
