#ifndef TTSTOP_HPP
#define TTSTOP_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
  class TStop : public Tactic
  {
  public:
    TStop(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { } // TTStop

    ~TStop()
    { } // ~TTStop

    inline bool isActiveTactic(void) const
    {
      return false;
    }

    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
      for (std::list<int>::iterator it=freeBots.begin(); it!=freeBots.end(); ++it)
      {
        // TODO make the bot choosing process more sophisticated, the logic below returns the 1st available bot
        return *it;
      }
      Util::Logger::abort("No bot available for role assignment");
      return -1;
    } // chooseBestBot

    void execute(const Param& tParam)
    {
      // Select the skill to the executed next
      sID = SkillSet::Stop;
      
      // Execute the selected skill
      skillSet->executeSkill(sID, sParam);

      if (state->homeVel[botID].absSq() < ZERO_VELOCITY_THRESHOLD*ZERO_VELOCITY_THRESHOLD)
      {
        tState = COMPLETED;
      }
    }
  }; // class TTStop
} // namespace Strategy

#endif // TTSTOP_HPP
