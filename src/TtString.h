/*
 * File:   TtString.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */


#ifndef TTSTRING_H
#define TTSTRING_H

#include "includes.h"

class TtString
{
public:
  TtString();
  TtString(char c);
  TtString(int num);
  TtString(const char *s);
  TtString(const TtString &other);
  ~TtString();

  TtString &operator=(const TtString &s);
  TtString operator+(const TtString &s) const;
  void dump();
  void echo();
  void clean();

protected:

private:
  bool is_whitespace(char c);
  
  char *string;
  size_t length;

};

#endif
