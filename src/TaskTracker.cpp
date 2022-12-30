/*
 * File:   TaskTracker.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtString.h"
#include "TtTime.h"
#include "TtDate.h"
#include "TtIO.h"
#include "TtRW.h"
#include "TtUI.h"

int main(int argc, char** argv)
{
  ClrScr();
  printf("Testing Directories!\n\n");

  TtUI ui;
  ui.Run();

/*

  TtRW *rw = new TtRW();

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

  delete rw;
*/
  return 0;
}
