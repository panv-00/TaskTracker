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
  exit_app     {false},
  menu         {(UserMenu) 0}
{
  rw = new TtRW();

  rw->GetCWDContents();
  
  switch(rw->GetStatus())
  {
    case HOME_ENV_ERROR:
      printf("[Error]   : $HOME environment variable not set.\n");
      break;

    case CONFIG_CREATE_ERROR:
      printf("[WARNING] : ~/.config does not exist.\n");
      printf("            Trying to create.\n");
      printf("[Error]   : Cannot Create ~/.config\n");
      break;

    case TT_CREATE_ERROR:
      printf("[WARNING] : data directory does not exist.\n");
      printf("            Trying to create @ ~/.config/TaskTracker/\n");
      printf("[Error]   : Cannot create data directory.\n");
      break;

    case DISC_STATUS_HEALTHY:
      printf("\nTotal Files: %d\n", rw->GetFilesCount());
      printf("Directory Listing:\n");
      printf("------------------\n");
      for (int i = 0; i < rw->GetFilesCount(); i++)
      {
        printf("[  %2d ] --> %s\n", i, rw->GetDirFile(i).ToString());
      }
      break;

    case DISC_STATUS_UNKNOWN:
      printf("[WARNING] : unexpected behavior.\n");
      printf("            App needs to close now.\n");
      break;
  }
  getc(stdin);
}

TtUI::~TtUI()
{
  delete rw;
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

  while (true)
  {
    if (term_resized)
    {
      term_resized = false;

      ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
      max_rows = w.ws_row;
      max_cols = w.ws_col;
      fflush(stdout);
      DrawUI();
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

    DrawUI();
  }
}

/*
 * Private Functions
 */

void TtUI::DrawUI()
{
  ResetBoundaries();
  
  TtIO io(io_limits);
  char m; // menu handler
  
  ClrScr();
  DrawDisplayBox();
  DrawPromptBox();

  switch (menu)
  {
    case WELCOME:
    {
      MoveTo(2, 3);
      ResetCursorToPrompt();
      io.ReadChar(" Welcome. Press Any Key to continue.\n\r\x1b[2C");
      menu = FILE_MANAGEMENT;

    } break;

    case FILE_MANAGEMENT:
    {
      ResetCursorToPrompt();
      m = io.ReadChar(" N-> New Workbook. O-> Open Workbook. Q-> Quit.\n\r\x1b[2C");
      
      if (m == 'n' || m == 'N') { menu = NEW_FILE;  }
      if (m == 'o' || m == 'O') { menu = OPEN_FILE; }
      if (m == 'q' || m == 'Q') { menu = QUIT;      }

    } break;

    case NEW_FILE:
    {
      ResetCursorToPrompt();
      io.ReadString("Filename:\n\r\x1b[2C");

      TtString filename = rw->GetParentDir() + io.ToString();
      MoveTo(2, 3);
      printf("Creating File: ");
      filename.Echo();
      //uirw->create_file(filename.get_string());
      MoveTo(3, 3);
      printf("...Done!");
      io.ReadChar("Press Any Key to continue.\n\r\x1b[2C");
      menu = WELCOME;

    } break;

    case OPEN_FILE:
    {
      //int num;
      
      //move_to(2, 3);
      //uirw->print_data_dir_contents();
      //ResetCursorToPrompt();
      //num = io.get_num("Enter File Number to open.\n\r\x1b[2C");

      menu = WELCOME;

    } break;

    case QUIT:
    {
      ResetCursorToPrompt();
      m = io.ReadChar(" Y-> Quit. Enter-> Go Back.\n\r\x1b[2C");
      if (m == 'y' || m == 'Y') { exit_app = true; }

      menu = WELCOME;

    } break;
  }
}

void TtUI::ResetBoundaries()
{
  width = max_cols - 2;
  display_height = max_rows - 5;
  prompt_height= 3;
  io_limits = max_cols - 4;
}

void TtUI::DrawDisplayBox()
{
  MoveTo(1, 1);
  SavePosition();

  printf("┏");
  for (int i = 0; i < width; i++) { printf("━"); }
  printf("┓");

  RestorePosition();
  MoveDown(1);
  
  for (int i = 0; i < display_height; i++)
  {
    printf("┃");
    MoveRight(width);
    printf("┃");
    MoveLeft(width + 2);
    MoveDown(1);
  }

  printf("┗");
  for (int i = 0; i < width; i++) { printf("━"); }
  printf("┛");
}

void TtUI::DrawPromptBox()
{
  MoveTo(display_height + 2, 1);
  SavePosition();

  printf("╭");
  for (int i = 0; i < width; i++) { printf("─"); }
  printf("╮");

  RestorePosition();
  MoveDown(1);
  
  for (int i = 0; i < prompt_height; i++)
  {
    printf("│");
    MoveRight(width);
    printf("│");
    MoveLeft(width + 2);
    MoveDown(1);
  }

  printf("╰");
  for (int i = 0; i < width; i++) { printf("─"); }
  printf("╯");
}

