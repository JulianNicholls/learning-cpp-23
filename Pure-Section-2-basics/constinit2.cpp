int getValue(int v) {
  return v * 2;
}

// Like this, the order of linking is important.
// run2 constinit1 constinit2 yields b = 0
// run2 constinit2 constinit1 yields b = 10
// int a = getValue(5);

// This fixes it.
int& getA() {
  static int a = getValue(5);

  return a;
}

// But better still

constexpr int getValueC(int y) {
  return y * 2;
}

constinit int a = getValueC(5);
