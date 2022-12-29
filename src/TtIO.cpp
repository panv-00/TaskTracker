/*
 * File:   TtIO.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtIO.h"

void clrscr          (            ) { system("clear"            ); };
void save_position   (            ) { printf("\x1b%d",         7); };
void restore_position(            ) { printf("\x1b%d",         8); };
void set_color       (ColorCode cc) { printf("\x1b[%dm",      cc); };
void move_up         (int count   ) { printf("\x1b[%dA",   count); };
void move_down       (int count   ) { printf("\x1b[%dB",   count); };
void move_right      (int count   ) { printf("\x1b[%dC",   count); };
void move_left       (int count   ) { printf("\x1b[%dD",   count); };
void move_to         (int r, int c) { printf("\x1b[%d;%df", r, c); };

TtIO::TtIO(size_t max_length) :
  io_line         {""},
  max_length      {max_length},
  cursor_position {0}
{

}

TtIO::~TtIO()
{

}

char TtIO::read_char(const char *prompt)
{
  int a = 0;

  printf("%s", prompt);

  while (!is_alpha(a) && !is_num(a) && !is_punct(a) && !is_ctrl(a))
  {
    a = getch();
  }

  return a;
  
}

int  TtIO::read_number(const char *prompt)
{
  return 0;
}
  
void TtIO::echo()
{

}

/*
 * Private Functions
 */

int TtIO::getch(void)
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

bool TtIO::is_alpha(int c)
{
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
  return false;
}

bool TtIO::is_num(int c)
{
  if (c >= '0' && c <= '9') return true;
  return false;
}

bool TtIO::is_punct(int c)
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

bool TtIO::is_ctrl(int a)
{
  switch (a)
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
