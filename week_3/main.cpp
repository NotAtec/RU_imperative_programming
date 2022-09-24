/********************************************************************
    Course: Imperative Programming - Assignment 3
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 22.09.2022
********************************************************************/

#include <iostream>

using namespace std;

/********************************************************************
    Part 1 - Desktop Test:
    Inclusion:
    Inclusion square root of 0 is 0
    Inclusion square root of 1 is 1
    Inclusion square root of 0.5 is 0.75 for epsilon 0.1
    Inclusion square root of 4 is 2 for epsilon 0.1
    Inclusion square root of 20 is 4.47265625 for epsilon 0.1

    Newton-Raphson:
    Newton Raphson square root of 0 is 0.25 for epsilon 0.1
    Newton Raphson square root of 1 is 1 for epsilon 0.1
    Newton Raphson square root of 0.5 is 0.75 for epsilon 0.1
    Newton Raphson square root of 4 is 2.0006097561 for epsilon 0.1
    Newton Raphson square root of 20 is 4.47831444547 for epsilon 0.1

    Part 4 - Comparing the Algorithms:
    Inclusion:
    v = 0
    0       0       0       1

    v = 1
    0       0       1       1

    v = 0.5
    0       0       0.5     1
    1       0.5     0.75    1

    v = 4
    0       0       2       4

    v = 20
    0       0       10      20
    1       0       5       10
    2       0       2.5     5
    3       2.5     3.75    5
    4       3.75    4.375   5
    5       4.375   4.6875  5
    6       4.375   4.53125 4.6875
    7       4.375   4.45312 4.53125
    8       4.45312 4.49219 4.53125
    9       4.45312 4.47266 4.49219

    Newton Raphson:
    v = 0
    0       1
    1       0.5
    2       0.25

    v = 1
    0       1

    v = 0.5
    0       1
    1       0.75

    v = 4
    0       4
    1       2.5
    2       2.05
    3       2.00061

    v = 20
    0       20
    1       10.5
    2       6.20238
    3       4.71347
    4       4.47831
********************************************************************/

/********************************************************************
    Function Definitions
********************************************************************/
void inclusion_output(double lower, double upper, double est, double v,
                      double eps) {
  if (lower * lower == v)
    cout << "Inclusion square root of " << v << " is " << lower << endl;
  else if (upper * upper == v)
    cout << "Inclusion square root of " << v << " is " << upper << endl;
  else
    cout << "Inclusion square root of " << v << " is " << est << " for epsilon "
         << eps << endl;
}

/********************************************************************
    Assignment part 2: Inclusion
********************************************************************/
void inclusion(double epsilon, double v) {
  double x = 0.0;         // The current estimation
  double a = 0.0;         // The lower estimation bound
  double b = max(v, 1.0); // The upper estimation bound
  int n = 0;              // Iteration

  // Since return values aren't allowed to be used yet, this has to be inside
  // this function due to scope. "Proper" styleguide adherence would make me
  // write a function here that returns the value to assign to x.
  if (a * a == v)
    x = 0;
  else if (b * b == v)
    x = 1;
  else
    x = (a + b) / 2;

  cout << n << '\t' << a << '\t' << x << '\t' << b << endl;

  // Same principle regarding return values applies here. In case of proper
  // style-guide adherance I would separate this part of the function into it's
  // own sub-function aswell, which then returns the final value of 'x'.
  while (abs(x * x - v) > epsilon) {
    x = (a + b) / 2;
    if (!(n == 0))
      cout << n << '\t' << a << '\t' << x << '\t' << b << endl;

    n++;

    if (x * x < v)
      a = x;
    else
      b = x;
  }

  inclusion_output(a, b, x, v, epsilon);
}

/********************************************************************
    Assignment part 3: Newton-Raphson
********************************************************************/
void newtonraphson(double epsilon, double v) {
  double x = max(v, 1.0); // Initial Estimation
  int n = 0;              // Iteration
  cout << n << '\t' << x << endl;

  while (abs(x * x - v) > epsilon) {
    x = x - (x * x - v) / (2 * x);
    n++;
    cout << n << '\t' << x << endl;
  }

  cout << "Newton Raphson square root of " << v << " is " << x
       << " for epsilon " << epsilon << endl;
}

int main() {
  inclusion(0.1, 0.0);
  inclusion(0.1, 1.0);
  inclusion(0.1, 0.5);
  inclusion(0.1, 4.0);
  inclusion(0.1, 20.0);

  newtonraphson(0.1, 0.0);
  newtonraphson(0.1, 1.0);
  newtonraphson(0.1, 0.5);
  newtonraphson(0.1, 4.0);
  newtonraphson(0.1, 20.0);

  return 0;
}
