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
  int c;

  c = io.read_char("Input only one character..");

  printf("\nYou gave : '%c'.\n", c);

  return 0;
}
