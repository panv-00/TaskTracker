/*
 * File:   TtInclude.h
 * Author: Michel Alwan
 *
 * Created on 2022-12-29
 */

#ifndef TTINCLUDE_H
#define TTINCLUDE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/ioctl.h>

//#include <sys/select.h>
//#include <sys/types.h>
//#include <stdint.h>

#define BUFFSIZE         1000

#define TAB              9
#define ESCAPE_CHAR      27
#define ARROW_CHAR       91
#define ARROW_UP         65
#define ARROW_DN         66
#define ARROW_RT         67
#define ARROW_LT         68
#define BACKSPACE        127
#define START_INPUT      "\r\x1b[2C"

typedef enum
{
  SUN = 0,
  MON,
  TUE,
  WED,
  THU,
  FRI,
  SAT

} DayOfWeek;

typedef enum
{
  CLR_DEFAULT  =  0,
  CLR_BLACK_FG = 30,
  CLR_RED_FG       ,
  CLR_GREEN_FG     ,
  CLR_YELLOW_FG    ,
  CLR_BLUE_FG      ,
  CLR_MAGENTA_FG   ,
  CLR_CYAN_FG      ,
  CLR_WHITE_FG     ,

  CLR_BLACK_BG = 40,
  CLR_RED_BG       ,
  CLR_GREEN_BG     ,
  CLR_YELLOW_BG    ,
  CLR_BLUE_BG      ,
  CLR_MAGENTA_BG   ,
  CLR_CYAN_BG      ,
  CLR_WHITE_BG

} ColorCode;

typedef enum
{
  HOME_ENV_ERROR = -3,
  CONFIG_CREATE_ERROR,
  TT_CREATE_ERROR,
  DISC_STATUS_HEALTHY,
  DISC_STATUS_UNKNOWN

} DiscStatus;

typedef enum
{
  WELCOME,         // Welcome Screen.
  FILE_MANAGEMENT, // N-> New Workbook. O-> Open Workbook. Q-> Quit.
  NEW_FILE,        // something for new file.
  OPEN_FILE,       // something for open file.
  QUIT             // Y-> Quit. Enter-> Go Back.

} UserMenu;

#endif
