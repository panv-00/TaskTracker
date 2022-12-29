/*
 * File:   TtDate.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtDate.h"

/*
 * Public Functions
 */

TtDate::TtDate()
{
  time_t current_time = time(nullptr);
  struct tm *local_time = localtime(&current_time);

  if (local_time != nullptr)
  {
    this->year  = local_time->tm_year + 1900;
    this->month = local_time->tm_mon  + 1;
    this->day   = local_time->tm_mday;
  }
}

TtDate::TtDate(int year, int month, int day)
{
  zero_all();

  if (is_valid(year, month, day))
  {
    this->year  = year;
    this->month = month;
    this->day   = day;  
  }
}

TtDate::~TtDate()
{

}

void TtDate::zero_all()
{
  this->year  = 9999;
  this->month = 99;
  this->day   = 99;
}

void TtDate::set_year(int year)
{
  if (year < 1) { return; }

  if (this->month == 99 || this->day == 99
      || is_valid(year, this->month, this->day))
  {
    this->year = year;
  }
}

void TtDate::set_month(int month)
{
  if (month < 1 || month > 12) { return; }

  if (this->year == 9999 || this->day == 99
      || is_valid(this->year, month, this->day))
  {
    this->month = month;
  }
}

void TtDate::set_day(int day)
{
  if (day < 1 || day > 31) { return; }

  if (this->month == 99 || this->year == 99
      || is_valid(this->year, this->month, day))
  {
    this->day = day;
  }
}

void TtDate::set_date(int year, int month, int day)
{
  if (is_valid(year, month, day))
  {
    this->year  = year;
    this->month = month;
    this->day   = day;
  }
}

DayOfWeek TtDate::get_day_of_week()
{
  int d = day;
  int m = month;
  int y = year;

  return (DayOfWeek)
    ((d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7);
}

void TtDate::echo()
{
  if (is_valid(year, month, day))
  {
    printf("%04d . %02d . %02d", year, month, day);
    return;
  }

  printf("XXXX . XX . XX");
}

/*
 * Private Functions
 */

bool TtDate::is_valid(int year, int month, int day)
{
  if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
  {
    return false;
  }

  if (month == 2)
  {
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
    {
      if (day > 29) { return false; }
    }

    else if (day > 28) { return false; }  
  }

  else if (month == 4 || month == 6 || month == 9 || month == 11)
  {
    if (day > 30) { return false; }
  }

  return true;
}

