#ifndef PEXEC_H
#define PEXEC_H

#include <utility>
#include "naivePS.h"
#include "expPS.h"

// Forward Declarations
namespace Strategy
{
  class BeliefState;
  class Robot;
}

namespace Strategy
{
#ifndef PS_CLASS
# error Macro PS_CLASS has to be defined as the name of one of the derived classed of class PS
#endif

  class PExec : private PS_CLASS
  {
  private:
    Play::Result playResult;
    Robot*       robot[HomeTeam::SIZE];
    Util::CS*    tacticCS[HomeTeam::SIZE];

  public:
    PExec(BeliefState& state, Util::CS& stateCS);

    ~PExec();

  private:
    // Stores the index to the tactics in all role that is to be executed by the team
    unsigned int currTacticIdx;

    // Current tactic in execution by each bot
    std::pair<Tactic::ID, Tactic::Param> currTactic[HomeTeam::SIZE];

    void assignRoles(void);

    bool canTransit(void);

    bool tryTransit(void);

  public:
    void selectPlay(void);

    void executePlay(void);

    void evaluatePlay(void);

    bool playTerminated(void);

    bool playCompleted(void);
  }; // class PExec
} // namespace Strategy

#endif // PEXEC_H