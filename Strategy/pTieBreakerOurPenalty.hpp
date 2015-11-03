#ifndef PTIEBREAKEROURPENALTY_HPP
#define PTIEBREAKEROURPENALTY_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"

/* This play positions performs penalty shootout during tiebreaker according to FIRA Rules */
namespace Strategy
{
  class PTieBreakerOurPenalty : public Play
  {
  public:
    inline PTieBreakerOurPenalty(const BeliefState& state) 
      : Play(state)
    {
      name = "TieBreakerOurPenalty";

      assert(HomeTeam::SIZE == 5); 
      
      PositionPlay = PLAYTYPE_YES;
      AttackPlay   = PLAYTYPE_NO;
      
      Tactic::Param param;
      /* There is only one robot in the field. Make it as goalie */
      roleList[0].push_back(std::make_pair(Tactic::GoalieOur, param));
      
      param.PositionP.x = -HALF_FIELD_MAXX/4;
      param.PositionP.y = HALF_FIELD_MAXY/4;
      param.PositionP.finalSlope  = 0;
      roleList[1].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = -HALF_FIELD_MAXX/4;
      param.PositionP.y = -HALF_FIELD_MAXY/4;
      param.PositionP.finalSlope  = 0;
      roleList[2].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = -CENTER_CIRCLE_DIAMETER/2;
      param.PositionP.y = 0;
      param.PositionP.finalSlope  = 0;
      roleList[3].push_back(std::make_pair(Tactic::Position, param));
      
      /* Always make one robot as goalie*/
      roleList[4].push_back(std::make_pair(Tactic::GoalieOur, param));
      
      /* Set the timeout to 35( 30 + 5) seconds as mentioned in the FIRA rules for TieBreakerPenalyShootout */
      setTimeout(35);
      computeMaxTacticTransits();
    }

    inline ~PTieBreakerOurPenalty()
    { }

    inline bool applicable(void) const
    {
      // printf("Set position is applicable\n");
      // TODO make it more sophisticated
      return true;
    }

    inline Result done(void) const
    {
      /* The penalty play can finish because of 3 reasons - 
       * 1. Timeout of 30 secs: 
       * 2. Ball goes out of DBox
       * 3. A goal is scored 
       */
      if(!state.pr_ball_in_opp_dbox)
        return COMPLETED;
      else
        return NOT_TERMINATED;
    }
  }; // class PTestPlay
} // namespace Strategy

#endif // PTEST_PLAY_HPP
