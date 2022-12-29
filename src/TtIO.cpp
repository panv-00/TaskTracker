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

void clrscr          (            ) { system("clear"            ); };
void save_position   (            ) { printf("\x1b%d",         7); };
void restore_position(            ) { printf("\x1b%d",         8); };
void set_color       (ColorCode cc) { printf("\x1b[%dm",      cc); };
void move_up         (int count   ) { printf("\x1b[%dA",   count); };
void move_down       (int count   ) { printf("\x1b[%dB",   count); };
void move_right      (int count   ) { printf("\x1b[%dC",   count); };
void move_left       (int count   ) { printf("\x1b[%dD",   count); };
void move_to         (int r, int c) { printf("\x1b[%d;%df", r, c); };

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
  read_any(prompt, true);
  io_line.clean();

  return io_line.to_number();
}

void TtIO::read_string(const char *prompt)
{
  read_any(prompt, false);
}
  
void TtIO::echo()
{
  printf(START_INPUT);
  io_line.echo();
  move_left(io_line.get_length());
  if (cursor_position > 0) { move_right(cursor_position); }
}

void TtIO::debug(bool start_debug)
{
  if (start_debug)
  {
    save_position();
    move_down(4);
    printf("\r");
  }

  else
  {
    restore_position();
  }
}

/*
 * Private Functions
 */

void TtIO::reset_line(int previous_cursor_position, int line_length)
{
  move_left(previous_cursor_position);
  printf("%*s", line_length + 1, " ");
  move_left(line_length);
}

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

void TtIO::read_any(const char *prompt, bool only_num)
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

    while (read_condition(a, only_num))
    {
      a = getch();
      line_length = io_line.get_length();
      previous_cursor_position = cursor_position;

      if (a == '\n') { return; }

      if ((a == BACKSPACE) && (cursor_position > 0))
      {
        do_insert = false;
        cursor_position--;
        io_line.delete_char_at(cursor_position);
      }
      
      if (a == ESCAPE_CHAR)
      {
        a = getch();
        if (a == ARROW_CHAR)
        {
          do_insert = false;
          a = getch();
          if (a == ARROW_LT)
          {
            if (cursor_position > 0) { cursor_position--; }
          }
          if (a == ARROW_RT)
          {
            if (cursor_position < io_line.get_length()) { cursor_position++; }
          }
        }
      }
    }

    if (io_line.get_length() < max_length)
    {
      if (io_line.get_length() > 0)
      {
        reset_line(previous_cursor_position, line_length);
      }

      if (do_insert)
      {

        io_line.insert_char_at(a, cursor_position);
        cursor_position++;
      }

      echo();
    }

    a = 0;
  }
}

bool TtIO::read_condition(int c, bool only_num)
{
  return 
    only_num ?
    !is_num(c) && !is_ctrl(c)
    :
    !is_alpha(c) && !is_num(c) && !is_punct(c) && !is_ctrl(c);
}
