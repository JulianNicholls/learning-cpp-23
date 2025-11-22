#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals;

using std::cout, std::endl;

int main()
{
  seconds s;
  cout << "Uninitialised seconds variable = " << s.count() << endl;

  auto hours = 5h;
  auto mins = 10min;
  auto secs = 2s;
  auto msecs = 20ms;
  auto usecs = 250us;
  auto nsecs = 300ns;

  cout << "hours = " << hours.count() << " hours (" << hours << ")\n";
  cout << "mins  = " << mins.count() << " mins\n";
  cout << "secs  = " << secs.count() << " secs\n";
  cout << "msecs = " << msecs.count() << " msecs\n";
  cout << "usecs = " << usecs.count() << " usecs\n";
  cout << "nsecs = " << nsecs.count() << " nsecs\n";

  auto hm = hours + mins;
  auto sm = secs + msecs;
  auto un = usecs + nsecs;

  cout << "\nhm = " << hm.count() << " minutes\n";
  cout << "sm = " << sm.count() << " msecs\n";
  cout << "un = " << un.count() << " nsecs\n";

  seconds as_sec = mins;
  auto trunc = duration_cast<seconds>(sm);

  cout << "\nmins as secs = " << as_sec.count() << " seconds (" << as_sec << ")\n";
  cout << "truncated hm = " << trunc.count() << " seconds (" << trunc << ")\n";
}
