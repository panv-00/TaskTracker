/*
 * File:   TtIO.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#ifndef TTIO_H
#define TTIO_H

#include "TtInclude.h"
#include "TtString.h"

void clrscr          (            );
void save_position   (            );
void restore_position(            );
void set_color       (ColorCode cc);
void move_up         (int count   );
void move_down       (int count   );
void move_right      (int count   );
void move_left       (int count   );
void move_to         (int r, int c);


class TtIO
{
public:
  TtIO(size_t max_length);
  ~TtIO();

  char read_char  (const char *prompt);
  int  read_number(const char *prompt);
  void read_string(const char *prompt);
  void echo();

protected:

private:
  void reset_line(int previous_cursor_position, int line_length);
  int  getch   (     );
  bool is_alpha(int c);
  bool is_num  (int c);
  bool is_punct(int c);
  bool is_ctrl (int c);

  // only_num = true -> Accept only numbers
  void read_any(const char *prompt, bool only_num);
  bool read_condition(int c, bool only_num);

  TtString io_line;
  size_t max_length;
  size_t cursor_position;

};

#endif
