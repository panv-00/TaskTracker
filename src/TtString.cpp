/*
 * File:   TtString.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtString.h"

/*
 * Public Functions
 */

TtString::TtString()
{
  length = 0;
  string = new char[length + 1];
  string[length] = '\0';
}

TtString::TtString(char c)
{
  length = 1;
  string = new char[length + 1];
  string[0] = c;
  string[length] = '\0';
}

TtString::TtString(int num)
{
  length = 0;

  int remainder;
  int count = 0;
  int number = num;

  while (number > 0)
  {
    number /= 10;
    length++;
  }

  string = new char[length + 1];

  while (num > 0)
  {
    remainder = num % 10;
    num /= 10;
    string[length - count - 1] = (char) (remainder + '0');
    count++;
  }

  string[length] = '\0';
}

TtString::TtString(const char *s)
{
  length = 0;
  const char *str = s;

  while (*str != '\0') { length++; str++; }
  if (length > BUFFSIZE) { length = BUFFSIZE; }
  
  string = new char[length + 1];

  for (size_t i = 0; i < length; i++) { string[i] = s[i]; }

  string[length] = '\0';
}

TtString::TtString(const TtString &other)
{
  length = other.length;
  string = new char[length + 1];

  for (size_t i = 0; i < length; i++) { string[i] = other.string[i]; }
  
  string[length] = '\0';
}

TtString::~TtString()
{
  delete[] string;
}

TtString &TtString::operator=(const TtString &s)
{
  if (this != &s)
  {
    delete[] string;
    length = s.length;
    string = new char[length + 1];
    
    for (size_t i = 0; i < length; i++)
    {
      string[i] = s.string[i];
    }

    string[length] = '\0';
  }

  return *this;
}

TtString TtString::operator+(const TtString &s) const
{
  TtString result;
  
  result.length = length + s.length;

  if (result.length > BUFFSIZE) { result.length = BUFFSIZE; }

  delete[] result.string;

  result.string = new char[result.length + 1];
  
  for (size_t i = 0; i < length; i++)
  {
    result.string[i] = string[i];
  }

  for (size_t i = 0; i < result.length - length; i++)
  {
    result.string[i + length] = s.string[i];
  }

  result.string[result.length] = '\0';

  return result;
}

void TtString::dump()
{
  size_t count = 0;
  
  printf("\n\tString Length: %ld\n", length);

  while (true)
  {
    if (string[count] == '\0')
    {
      printf("\t[%10ld] - '\\0'\n", count);
      break;
    }

    printf("\t[%10ld] - '%c'\n", count, string[count]);
    count++;
  }
}

void TtString::echo()
{
  printf("%s", string);
}

void TtString::clean()
{
  size_t start = 0;
  while (is_whitespace(string[start])) { start++; }

  size_t end = length - 1;
  while (is_whitespace(string[end])) { end--; }

  size_t new_length = end - start + 1;

  char *new_string = new char[new_length + 1];

  for (size_t i = 0; i < new_length; i++) {
    new_string[i] = string[start + i];
  }

  new_string[new_length] = '\0';

  delete[] string;

  string = new_string;
  length = new_length;
}

/*
 * Private Functions
 */

bool TtString::is_whitespace(char c)
{
  return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}
