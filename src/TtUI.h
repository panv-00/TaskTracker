/*
 * File:   TtUI.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-30
 */

#ifndef TTUI_H
#define TTUI_H

#include "TtInclude.h"
#include "TtIO.h"
#include "TtRW.h"

class TtUI
{
public:
  TtUI();
  ~TtUI();

  void sigwinch_handler(int signum);
  void Run();

protected:

private:
  friend void sigwinch_wrapper(int signum);

  void ResetCursorToPrompt() { MoveTo(max_rows - 2, 2); };
  
  void DrawUI();
  void ResetBoundaries();
  void DrawDisplayBox();
  void DrawPromptBox();

  bool term_resized;
  bool exit_app;
  int max_rows;
  int max_cols;
  int width;
  int display_height;
  int prompt_height;
  int io_limits;

  UserMenu menu;
  TtRW *rw;
};

#endif
