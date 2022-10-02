#include "main.cpp"
#include "gtest/gtest.h"

/********************************************************************
  Unit Tests part 1: Leap years
********************************************************************/
TEST (part_one, is_leap_year)
{
  EXPECT_TRUE (is_leap_year (400));
  EXPECT_TRUE (is_leap_year (1600));
  EXPECT_TRUE (is_leap_year (2000));
  EXPECT_TRUE (is_leap_year (2004));
  EXPECT_TRUE (is_leap_year (2008));
  EXPECT_TRUE (is_leap_year (2012));
  EXPECT_TRUE (is_leap_year (2016));
  EXPECT_TRUE (is_leap_year (2020));
  EXPECT_FALSE (is_leap_year (500));
  EXPECT_FALSE (is_leap_year (1700));
  EXPECT_FALSE (is_leap_year (1900));
  EXPECT_FALSE (is_leap_year (2001));
  EXPECT_FALSE (is_leap_year (2005));
  EXPECT_FALSE (is_leap_year (2013));
  EXPECT_FALSE (is_leap_year (2017));
  EXPECT_FALSE (is_leap_year (2021));
}

TEST (part_one, number_of_days_in_month)
{
  EXPECT_EQ (number_of_days_in_month (2000, February), 29);
  EXPECT_EQ (number_of_days_in_month (2020, February), 29);
  EXPECT_EQ (number_of_days_in_month (2021, January), 31);
  EXPECT_EQ (number_of_days_in_month (2021, March), 31);
  EXPECT_EQ (number_of_days_in_month (2021, May), 31);
  EXPECT_EQ (number_of_days_in_month (2021, July), 31);
  EXPECT_EQ (number_of_days_in_month (2021, August), 31);
  EXPECT_EQ (number_of_days_in_month (2021, October), 31);
  EXPECT_EQ (number_of_days_in_month (2021, December), 31);
  EXPECT_EQ (number_of_days_in_month (2021, February), 28);
  EXPECT_EQ (number_of_days_in_month (2021, April), 30);
  EXPECT_EQ (number_of_days_in_month (2021, June), 30);
  EXPECT_EQ (number_of_days_in_month (2021, September), 30);
  EXPECT_EQ (number_of_days_in_month (2021, November), 30);
}

/********************************************************************
  Unit Tests: Helper functions
********************************************************************/
TEST (helper_functions, no_of_days_since_year_start)
{
  EXPECT_EQ (no_of_days_since_year_start (3, January, 2010), 3); 
  EXPECT_EQ (no_of_days_since_year_start (1, February, 2010), 32); 
  EXPECT_EQ (no_of_days_since_year_start (1, February, 2012), 32); 
  EXPECT_EQ (no_of_days_since_year_start (3, March, 2010), 62); 
  EXPECT_EQ (no_of_days_since_year_start (1, March, 2012), 61); 
  EXPECT_EQ (no_of_days_since_year_start (4, January, 2012), 4); 
  EXPECT_EQ (no_of_days_since_year_start (15, April, 2012), 106); 
  EXPECT_EQ (no_of_days_since_year_start (31, December, 2012), 366); 
  EXPECT_EQ (no_of_days_since_year_start (31, December, 2010), 365); 
}

TEST (helper_functions, get_formatted_date_from_day_number)
{
  EXPECT_EQ (get_formatted_date_from_day_number (3, 2010), "3-1"); 
  EXPECT_EQ (get_formatted_date_from_day_number (4, 2012), "4-1"); 
  EXPECT_EQ (get_formatted_date_from_day_number (32, 2010), "1-2");
  EXPECT_EQ (get_formatted_date_from_day_number (61, 2010), "2-3");
  EXPECT_EQ (get_formatted_date_from_day_number (61, 2012), "1-3"); 
  EXPECT_EQ (get_formatted_date_from_day_number (366, 2012), "31-12"); 
  EXPECT_EQ (get_formatted_date_from_day_number (365, 2010), "31-12"); 
}

/********************************************************************
  Unit Tests part 2: Holy days based on Easter
********************************************************************/
TEST (part_two, carnival)
{
  EXPECT_EQ (show_carnival (4, April, 2010), "14-2");
  EXPECT_EQ (show_carnival (24, April, 2011), "6-3");
  EXPECT_EQ (show_carnival (8, April, 2012), "19-2");
  EXPECT_EQ (show_carnival (31, March, 2013), "10-2");
  EXPECT_EQ (show_carnival (20, April, 2014), "2-3");
  EXPECT_EQ (show_carnival (5, April, 2015), "15-2");
  EXPECT_EQ (show_carnival (27, March, 2016), "7-2");
  EXPECT_EQ (show_carnival (16, April, 2017), "26-2");
  EXPECT_EQ (show_carnival (1, April, 2018), "11-2");
  EXPECT_EQ (show_carnival (21, April, 2019), "3-3");
  EXPECT_EQ (show_carnival (12, April, 2020), "23-2");
  EXPECT_EQ (show_carnival (4, April, 2021), "14-2");
}

TEST (part_two, good_friday)
{
  EXPECT_EQ (show_good_friday (4, April, 2010), "2-4");
  EXPECT_EQ (show_good_friday (24, April, 2011), "22-4");
  EXPECT_EQ (show_good_friday (8, April, 2012), "6-4");
  EXPECT_EQ (show_good_friday (31, March, 2013), "29-3");
  EXPECT_EQ (show_good_friday (20, April, 2014), "18-4");
  EXPECT_EQ (show_good_friday (5, April, 2015), "3-4");
  EXPECT_EQ (show_good_friday (27, March, 2016), "25-3");
  EXPECT_EQ (show_good_friday (16, April, 2017), "14-4");
  EXPECT_EQ (show_good_friday (1, April, 2018), "30-3");
  EXPECT_EQ (show_good_friday (21, April, 2019), "19-4");
  EXPECT_EQ (show_good_friday (12, April, 2020), "10-4");
  EXPECT_EQ (show_good_friday (4, April, 2021), "2-4");
}

TEST (part_two, easter)
{
  EXPECT_EQ (show_easter (4, April, 2010), "4-4");
  EXPECT_EQ (show_easter (24, April, 2011), "24-4");
  EXPECT_EQ (show_easter (8, April, 2012), "8-4");
  EXPECT_EQ (show_easter (31, March, 2013), "31-3");
  EXPECT_EQ (show_easter (20, April, 2014), "20-4");
  EXPECT_EQ (show_easter (5, April, 2015), "5-4");
  EXPECT_EQ (show_easter (27, March, 2016), "27-3");
  EXPECT_EQ (show_easter (16, April, 2017), "16-4");
  EXPECT_EQ (show_easter (1, April, 2018), "1-4");
  EXPECT_EQ (show_easter (21, April, 2019), "21-4");
  EXPECT_EQ (show_easter (12, April, 2020), "12-4");
  EXPECT_EQ (show_easter (4, April, 2021), "4-4");
}

TEST (part_two, whitsuntide)
{
  EXPECT_EQ (show_whitsuntide (4, April, 2010), "23-5");
  EXPECT_EQ (show_whitsuntide (24, April, 2011), "12-6");
  EXPECT_EQ (show_whitsuntide (8, April, 2012), "27-5");
  EXPECT_EQ (show_whitsuntide (31, March, 2013), "19-5");
  EXPECT_EQ (show_whitsuntide (20, April, 2014), "8-6");
  EXPECT_EQ (show_whitsuntide (5, April, 2015), "24-5");
  EXPECT_EQ (show_whitsuntide (27, March, 2016), "15-5");
  EXPECT_EQ (show_whitsuntide (16, April, 2017), "4-6");
  EXPECT_EQ (show_whitsuntide (1, April, 2018), "20-5");
  EXPECT_EQ (show_whitsuntide (21, April, 2019), "9-6");
  EXPECT_EQ (show_whitsuntide (12, April, 2020), "31-5");
  EXPECT_EQ (show_whitsuntide (4, April, 2021), "23-5");
}

TEST (part_two, ascension_day)
{
  EXPECT_EQ (show_ascension_day (4, April, 2010), "13-5");
  EXPECT_EQ (show_ascension_day (24, April, 2011), "2-6");
  EXPECT_EQ (show_ascension_day (8, April, 2012), "17-5");
  EXPECT_EQ (show_ascension_day (31, March, 2013), "9-5");
  EXPECT_EQ (show_ascension_day (20, April, 2014), "29-5");
  EXPECT_EQ (show_ascension_day (5, April, 2015), "14-5");
  EXPECT_EQ (show_ascension_day (27, March, 2016), "5-5");
  EXPECT_EQ (show_ascension_day (16, April, 2017), "25-5");
  EXPECT_EQ (show_ascension_day (1, April, 2018), "10-5");
  EXPECT_EQ (show_ascension_day (21, April, 2019), "30-5");
  EXPECT_EQ (show_ascension_day (12, April, 2020), "21-5");
  EXPECT_EQ (show_ascension_day (4, April, 2021), "13-5");
}
