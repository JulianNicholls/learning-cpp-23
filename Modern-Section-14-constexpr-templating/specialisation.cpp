#include <iostream>
#include <string>

using std::cout, std::endl;
using std::string;
using namespace std::string_literals;

template <typename T> T add(T a, T b){
  return a + b;
}

// I'm not sure if this is an elegant solution, it's certainly not thread-safe,
// and may have other horrible gotchas too.
// This also doesn't specialise for char*, as I discovered below.
template <> const char* add(const char* a, const char* b) {
  static string temp;

  temp = string(a) + b;

  return temp.c_str();
}

int main() {
  cout << "add(34, 45): " << add(34, 45) << endl;
  cout << "add(34.7, 45.8): " << add(34.7, 45.8) << endl;
  cout << R"(add("left "s, "right"s): ")" << add("left "s, "right"s) << "\"\n";

  // This is impossible without the specialisation
  cout << R"(add("left ", "right"): ")" << add("left ", "right") << "\"\n";

  // Specialisation doesn't translate to char*
  // char m[]  = "mutable ";
  // char cs[] = "c-string";

  // cout << "add(m, cs): \"" << add(m, cs) << "\"\n";
}
