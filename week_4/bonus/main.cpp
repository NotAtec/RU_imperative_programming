#include <iostream>

using namespace std;

enum Month
{
  January = 1, February, March, April, May, June,
  July, August, September, October, November, December
};

// We override the cout operator in order to be able to print out 
// the name of the month
ostream& operator<<(ostream& out, Month m) {
    switch (m) {
        case January: out << "January"; break;
        case February: out << "February"; break;
        case March: out << "March"; break;
        case April: out << "April"; break;
        case May: out << "May"; break;
        case June: out << "June"; break;
        case July: out << "July"; break;
        case August: out << "August"; break;
        case September: out << "September"; break;
        case October: out << "October"; break;
        case November: out << "November"; break;
        case December: out << "December"; break;
    }
    return out;
}

// We define an enum for easier to read code
enum Weekday
{
  Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday,
  Sunday
};


/********************************************************************
  Easter functions
********************************************************************/
int easter_base (int year)
{
  const int A = year % 19;
  const int B = year / 100;
  const int C = year % 100;
  const int D = B / 4;
  const int E = B % 4;
  const int F = (B + 8) / 25;
  const int G = (B - F + 1) / 3;
  const int H = (19 * A + B - D - G + 15) % 30;
  const int I = C / 4;
  const int K = C % 4;
  const int L = (32 + 2 * E + 2 * I - H - K) % 7;
  const int M = (A + 11 * H + 22 * L) / 451;
  return H + L - 7 * M + 114;
}

/* The result of easter_year is the day number of the month in which Easter
   occurs in the given year.
*/
int calculate_easter_day (int year)
{
  return (easter_base (year) % 31) + 1;
}

/* The result of easter_month is the month in which Easter occurs in the given
   year.
*/
Month calculate_easter_month (int year)
{
  return static_cast<Month> (easter_base (year) / 31);
}

/********************************************************************
  Helper functions
********************************************************************/
bool is_leap_year (int year)
{
  if (year % 4 == 0)
  {
    if (year % 100 == 0 && year % 400 != 0)
      return false;
    return true;
  }

  return false;
}

int number_of_days_in_month (int year, Month month)
{
  switch(month) {
    case February: return is_leap_year(year) ? 29 : 28;
    case April:
    case June:
    case September:
    case November: return 30;
    default: return 31;
  }
}

int no_of_days_since_year_start (int day, Month month, int year)
{
  int no_of_days = 0;
  
  // Sum the days of all months before the current month
  for ( int month_int = January; month_int != month; month_int++ )
  {
    Month current_month = static_cast<Month>(month_int);
    no_of_days += number_of_days_in_month(year, current_month);
  }

  // Add the number of days from this month
  no_of_days += day;

  return no_of_days;
}

Weekday get_weekday_of_first_january (int year)
{
  // We can compute the date of Easter and we know that Easter is on a Sunday
  // so we can backtrack to find the weekday of 1st of January
  int easter_day = calculate_easter_day(year);
  Month easter_month = calculate_easter_month(year);

  int easter_day_index = no_of_days_since_year_start(easter_day, easter_month, year);

  // We subtract as many weeks as possible and we end up with the index
  // of the first Sunday of the year
  const int NO_OF_DAYS_IN_WEEK = 7;
  int first_sunday_index = easter_day_index % NO_OF_DAYS_IN_WEEK - 1;

  Weekday first_january_weekday = static_cast<Weekday>(7 - first_sunday_index);

  return first_january_weekday;
}

Weekday get_starting_weekday_of_month (int year, Month month)
{
    int weekday_index = static_cast<int>(get_weekday_of_first_january(year));

    // We iterate through the days of the week, resetting it back to Monday
    // when we are on Sunday
    for (int day_index = 1; day_index < no_of_days_since_year_start(1, month, year); day_index++)
    {
      weekday_index ++;
      if (weekday_index == 7)
        weekday_index = 0;
    }

    Weekday weekday = static_cast<Weekday>(weekday_index);
    return weekday;
}

void print_month (Weekday start_day, int month_length)
{
  cout << "Mo Tu We Th Fr Sa Su \n";

  // Print spaces until the start day
  for (int day = 1; day < start_day; day++)
    cout << "   ";

  // We need to keep the weekday index in order to break the line
  int weekday_index = static_cast<int>(start_day);

  for (int day = 1; day <= month_length ; day++)
  {
    if (day < 10)
      cout << day << "  ";
    else 
      cout << day << " ";

    if (weekday_index % 7 == 0)
      cout << "\n";
    weekday_index ++;
  }
}

/********************************************************************
  Assignment functions
********************************************************************/
void show_month (Month month, int year)
{
  cout << "\n" << month << " " << year << "\n";

  Weekday start_day = get_starting_weekday_of_month(year, month);
  print_month(start_day, number_of_days_in_month(year, month));
}

void show_months ()
{
  int year;
  int month_index;

	cout << "Please enter the month and year for printing the calendar\n";
  cout << "Month [MM]: ";
  cin >> month_index;
  cout << "Year [YYYY]: ";
  cin >> year;
  
  show_month(static_cast<Month>(month_index), year);
}

#ifndef TESTING
int main ()
{
    show_months();
    return 0;
}
#endif
