/*
 * File:   TtTime.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#ifndef TTTIME_H
#define TTTIME_H

#include "TtInclude.h"

class TtTime
{
public:
  TtTime();
  TtTime(int hour, int minute);
  ~TtTime();

  void ZeroAll();
  int  GetHour  () { return hour;   };
  int  GetMinute() { return minute; };

  void SetHour  (int hour            );
  void SetMinute(int minute          );
  void SetTime  (int hour, int minute);

  void Echo();
  bool IsValid() { return IsValid(hour, minute); };


protected:

private:
  bool IsValid(int hour, int minute);

  int hour, minute;
};

#endif
