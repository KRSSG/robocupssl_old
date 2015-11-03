#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "comdef.h"
#include "logger.h"

namespace Util
{
  // Defining the static variable stdoutCS of class Logger
  CS Logger::stdoutCS;

  Logger::Logger(const char* fileName,
                 Mode        mode,
                 CS&         logCS) :
    logCS(logCS)
  {
    timer.start();
    switch (mode)
    {
      case Write:
        logF = fopen(fileName, "w");
        assert(logF != NULL);
        break;

      case Append:
        logF = fopen(fileName, "a");
        assert(logF != NULL);
        break;

      default:
        Logger::abort("Undefined mode used");
    }
  } // Logger

  Logger::~Logger()
  {
    if (logF != NULL)
    {
      fclose(logF);
    }
  } // ~Logger

  void Logger::add(const char* format, ...)
  {
    va_list args;
    va_start(args, format);

    logCS.enter();
    fprintf(logF, "%7dms ", timer.split());
    vfprintf(logF, format, args);
    fprintf(logF, "\n");
    fflush(logF);
    logCS.leave();
  } // add

  void Logger::toStdOut(const char* format, ...)
  {
    va_list args;
    va_start(args, format);

    stdoutCS.enter();
    vfprintf(stdout, format, args);
    fflush(stdout);
    stdoutCS.leave();
  } // toStdOut

  void Logger::abort(const char* format, ...)
  {
    static char msg[1024];
    static va_list args;

    va_start(args, format);

    stdoutCS.enter();
    sprintf(msg, format, args);
    fprintf(stderr, "%s", msg);
    fflush(stderr);
    stdoutCS.leave();
#ifdef WIN32
    MessageBox(NULL, TEXT(msg), TEXT("Aborting..."), MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
#endif // WIN32
    exit(EXIT_FAILURE);
  }
} // namespace Util