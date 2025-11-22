#include <iostream>
#include <stack>
#include <string>

using std::cout, std::endl;
using std::stack;
using std::string, std::string_view;

struct RPNEntry
{
  RPNEntry(double value, char op = 'n') : value_(value), op_(op) {}

  double value_;
  char op_;
};

class RPNStack
{
public:
  RPNStack() : operations_{} {}
  void push(const RPNEntry &r) { operations_.push(r); };

  double expression();
  double value();

private:
  stack<RPNEntry> operations_;
};

double RPNStack::value()
{
  auto val = operations_.top().value_;
  operations_.pop();

  return val;
}

double RPNStack::expression()
{
  auto item = operations_.top();

  if (item.op_ == 'n')
    return value();

  operations_.pop();

  switch (item.op_)
  {
  case '+':
    return expression() + expression();

  case '-': // - has to be reversed
  {
    auto right = expression();
    return expression() - right;
  }

  case '*':
    return expression() * expression();

  case '/': // / has to be reversed
  {
    auto right = expression();

    return expression() / right;
  }

  default:
    return 0.0;
  }
}

void print(const stack<int> &q)
{
  if (q.empty())
  {
    cout << "The stack is empty\n";
    return;
  }

  cout << "The stack contains  " << q.size() << " elements\n";
  cout << "The top element is  " << q.top() << endl;
}

void stacks()
{
  stack<int> s;

  cout << "Simple Stack\n";

  s.push(4);
  s.push(3);
  s.push(2);
  s.push(1);

  print(s);

  cout << "The stack goes  ";

  while (!s.empty())
  {
    cout << s.top() << ", ";
    s.pop();
  }

  cout << endl;
}

void rpn_calculator()
{
  RPNStack rpn;

  cout << "\nRPN calculator\n";

  rpn.push({10});
  rpn.push({5});
  rpn.push({0, '+'});

  cout << "10 + 5 = " << rpn.expression() << endl;

  rpn.push({10});
  rpn.push({5});
  rpn.push({0, '-'});

  cout << "10 - 5 = " << rpn.expression() << endl;

  rpn.push({10});
  rpn.push({5});
  rpn.push({0, '*'});

  cout << "10 * 5 = " << rpn.expression() << endl;

  rpn.push({10});
  rpn.push({5});
  rpn.push({0, '/'});

  cout << "10 / 5 = " << rpn.expression() << endl;

  rpn.push({5.5});
  rpn.push({6.5});
  rpn.push({0, '+'});

  rpn.push({2.4});
  rpn.push({3.6});
  rpn.push({0, '+'});
  rpn.push({0, '/'});
  cout << "(5.5 + 6.5) / (2.4 + 3.6) = " << rpn.expression() << endl;
}

int main()
{
  stacks();
  rpn_calculator();
}
