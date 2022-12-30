/*
 * File:   TtIO.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtIO.h"

/*
 * Non-Class Functions
 */

void ClrScr         (            ) { system("clear"            ); };
void SavePosition   (            ) { printf("\x1b%d",         7); };
void RestorePosition(            ) { printf("\x1b%d",         8); };
void SetColor       (ColorCode cc) { printf("\x1b[%dm",      cc); };
void MoveUp         (int count   ) { printf("\x1b[%dA",   count); };
void MoveDown       (int count   ) { printf("\x1b[%dB",   count); };
void MoveRight      (int count   ) { printf("\x1b[%dC",   count); };
void MoveLeft       (int count   ) { printf("\x1b[%dD",   count); };
void MoveTo         (int r, int c) { printf("\x1b[%d;%df", r, c); };

/*
 * Public Functions
 */

TtIO::TtIO(size_t max_length) :
  io_line         {""},
  max_length      {max_length},
  cursor_position {0}
{

}

TtIO::~TtIO()
{

}

char TtIO::ReadChar(const char *prompt)
{
  int a = 0;

  printf("%s", prompt);

  while (!IsAlpha(a) && !IsNum(a) && !IsPunct(a) && !IsCtrl(a))
  {
    a = Getch();
  }

  return a;
}

int  TtIO::ReadNumber(const char *prompt)
{
  ReadAny(prompt, true);
  io_line.Clean();

  return io_line.ToNumber();
}

void TtIO::ReadString(const char *prompt)
{
  ReadAny(prompt, false);
}
  
void TtIO::Echo()
{
  printf(START_INPUT);
  io_line.Echo();
  MoveLeft(io_line.GetLength());
  
  if (cursor_position > 0) { MoveRight(cursor_position); }
}

/*
 * Private Functions
 */

void TtIO::ResetLine(int previous_cursor_position, int line_length)
{
  MoveLeft(previous_cursor_position);
  printf("%*s", line_length + 1, " ");
  MoveLeft(line_length);
}

int TtIO::Getch(void)
{
  struct termios oldt, newt;
  int ch;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}

bool TtIO::IsAlpha(int c)
{
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
  return false;
}

bool TtIO::IsNum(int c)
{
  if (c >= '0' && c <= '9') return true;
  return false;
}

bool TtIO::IsPunct(int c)
{
  switch (c)
  {
    case '`':
    case '~':
    case '!':
    case '@':
    case '#':
    case '$':
    case '%':
    case '^':
    case '&':
    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
    case '.':
    case ',':
    case '<':
    case '>':
    case ';':
    case '?':
    case ':':
    case '_':
    case '|':
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
    case '"':
    case '\\':
    case '\'':
      return true;

    default:
      return false;
  }
}

bool TtIO::IsCtrl(int c)
{
  switch (c)
  {
    case ' ':
    case '\n':
    case BACKSPACE:
    case ESCAPE_CHAR:
    case ARROW_CHAR:
    case ARROW_RT:
    case ARROW_LT:
    case ARROW_UP:
    case ARROW_DN:
      return true;

    default:
      return false;
  }
}

void TtIO::ReadAny(const char *prompt, bool only_num)
{
  int  a = 0;
  int  line_length = 0;
  int  previous_cursor_position = 0;
  bool do_insert;
  
  io_line = "";
  cursor_position = 0;

  printf("%s", prompt);

  while(true)
  {
    do_insert = true;

    while (ReadCondition(a, only_num))
    {
      a = Getch();
      line_length = io_line.GetLength();
      previous_cursor_position = cursor_position;

      if (a == '\n') { return; }

      if ((a == BACKSPACE) && (cursor_position > 0))
      {
        do_insert = false;
        cursor_position--;
        io_line.DeleteCharAt(cursor_position);
      }
      
      if (a == ESCAPE_CHAR)
      {
        a = Getch();
        if (a == ARROW_CHAR)
        {
          do_insert = false;
          a = Getch();
          if (a == ARROW_LT)
          {
            if (cursor_position > 0) { cursor_position--; }
          }
          if (a == ARROW_RT)
          {
            if (cursor_position < io_line.GetLength()) { cursor_position++; }
          }
        }
      }
    }

    if (io_line.GetLength() < max_length)
    {
      if (io_line.GetLength() > 0)
      {
        ResetLine(previous_cursor_position, line_length);
      }

      if (do_insert)
      {

        io_line.InsertCharAt(a, cursor_position);
        cursor_position++;
      }

      Echo();
    }

    a = 0;
  }
}

bool TtIO::ReadCondition(int c, bool only_num)
{
  return 
    only_num ?
    !IsNum(c) && !IsCtrl(c)
    :
    !IsAlpha(c) && !IsNum(c) && !IsPunct(c) && !IsCtrl(c);
}
