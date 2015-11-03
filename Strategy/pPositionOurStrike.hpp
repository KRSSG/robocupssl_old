#ifndef PPOSITIONOURSTRIKE_HPP
#define PPOSITIONOURSTRIKE_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"

/* This play positions the bots in the position in case we lose the toss and Opponent strikes the ball first. */
namespace Strategy
{
  class PPositionOurStrike : public Play
  {
  public:
    inline PPositionOurStrike(const BeliefState& state) 
      : Play(state)
    {
      name = "PositionOurStrike";

      assert(HomeTeam::SIZE == 5);
      
      PositionPlay = PLAYTYPE_YES;
      AttackPlay   = PLAYTYPE_NO;
      
      Tactic::Param param;
      param.PositionP.align = true;
      param.PositionP.x = -3*HALF_FIELD_MAXX/4;
      param.PositionP.y = 0;
      param.PositionP.finalSlope=0;
      roleList[0].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.align = true;
      param.PositionP.x = -HALF_FIELD_MAXX/4;
      param.PositionP.y = HALF_FIELD_MAXY/4;
      param.PositionP.finalSlope  = 0;
      roleList[1].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.align = true;
      param.PositionP.x = -HALF_FIELD_MAXX/4;
      param.PositionP.y = -HALF_FIELD_MAXY/4;
      param.PositionP.finalSlope  = 0;
      roleList[2].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.align = true;
      param.PositionP.x = CENTER_CIRCLE_DIAMETER/5;
      param.PositionP.y = 0;
      param.PositionP.finalSlope  = PI;
      roleList[3].push_back(std::make_pair(Tactic::Position, param));
      
      /* Always make one robot as goalie*/
      roleList[4].push_back(std::make_pair(Tactic::GoalieOur, param));
      
      computeMaxTacticTransits();
    }

    inline ~PPositionOurStrike()
    { }

    inline bool applicable(void) const
    {
      // printf("Set position is applicable\n");
      // TODO make it more sophisticated
      return true;
    }

    inline Result done(void) const
    {
      // TODO make it more sophisticated and also use the timeout info to determine if the play has terminated
      // printf("Done condition not finalised\n");
      return NOT_TERMINATED;
    }
  }; // class PTestPlay
} // namespace Strategy

#endif // PTEST_PLAY_HPP
