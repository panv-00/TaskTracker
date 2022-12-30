/*
 * File:   TtRW.cpp
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#include "TtRW.h"


TtRW::TtRW() :
  parent_dir {""},
  dir_files {0},
  files_count {0},
  status {DISC_STATUS_UNKNOWN}
{

}

TtRW::~TtRW()
{
  if (dir_files != NULL) { delete[] dir_files; }
}

void TtRW::GetCWDContents()
{
  TtString home = getenv("HOME");

  if (home.GetLength() == 0)
  {
    status = HOME_ENV_ERROR;

    return;
  }

  DIR *dir;

  parent_dir = home + "/.config";
  dir = opendir(parent_dir.ToString());
  
  if (dir == NULL
      && mkdir(parent_dir.ToString(), S_IRWXU | S_IRWXG | S_IRWXO) != 0)
  {
    status = CONFIG_CREATE_ERROR;

    return;
  }

  closedir(dir);

  parent_dir = home + "/.config/TaskTracker";
  dir = opendir(parent_dir.ToString());

  if (dir == NULL
      && mkdir(parent_dir.ToString(), S_IRWXU | S_IRWXG | S_IRWXO) != 0)
  {
    status = TT_CREATE_ERROR;

    return;
  }

  struct dirent *ent;

  while ((ent = readdir(dir)) != NULL)
  {
    if (ent->d_type != DT_DIR)
    {
      files_count++;
    }
  }

  closedir(dir);
  dir = opendir(parent_dir.ToString());

  dir_files = new TtString[files_count];
  int count = 0;
  
  while ((ent = readdir(dir)) != NULL)
  {
    if (ent->d_type != DT_DIR)
    {
      dir_files[count++] = ent->d_name;
    }
  }

  free(ent);
  closedir(dir);
  status = DISC_STATUS_HEALTHY;
}

