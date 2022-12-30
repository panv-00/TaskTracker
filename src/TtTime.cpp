/*
 * File:   TtTime.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtTime.h"

/*
 * Public Functions
 */

TtTime::TtTime() 
{
  time_t current_time = time(nullptr);
  struct tm *local_time = localtime(&current_time);

  if (local_time != nullptr)
  {
    this->hour = local_time->tm_hour;
     this->minute = local_time->tm_min;
  }
}

TtTime::TtTime(int hour, int minute)
{
  ZeroAll();
  
  if (IsValid(hour, minute))
  {
    this->hour   = hour;
    this->minute = minute;
  }
}

TtTime::~TtTime()
{

}

void TtTime::ZeroAll()
{
  this->hour   = 99;
  this->minute = 99;
}

void TtTime::SetHour(int hour)
{
  if (hour < 0 || hour > 23) { return; }
  
  if (this->minute == 99 || IsValid(hour, this->minute))
  {
    this->hour = hour;
  }
}

void TtTime::SetMinute(int minute)
{
  if (minute < 0 || minute > 59) { return; }

  if (this->hour == 99 || IsValid(this->hour, minute))
  {
    this->minute = minute;
  }
}

void TtTime::SetTime(int hour, int minute)
{
  if (IsValid(hour, minute))
  {
    this->hour   = hour;
    this->minute = minute;
  }
}

void TtTime::Echo()
{
  if (IsValid(hour, minute))
  {
    printf("%02d : %02d", hour, minute);
    return;
  }

  printf("XX : XX");
}

/*
 * Private Functions
 */

bool TtTime::IsValid(int hour, int minute)
{
  if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
  {
    return false;
  }

  return true;
}

