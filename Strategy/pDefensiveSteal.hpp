#ifndef PDEFENSIVESTEAL_HPP
#define PDEFENSIVESTEAL_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"

namespace Strategy
{
  class PDefensiveSteal : public Play
  {
  public:
    inline PDefensiveSteal(const BeliefState& state) 
      : Play(state)
    {
      name = "DefensiveSteal";

      assert(HomeTeam::SIZE == 5); // TestPlay is applicable for a team of 3 robots only
      PositionPlay = PLAYTYPE_NO;
      AttackPlay   = PLAYTYPE_NO;
      Tactic::Param param;
      roleList[0].push_back(std::make_pair(Tactic::GoalieOur, param));
      
      roleList[1].push_back(std::make_pair(Tactic::Steal, param));
      
      roleList[2].push_back(std::make_pair(Tactic::Steal, param));
      
      param.PositionP.x = -3*HALF_FIELD_MAXX/4;
      param.PositionP.y = -HALF_FIELD_MAXY/4;
      param.PositionP.finalSlope  = 0;
      roleList[3].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = -3*HALF_FIELD_MAXX/4;
      param.PositionP.y =  HALF_FIELD_MAXY/4;
      param.PositionP.finalSlope  = 0;
      roleList[4].push_back(std::make_pair(Tactic::Position, param));
      
      computeMaxTacticTransits();
    }

    inline ~PDefensiveSteal()
    { }

    inline bool applicable(void) const
    {
      if(!Play::applicable()) return false;
      return state.pr_oppBall;
    }

    inline Result done(void) const
    {
      if(state.pr_oppBall)
        return NOT_TERMINATED;
      // TODO Improve success conditions.
      return COMPLETED;
    }
  }; // class PTestPlay
} // namespace Strategy

#endif // PTEST_PLAY_HPP
