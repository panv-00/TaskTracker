/*
 * File:   TtUI.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-30
 */

#include "TtUI.h"

TtUI *obj;

/*
 * Public Functions
 */

TtUI::TtUI() :
  term_resized {false},
  exit_app     {false}
{

}

TtUI::~TtUI()
{

}

void TtUI::sigwinch_handler(int signum)
{
  term_resized = true;
}

void sigwinch_wrapper(int signum)
{
  obj->sigwinch_handler(signum);
}

void TtUI::Run()
{
  obj = this;

  signal(SIGWINCH, sigwinch_wrapper);

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  max_rows = w.ws_row;
  max_cols = w.ws_col;

  fd_set fds;

  while (1)
  {
    if (term_resized)
    {
      term_resized = false;

      ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
      max_rows = w.ws_row;
      max_cols = w.ws_col;
      fflush(stdout);
    }

    FD_ZERO(&fds);
    FD_SET(SIGWINCH, &fds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000; // 100ms
    select(SIGWINCH + 1, &fds, NULL, NULL, &timeout);

    if (exit_app)
    {
      system("clear");
      MoveTo(1, 1);
      printf("Exiting in one Piece!\n");
      break;
    }

    printf("Seems Ok...");
    getc(stdin);
    exit_app = true;
  }
}

/*
 * Private Functions
 */


