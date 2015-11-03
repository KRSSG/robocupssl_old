#ifndef ROBOT_H
#define ROBOT_H

#include "thread.h"
#include "tactic.h"

// Forward Declarations
namespace Util
{
  class CS;
}

namespace Strategy
{
  class BeliefState;
}

namespace Strategy
{
  class Robot : private Util::Thread
  {
    friend class PExec;

  public:
    // Stores the current tactic and is controlled by the Play Layer
    Tactic::ID     tIDSh;
    // Stores the current tactic's parameters and is controlled by the Play Layer
    Tactic::Param  tParamSh;
    // Stores the current tactic's state and is controlled by the Play Layer
    Tactic::TState tStateSh;
    // List of tactics: A map of ID -> Tactic objects
    Tactic*        tacticList[Tactic::MAX_TACTICS];

  private:
    int            botID;

    // Critical Section object for synchronizing access to the above two fields
    Util::CS*      tacticCS;
    // Belief State object that the robot will use
    BeliefState*   state;
    // Shared Belief State object between it and the main thread
    BeliefState&   stateSh;
    // Critical Section object for synchronizing access to the belief state
    Util::CS&      stateCS;

    // The function in which the Tactic loop runs forever
    void run();

  public:
    Robot(BeliefState& stateSh,
          Util::CS&    stateCS,
          Util::CS*    tacticCS,
          int          botID);

    ~Robot();
  }; // class Robot
} // namespace Strategy

#endif // ROBOT_H
