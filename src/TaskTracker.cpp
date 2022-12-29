/*
 * File:   TaskTracker.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtString.h"

int main(int argc, char** argv) {

  TtString a("\r\t  \n   dc.   \n ");
  a.dump();
  a.clean();
  a.dump();

  return 0;
}
