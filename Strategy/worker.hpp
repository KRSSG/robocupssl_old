#include "mainheaders.hpp"
#include "thread.h"
using namespace Strategy;

class Worker:public Util::Thread {
public:
  bool &running;
  BeliefState &state;
  Worker(bool &running_, BeliefState &state_):running(running_),state(state_) {}
  void run()
  {
    Util::CS loggerCS;
    Util::Logger logger("timelog.log", Util::Logger::Write, loggerCS);
    Util::CS    stateCS;
    Kalman      kFilter;
    VisionThread vThread(kFilter);
    vThread.start();

    PExec       pExec(state, stateCS);

    Util::Logger::toStdOut("Waiting for signal from Referee Box and SSLVision Client\n");

  #ifdef RUN_REFBOX
      unsigned char   refBoxCmdCounter = -1;
      HAL::RefBoxCmd  refBoxCmdSh;//  = new RefBoxCmd();
      Util::CS        refBoxCS;//     = new CS();
      RefBoxThread    refBoxThread(&refBoxCmdSh, &refBoxCS);
      refBoxThread.start();
  #endif // RUN_REFBOX

    state.refreeUpdated = false;
    while (running)
    {
      kFilter.update(state);
      
  #ifdef RUN_REFBOX
      {
        // Critical Section protected by refBoxCS
        refBoxCS.enter();
        // Updating from Referee Box and the Game State
        if (refBoxCmdCounter != refBoxCmdSh.cmdCounter)
        {
          state.refreeUpdated = true;
          Util::Logger::toStdOut("Ref Box Updated to %d\n", refBoxCmdSh.cmdCounter);
          refBoxCmdCounter      = refBoxCmdSh.cmdCounter;
          stateCS.enter();
          state.updateStateFromRefree(refBoxCmdSh);
          stateCS.leave();
        }
        refBoxCS.leave();
      } // End of Critical Section protected by refBoxCS
  #endif // RUN_REFBOX

      {
        if(state.refreeUpdated) 
        {
          state.refreeUpdated = false;
          Util::Logger::toStdOut("Command From Refee.. Reselecting play..\n");
          pExec.selectPlay();
        }
        else if (pExec.playTerminated())
        {
          Util::Logger::toStdOut("*************Play terminated.Select new play\n*********************");
          pExec.evaluatePlay();
          pExec.selectPlay();
        } 
        pExec.executePlay();
      }
      usleep(16000);  // Adding sleep to this thread of execution to prevent CPU hogging
    }
    vThread.stop();
    Util::Logger::toStdOut("Exiting process");
  }
};