/********************************************************************
    Course: Imperative Programming - Assignment 2
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 22.09.2022
********************************************************************/

#include <iostream>

using namespace std;

/********************************************************************
    Desktop Test:
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

********************************************************************/

/********************************************************************
    Type, Variable & Function Definitions
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

double estimation_loop(double x, double a, double b, double v, double epsilon) {
  while (abs(x * x - v) > epsilon) {
    x = (a + b) / 2;
    if (x * x < v)
      a = x;
    else
      b = x;
  }
  return x;
}
/********************************************************************
    Assignment part 2: Inclusion
********************************************************************/
void inclusion(double epsilon, double v) {
  double x = 0.0; // The current estimation
  double a = 0.0; // The lower estimation bound
  double b = 0.0; // The upper estimation bound

  b = std::max(v, 1.0);

  if (a * a == v)
    x = 0;
  else if (b * b == v)
    x = 1;
  else
    x = (a + b) / 2;

  x = estimation_loop(x, a, b, v, epsilon);
  inclusion_output(a, b, x, v, epsilon);
}

/********************************************************************
    Assignment part 3: Newton-Raphson
********************************************************************/
void newtonraphson(double epsilon, double v) {
  // implement this function
}

int main() {
  inclusion(0.1, 0.0);
  inclusion(0.1, 1.0);
  inclusion(0.1, 0.5);
  inclusion(0.1, 4.0);
  inclusion(0.1, 20.0);
  return 0;
}
