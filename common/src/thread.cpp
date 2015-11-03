#ifndef WIN32
#include <errno.h>
#include <unistd.h>
#endif // !WIN32
#include <cstring>
#include "thread.h"
#include "logger.h"

namespace Util
{
  Thread::Thread() :
    handle(0)
  { }

  Thread::~Thread()
  {
    if (handle != 0)
    {
      stop();
    }
  }

  void Thread::start()
  {
#ifdef WIN32
    LPDWORD threadID = 0;
    handle = CreateThread(NULL,           // Security attributes
                          0,              // Stack size
                          threadFunc,     // Thread function
                          (Thread*)this,  // Parameter
                          0,              // Flags
                          threadID        // Thread ID
                         );
    assert(handle); // Failed to create thread
    setPriority(Thread::P_NORMAL);
#else
    if (pthread_create(&handle, NULL, threadFunc, this) != 0)
    {
      Logger::abort("Could not create thread: %s", strerror(errno));
    }
#endif // !WIN32
  }

  void Thread::sleep(long ms)
  {
#ifdef WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif // !WIN32
  }

  void Thread::stop()
  {
    assert(handle);

#ifdef WIN32
    DWORD status = 0;
    ExitThread(status);
    CloseHandle(handle);
#else
    int retval;
    pthread_exit(&retval);
#endif // !WIN32

    handle = 0;
  }

#ifdef WIN32
  void Thread::setPriority(int tp)
  {

    assert(handle); // Thread object is null. Priority cannot be set
    int ret = SetThreadPriority(handle, tp);
    assert(ret); // Failed to set priority
  }

  void Thread::suspend()
  {
    assert(handle); // Thread object is null
    int ret = SuspendThread(handle);
    assert(ret >= 0); // Failed to suspend thread
  }

  void Thread::resume()
  {
    assert(handle); // Thread object is null
    int ret = ResumeThread(handle);
    assert(ret >= 0); // Failed to resume thread
  }

  DWORD WINAPI Thread::threadFunc(LPVOID pv)
  {
    (reinterpret_cast<Thread *>(pv))->run();
    return 0;
  }
#else
  void* Thread::threadFunc(void* arg)
  {
    reinterpret_cast<Thread *>(arg)->run();
    return 0;
  }
#endif // !WIN32
} // namespace Util
