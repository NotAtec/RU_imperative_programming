#include <iostream>

using namespace std;

enum Month
{
  January = 1, February, March, April, May, June,
  July, August, September, October, November, December
};

/* The function easter_base uses the Meeus/Jones/Butcher formula to compute
   the number that is used to determine on which month (easter_month below)
   and day (easter_day below) Easter is in the given year.
*/
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
  Assignment part 1: Leap years
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

/********************************************************************
  Helper functions
********************************************************************/
int no_of_days_since_year_start(int day, Month month, int year)
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

string get_formatted_date_from_day_number(int day_number, int year)
{
  int current_month_int = 1;

  // Subtract no of days per month from the total until it is less than the current month's 
  while (day_number > number_of_days_in_month(year, static_cast<Month>(current_month_int)))
  {
    // As Enums are not contiguous we need to cast continuously from Enum to Int and back
    Month current_month = static_cast<Month>(current_month_int);
    day_number -= number_of_days_in_month(year, current_month);
    current_month_int ++;
  }

  // Format the string as required
  string day_string = to_string(day_number);
  string month_string = to_string(current_month_int);
  return day_string + "-" + month_string;
}

/********************************************************************
  Assignment part 2: Holy days based on Easter
********************************************************************/
string show_carnival(int easter_day, Month easter_month, int year)
{
  int no_of_days_easter = no_of_days_since_year_start(easter_day, easter_month, year);
  // Carnival is 7 weeks before Easter
  int no_of_days_carnival = no_of_days_easter - 7 * 7;
  return get_formatted_date_from_day_number(no_of_days_carnival, year);
}

string show_good_friday(int easter_day, Month easter_month, int year)
{
  int no_of_days_easter = no_of_days_since_year_start(easter_day, easter_month, year);
  // Carnival is 2 days before Easter
  int no_of_days_good_friday = no_of_days_easter - 2;
  return get_formatted_date_from_day_number(no_of_days_good_friday, year);
}

string show_easter(int easter_day, Month easter_month, int year)
{
  string day_string = to_string(easter_day);
  string month_string = to_string(static_cast<int>(easter_month));
  return day_string + "-" + month_string;
}

string show_whitsuntide(int easter_day, Month easter_month, int year)
{
  int no_of_days_easter = no_of_days_since_year_start(easter_day, easter_month, year);
  // Whitsuntide is 7 weeks after Easter
  int no_of_days_whitsuntide = no_of_days_easter + 7 * 7;
  return get_formatted_date_from_day_number(no_of_days_whitsuntide, year);
}

string show_ascension_day(int easter_day, Month easter_month, int year)
{
  int no_of_days_easter = no_of_days_since_year_start(easter_day, easter_month, year);
  // Ascension is 10 days before Whitsuntide or 39 days after Easter
  int no_of_days_ascension = no_of_days_easter + 39;
  return get_formatted_date_from_day_number(no_of_days_ascension, year);
}

void show_holy_days (int year)
{
  // Calculate Easter Date
  int easter_day = calculate_easter_day(year);
  Month easter_month = calculate_easter_month(year);

  // Print the requested Dates
  cout << "In the year " << year << ", these will be the Holy Dates:\n";
  cout << "\t - Carnival: " <<  show_carnival(easter_day, easter_month, year) << "\n";
  cout << "\t - Good Friday: " <<  show_good_friday(easter_day, easter_month, year) << "\n";
  cout << "\t - Easter: " <<  show_easter(easter_day, easter_month, year) << "\n";
  cout << "\t - Whitsuntide: " <<  show_whitsuntide(easter_day, easter_month, year) << "\n";
  cout << "\t - Ascension Day: " <<  show_ascension_day(easter_day, easter_month, year) << "\n";
}

#ifndef TESTING
int main()
{
  // Read User Input
  int user_year;
  cout << "Please enter the year for the Holy Dates [format: YYYY]: ";
  cin >> user_year;

  show_holy_days(user_year);

	return 0;
}
#endif
