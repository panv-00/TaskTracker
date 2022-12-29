/*
 * File:   TaskTracker.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtString.h"

int main(int argc, char** argv) {

  TtString a("123456");
  a.dump();
  a.insert_char_at('A', 4);
  a.dump();

  return 0;
}
