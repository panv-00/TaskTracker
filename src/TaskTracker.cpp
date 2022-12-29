/*
 * File:   TaskTracker.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtString.h"
#include "TtTime.h"
#include "TtDate.h"
#include "TtIO.h"

int main(int argc, char** argv)
{
  clrscr();
  printf("Testing TtIO!\n\n");

  TtIO io(24);

  io.read_string("Input a String..\n\r\x1b[2C");

  printf("\n\nYou Selected the lucky text: \n");
  io.echo();
  printf("\n");

  return 0;
}
