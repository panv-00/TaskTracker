/*
 * File:   TtDate.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#ifndef TTDATE_H
#define TTDATE_H

#include "includes.h"

class TtDate
{
public:
  TtDate();
  TtDate(int year, int month, int day);
  ~TtDate();

  void zero_all();
  int  get_year () { return year;  };
  int  get_month() { return month; };
  int  get_day  () { return day;   };

  void set_year (int year );
  void set_month(int month);
  void set_day  (int day  );
  void set_date (int year, int month, int day);

  DayOfWeek get_day_of_week();
  void echo();
  bool is_valid() { return is_valid(year, month, day); };

protected:

private:
  bool is_valid(int year, int month, int day);
  
  int year, month, day;

};

#endif
