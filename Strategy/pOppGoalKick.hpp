#ifndef POPPGOALKICK_HPP
#define POPPGOALKICK_HPP

#include <utility>
#include "play.hpp"
#include "kalman.h"
#include "beliefState.h"
#include "tactic.h"
#include "fieldConfig.h"
using namespace std;

namespace Strategy
{
  class POppGoalKick : public Play
  {
    public: 
    inline POppGoalKick(const BeliefState& state) : Play(state)
    {
      name = "OppGoalKick";
      PositionPlay = PLAYTYPE_NO;
      AttackPlay   = PLAYTYPE_NO;
      assert(HomeTeam::SIZE ==5);
      Tactic::Param param;
      /* Role 0 - Goalie */
      roleList[0].push_back(std::make_pair(Tactic::GoalieOur,param));
      /* Role 1 - Defender*/
      param.DefendLineP.x1 = -HALF_FIELD_MAXX/2;
      param.DefendLineP.y1 = -HALF_FIELD_MAXY;
      param.DefendLineP.x2 = -HALF_FIELD_MAXX/2;
      param.DefendLineP.y2 = HALF_FIELD_MAXY;
      roleList[1].push_back(std::make_pair(Tactic::DefendLine,param));
      /* Role 2 -defender */
      param.DefendLineP.x1 = -3*HALF_FIELD_MAXX/4;
      param.DefendLineP.y1 = -HALF_FIELD_MAXY;
      param.DefendLineP.x2 = -3*HALF_FIELD_MAXX/4;
      param.DefendLineP.y2 = HALF_FIELD_MAXY;
      roleList[2].push_back(std::make_pair(Tactic::DefendLine,param));
      /* Role 3 - Bot1 ready to intercept ball */
      param.PositionP.x=-HALF_FIELD_MAXX/4;
      param.PositionP.y= -HALF_FIELD_MAXY/2;
      param.PositionP.align=true;
      param.PositionP.finalSlope= PI/2;
      roleList[3].push_back(std::make_pair(Tactic::Position,param));
      /* Role 4 - Midfield Player */
      param.PositionP.x=-HALF_FIELD_MAXX/4;
      param.PositionP.y= 0;
      param.PositionP.align=true;
      param.PositionP.finalSlope= PI/2;
      roleList[4].push_back(std::make_pair(Tactic::Position, param));
      
      computeMaxTacticTransits();
    }
          
    inline ~POppGoalKick()
    {
      
    }
    inline bool applicable(void) const
    {
    if(state.pr_oppKickOff)
        return true;
      else
        return false;
    }
    inline Result done(void) const
    {
      if(!(state.ballPos.x > (HALF_FIELD_MAXX-DBOX_WIDTH))&&((state.ballPos.y < OUR_GOAL_MAXY)&&(state.ballPos.y > -OUR_GOAL_MAXY)))
        return COMPLETED;
      else  
        return NOT_TERMINATED;
    }
  };
}
#endif // POPP_GOAL_KICK_HPP
