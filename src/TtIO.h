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

void ClrScr         (            );
void SavePosition   (            );
void RestorePosition(            );
void SetColor       (ColorCode cc);
void MoveUp         (int count   );
void MoveDown       (int count   );
void MoveRight      (int count   );
void MoveLeft       (int count   );
void MoveTo         (int r, int c);


class TtIO
{
public:
  TtIO(size_t max_length);
  ~TtIO();

  char ReadChar  (const char *prompt);
  int  ReadNumber(const char *prompt);
  void ReadString(const char *prompt);
  void Echo();

protected:

private:
  void ResetLine(int previous_cursor_position, int line_length);
  int  Getch  (     );
  bool IsAlpha(int c);
  bool IsNum  (int c);
  bool IsPunct(int c);
  bool IsCtrl (int c);

  // only_num = true -> Accept only numbers
  void ReadAny(const char *prompt, bool only_num);
  bool ReadCondition(int c, bool only_num);

  TtString io_line;
  size_t max_length;
  size_t cursor_position;

};

#endif
