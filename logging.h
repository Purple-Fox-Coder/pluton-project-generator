#ifndef PLIO_H
#define PLIO_H

#ifndef LOG_TO_STDERR
#define LOG_TO_STDERR 0
#endif

#define INFO_COLOR 34
#define WARN_COLOR 33
#define ERR_COLOR  31

#include <stdint.h>

// gen IO  ///////////////////////////////////////

/// assumes null termination (string literal)
void plPrintErr(const char* message);

// logging ///////////////////////////////////////
void plInfo(const uint8_t  doLogging, const uint8_t doVerboseLogging,
    const uint8_t isVerbose, const char* tag, const char* message);

void plWarning(const uint8_t  doLogging, const uint8_t doVerboseLogging,
    const uint8_t isVerbose, const char* tag, const char* message);

void plError(const uint8_t  doLogging, const uint8_t doVerboseLogging,
    const uint8_t isVerbose, const uint8_t exitOnErr, const char* tag,
    const char* message);


void plDisplayIfLoggingEnabled(const uint8_t doLogging,
    const uint8_t doVerboseLogging, const char* tag);

uint8_t checkForIfLogging(const uint8_t  argc, const char **argv);
uint8_t checkForIfLoggingVerbose(const uint8_t  argc, const char **argv);

#endif // PLIO_H
