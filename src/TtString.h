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
  void Dump();
  void Echo();
  void Clean();
  void InsertCharAt(char c, size_t index);
  void DeleteCharAt(size_t index);
  int  ToNumber();

  const char* ToString() const { return string; };
  const size_t GetLength() { return length; };

protected:

private:
  bool IsWhitespace(char c);
  
  char *string;
  size_t length;

};

#endif
