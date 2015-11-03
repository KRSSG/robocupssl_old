#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <cstdio>
#include <cstdarg>
#include "timer.h"
#include "cs.hpp"

namespace Util
{
  class Logger
  {
  private:
    FILE*     logF;
    CS&       logCS;
    Timer     timer;
    static CS stdoutCS;

  public:
    enum Mode
    {
      Write,
      Append
    };

    Logger(const char* fileName,
           Mode        mode,
           CS&         logCS);

    ~Logger();

    void add(const char* format, ...);

    static void toStdOut(const char* format, ...);

    static void abort(const char* format, ...);
  }; // class Logger
} // namespace Util

#endif // LOGGER_HPP
