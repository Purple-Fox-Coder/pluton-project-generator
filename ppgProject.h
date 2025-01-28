#ifndef PPG_PROJECT_H
#define PPG_PROJECT_H

#include <stdint.h>

// OS specific includes, non-windows systems will be defaulted to POSIX
#ifdef _WIN32
#include "ppgWin.h"
#else
#include "ppgPOSIX.h"
#endif

#define PPG_VERSIONNO   "1.0.0"
#define PPG_DESCRIPTION "A simple project generator, simply choose the options you would like, and let the program generate the files for you."

// makefile ID number (for the purposes of this program)
#ifndef PPG_MKFILE
#define PPG_MKFILE 10
#endif // PPG_MKFILE

// defaults
#define PPG_DEFAULTNAME   "ppgProject"
#define PPG_DEFAULTALIAS  "main"
#define PPG_DEFAULTTMPDIR "~/ppg/templates"

typedef struct {
  char* workingDirectory;
  char* templateDirectory;
  char* projectName;
  char* projectAlias;

  uint8_t buildSystemID;
} PPGProject;

void displayHelpMessage(void);
void displayInfoPage(void);

void findAndReplace(const char *find, const char *replacement,
  const char *original);

void parseArgs(int argc, const char* argv[], PPGProject* progectInfo);

int8_t awaitYesOrNo(void);

int8_t generateProject(PPGProject* progectInfo);

void requestMoreInfo(PPGProject* progectInfo);

#endif // PPG_PROJECT_H
