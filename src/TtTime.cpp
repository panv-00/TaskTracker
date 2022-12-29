/*
 * File:   TtTime.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtTime.h"

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
  zero_all();
  
  if (is_valid(hour, minute))
  {
    this->hour   = hour;
    this->minute = minute;
  }
}

TtTime::~TtTime()
{

}

void TtTime::zero_all()
{
  this->hour   = 99;
  this->minute = 99;
}

bool TtTime::is_valid(int hour, int minute)
{
  if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
  {
    return false;
  }

  return true;
}

void TtTime::set_hour(int hour)
{
  if (hour < 0 || hour > 23) { return; }
  
  if (this->minute == 99 || is_valid(hour, this->minute))
  {
    this->hour = hour;
  }
}

void TtTime::set_minute(int minute)
{
  if (minute < 0 || minute > 59) { return; }

  if (this->hour == 99 || is_valid(this->hour, minute))
  {
    this->minute = minute;
  }
}

void TtTime::set_time(int hour, int minute)
{
  if (is_valid(hour, minute))
  {
    this->hour   = hour;
    this->minute = minute;
  }
}

void TtTime::echo()
{
  if (is_valid(hour, minute))
  {
    printf("%02d : %02d", hour, minute);
    return;
  }

  printf("XX : XX");
}
