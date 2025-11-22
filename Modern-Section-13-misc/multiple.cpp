#include <iostream>

using std::cout, std::endl;

struct Params
{
};

// Hardware class
class HardwareDevice
{
public:
  HardwareDevice() { cout << "  Calling HardwareDevice constructor\n"; }
  ~HardwareDevice() { cout << "  Calling HardwareDevice destructor\n"; }

  bool initialise([[maybe_unused]] Params &)
  {
    cout << "  Calling HardwareDevice::initialise()\n";
    return true;
  }

  void get_data()
  {
    cout << "  Calling HardwareDevice::get_data()\n";
  }
};

// User interaction class
class TouchResponder
{
public:
  TouchResponder() { cout << "  Calling TouchResponder constructor\n"; }
  ~TouchResponder() { cout << "  Calling TouchResponder destructor\n"; }

  void initialise()
  {
    cout << "  Calling TouchResponder::initialise()\n";
  }

  bool touch_down()
  {
    cout << "  Calling TouchResponder::touch_down()\n";
    return true;
  }
};

// Classes which inherit from both HardwareDevice and TouchResponder
class Mouse : public HardwareDevice, public TouchResponder
{
public:
  Mouse() { cout << "Calling Mouse constructor\n"; }
  ~Mouse() { cout << "Calling Mouse destructor\n"; }

  bool initialise_mouse(Params &params)   // or initialise()
  {
    cout << "Calling Mouse::initialise()\n";
    HardwareDevice::initialise(params);
    TouchResponder::initialise();
    return true;
  }

  void process()
  {                   // Member function in Mouse class
    if (touch_down()) // Mouse inherits touch_down() from TouchResponder
      get_data();     // Mouse inherits get_data() from HardwareDevice
  }
};

int main()
{
  Mouse mouse;
  Params params;
  // mouse.initialise();          // This doesn't work natively
  // mouse.initialise(params);    // Nor does this

  mouse.initialise_mouse(params); // This clears up the ambiguity
}
