#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>

// simple logging functions, logs with colour and has toggles
// for coding convienience

void plInfo(const uint8_t doLogging, const uint8_t doVerboseLogging,
    const uint8_t isVerbose, const char* tag, const char* message) {

  if (doLogging && ((doVerboseLogging && isVerbose) || !isVerbose)) {
    if (LOG_TO_STDERR) {
      fprintf(stderr, "INFO: [%s] - %s\n", tag, message);
    } else {
      printf("\n\033[%dm[%s] - %s\n\033[0m", INFO_COLOR, tag, message);
    }
  }
}
void plWarning(const uint8_t doLogging, const uint8_t doVerboseLogging,
    const uint8_t isVerbose, const char* tag, const char* message) {

  if (doLogging && ((doVerboseLogging && isVerbose) || !isVerbose)) {
    if (LOG_TO_STDERR) {
      fprintf(stderr, "WARN: [%s] - %s\n", tag, message);
    } else {
      printf("\n\033[%dm[%s] - %s\n\033[0m", WARN_COLOR, tag, message);
    }
  }
}
void plError(const uint8_t doLogging, const uint8_t doVerboseLogging,
    const uint8_t isVerbose, const uint8_t panicOnErr, const char* tag,
    const char* message) {

  if (doLogging && ((doVerboseLogging && isVerbose) || !isVerbose)) {
    if (LOG_TO_STDERR) {
      fprintf(stderr, "ERR : [%s] - %s\n", tag, message);
    } else {
      printf("\n\033[%dm[%s] - %s\n\033[0m", ERR_COLOR, tag, message);
    }
  }

  if (panicOnErr) {
    exit(-1);
  }
}

void plDisplayIfLoggingEnabled(const uint8_t doLogging,
    const uint8_t doVerboseLogging, const char* tag) {
  if (!doVerboseLogging) {
    plInfo(doLogging, doVerboseLogging, 0, tag, "Logging enabled!");
  } else {
    plInfo(doLogging, doVerboseLogging, 1, tag, "Verbose logging enabled!");
  }
}

// looks for -v or -l in the command line arguments, quick and dirty,
// doesn't validate that it is just -v or -l
uint8_t checkForIfLogging(const uint8_t argc, const char **argv) {
  for (size_t i = 1; i < argc; i++)
  {
    if ((strncmp(argv[i], "-l", 2) == 0)
        || (strncmp(argv[i], "-v", 2) == 0)) {
          return 1;
    }
  }

  return 0;
}
// looks for -v in the command line arguments, quick and dirty,
// doesn't validate that it is just -v
uint8_t checkForIfLoggingVerbose(const uint8_t argc, const char **argv) {
  for (size_t i = 1; i < argc; i++)
  {
    if (strncmp(argv[i], "-v", 2) == 0) {
          return 1;
    }
  }

  return 0;
}
