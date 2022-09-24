/********************************************************************
    Course: Imperative Programming - Bonus Assignment 3
    Authors: Jeroen Brinkhorst [S1101799]
             Andrei Ujica [S1102725]
    Date: 22.09.2022
********************************************************************/

#include <cmath>
#include <iostream>

using namespace std;

/********************************************************************
    Constant & Function Definitions
********************************************************************/
const double PI = 3.1415926; // the number pi
const double EPS = 0.00001;  // the precision used in the test (main)

double factorial(int x) {
  double v = 1;
  for (int i = 1; i <= x; i++) {
    v = v * i;
  }
  return v;
}

double power(double x, int exponent) {
  double res = 1;
  for (int i = 0; i < exponent; i++) {
    res = res * x;
  }
  return res;
}

/********************************************************************
    Bonus assignment: computing approximations of sinus and cosinus
********************************************************************/
// sinus (x,eps,max_no_steps) computes and prints the approximations of sin
// (`x`), with an accuracy of `eps` and at most `max_no_steps`
void sinus(double x, double eps, int max_no_steps) {
  double prev = 0.0;
  double est = 0.0;
  int i = 0;

  do {
    prev = est;
    est += (power(-1, i) * power(x, (2 * i + 1))) / factorial(2 * i + 1);

    if (i == max_no_steps)
      prev = est; // Set previous estimation to current so while loop will exit

    i++;
  } while (abs(est - prev) > eps);

  cout << "sin (" << x << ") = " << est << endl;
}

// cos (x,eps,max_no_steps) computes and prints the approximations of cos (`x`),
// with an accuracy of `eps` and at most `max_no_steps`
void cosinus(double x, double eps, int max_no_steps) {
  double prev = 0.0;
  double est = 0.0;
  int i = 0;

  do {
    prev = est;
    est += (power(-1, i) * power(x, (2 * i))) / factorial(2 * i);

    if (i == max_no_steps)
      prev = est; // Set previous estimation to current so while loop will exit

    i++;
  } while (abs(est - prev) > eps);

  cout << "cos (" << x << ") = " << est << endl;
}

int main() {
  for (double angle = 0; angle <= PI; angle += PI / 100) {
    sinus(angle, EPS, 20);
    cout << "sin (" << angle << ") = " << sin(angle) << endl;
    cosinus(angle, EPS, 20);
    cout << "cos (" << angle << ") = " << cos(angle) << endl;
  }

  return 0;
}
