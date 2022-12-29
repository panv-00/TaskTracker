/*
 * File:   TtString.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */


#ifndef TTSTRING_H
#define TTSTRING_H

#include "TtInclude.h"
#include "TtTime.h"
#include "TtDate.h"

class TtString
{
public:
  TtString();
  TtString(char c);
  TtString(int num);
  TtString(TtTime t);
  TtString(TtDate d);
  TtString(const char *s);
  TtString(const TtString &tts);
  ~TtString();

  TtString &operator=(const TtString &tts);
  TtString operator+(const TtString &tts) const;
  bool operator==(const TtString &tts) const;
  void dump();
  void echo();
  void clean();
  void insert_char_at(char c, size_t index);
  void delete_char_at(size_t index);
  int  to_number();

  const char* to_string() const { return string; };
  const size_t get_length() { return length; };

protected:

private:
  bool is_whitespace(char c);
  
  char *string;
  size_t length;

};

#endif
