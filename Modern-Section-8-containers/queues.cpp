#include <iostream>
#include <queue>
#include <string>

using std::cout, std::endl;
using std::queue, std::priority_queue;
using std::string, std::string_view;

class Bug
{
public:
  Bug(std::string_view problem, int severity) : problem_(problem), severity_(severity) {}

  bool operator<(const Bug &other) const;

  string to_string() const;

private:
  string problem_;
  int severity_;
};

bool Bug::operator<(const Bug &other) const
{
  return severity_ < other.severity_;
}

string Bug::to_string() const
{
  return problem_ + " (" + std::to_string(severity_) + ")";
}

void print(const queue<int> &q)
{
  if (q.empty())
  {
    cout << "The queue is empty\n";
    return;
  }

  cout << "The queue contains   " << q.size() << " elements\n";
  cout << "The first element is " << q.front() << endl;
  cout << "The last  element is " << q.back() << endl;
}

void print(const priority_queue<int> &q)
{
  if (q.empty())
  {
    cout << "The queue is empty\n";
    return;
  }

  cout << "The queue contains  " << q.size() << " elements\n";
  cout << "The top element is  " << q.top() << endl;
}

void print(priority_queue<Bug> &q)
{
  if (q.empty())
  {
    cout << "The queue is empty\n";
    return;
  }

  cout << "The queue contains  " << q.size() << " elements\n";
  cout << "The top element is  " << q.top().to_string() << endl;

  while(!q.empty()) {
    cout << "  " << q.top().to_string() << endl;
    q.pop();
  }
}

void queues()
{
  queue<int> q;

  cout << "Queue\n";

  q.push(17);
  q.push(23);
  q.push(9);
  q.push(45);
  q.push(12);

  print(q);

  q.push(1);
  q.pop();

  cout << "\nAfter insertion and removal\n";
  print(q);
}

void priority_queues()
{
  // A list of ints doesn't really demonstrate this well...
  priority_queue<int> pq;

  cout << "\nPriority Queue\n";

  pq.push(17);
  pq.push(23);
  pq.push(9);
  pq.push(45);
  pq.push(12);

  print(pq);

  pq.pop();
  pq.push(47);

  cout << "\nAfter insertion and removal\n";
  print(pq);
}

void bugfix_queue()
{
  priority_queue<Bug> bq;

  cout << "\nBug queue\n";

  print(bq);

  bq.push({"The dark mode doesn't work everywhere", 3});
  bq.push({"Can't save defects", 5});
  bq.push({"One page is misaligned on small mobiles", 3});
  bq.push({"The list of defects is empty", 5});

  print(bq);
}

int main()
{
  queues();
  priority_queues();
  bugfix_queue();
}
