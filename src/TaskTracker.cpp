/*
 * File:   TaskTracker.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtString.h"
#include "TtTime.h"
#include "TtDate.h"

int main(int argc, char** argv)
{
  TtTime t1;
  t1.echo();printf("\n");

  TtString timestring(t1);
  timestring.dump();

  TtDate d1;
  d1.echo();printf("\n");

  d1.set_month(3);
  d1.echo();printf("\n");

  TtString datestring(d1);
  datestring.dump();

  return 0;
}
