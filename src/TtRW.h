/*
 * File:   TtRW.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#ifndef TTRW_H
#define TTRW_H

#include "TtInclude.h"
#include "TtString.h"

class TtRW
{
public:
  TtRW();
  ~TtRW();

  void       GetCWDContents();
  int        GetFilesCount ()      { return files_count;  };
  DiscStatus GetStatus     ()      { return status;       };
  TtString   GetParentDir  ()      { return parent_dir;   };
  TtString   GetDirFile    (int i) { return dir_files[i]; };

protected:

private:
  TtString   parent_dir;
  TtString   *dir_files;
  int        files_count;
  DiscStatus status;

};

#endif
