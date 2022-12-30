/*
 * File:   TtDate.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#ifndef TTDATE_H
#define TTDATE_H

#include "TtInclude.h"

class TtDate
{
public:
  TtDate();
  TtDate(int year, int month, int day);
  ~TtDate();

  void ZeroAll();
  int  GetYear () { return year;  };
  int  GetMonth() { return month; };
  int  GetDay  () { return day;   };

  void SetYear (int year );
  void SetMonth(int month);
  void SetDay  (int day  );
  void SetDate (int year, int month, int day);

  DayOfWeek GetDayOfWeek();
  void Echo();
  bool IsValid() { return IsValid(year, month, day); };

protected:

private:
  bool IsValid(int year, int month, int day);
  
  int year, month, day;

};

#endif
