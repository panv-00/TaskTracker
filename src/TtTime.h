/*
 * File:   TtTime.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#ifndef TTTIME_H
#define TTTIME_H

#include "includes.h"

class TtTime
{
public:
  TtTime();
  TtTime(int hour, int minute);
  ~TtTime();

  void zero_all();
  int  get_hour  () { return hour;   };
  int  get_minute() { return minute; };

  void set_hour  (int hour            );
  void set_minute(int minute          );
  void set_time  (int hour, int minute);

  void echo();
  bool is_valid() { return is_valid(hour, minute); };


protected:

private:
  bool is_valid(int hour, int minute);

  int hour, minute;
};

#endif
