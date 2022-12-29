/*
 * File:   TaskTracker.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtString.h"

int main(int argc, char** argv) {

  TtString a;
  TtString b('f');
  TtString c(256);
  TtString d("alfa000");
  TtString e("\r\ta b c\n  ");
  TtString f(e);

  a = c + d;
  if (f == e) printf ("f and e are equal\n");
  else printf("f and e are not equal\n");

  a.dump(); b.dump(); c.dump(); d.dump(); e.dump(); f.dump();
  d.insert_char_at('M', 2);
  d.dump();
  e.clean();
  if (f == e) printf ("f and e are equal\n");
  else printf("f and e are not equal\n");

  return 0;
}
