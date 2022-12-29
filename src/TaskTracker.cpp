/*
 * File:   TaskTracker.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtString.h"
#include "TtTime.h"

int main(int argc, char** argv)
{
  TtTime t1;
  t1.echo();printf("\n");

  TtString timestring(t1);
  timestring.dump();

  return 0;
}
