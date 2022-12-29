/*
 * File:   TtIO.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#ifndef TTIO_H
#define TTIO_H

#include "includes.h"
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

  int  read_number(const char *prompt);
  char read_char(const char *prompt);
  void echo();

protected:

private:
  int  getch   (     );
  bool is_alpha(int c);
  bool is_num  (int c);
  bool is_punct(int c);
  bool is_ctrl (int c);

  TtString io_line;
  size_t max_length;
  size_t cursor_position;

};

#endif
