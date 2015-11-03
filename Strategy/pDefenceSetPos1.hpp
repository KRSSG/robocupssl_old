#ifndef PDEFENCESETPOSITION1_HPP
#define PDEFENCESETPOSITION1_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"

namespace Strategy
{
  class PDefenceSetPosition1 : public Play
  {
  public:
    inline PDefenceSetPosition1(const BeliefState& state) 
      : Play(state)
    {
      name = "DefenceSetPositon1";
      
      PositionPlay = PLAYTYPE_YES;
      AttackPlay   = PLAYTYPE_NO;
      
      assert(HomeTeam::SIZE == 5); // TestPlay is applicable for a team of 5 robots only

      Tactic::Param param;
      param.PositionP.align = true;
          
      param.PositionP.x = -HALF_FIELD_MAXX/6;
      param.PositionP.y = 0;
      param.PositionP.finalSlope=0;
      param.PositionP.finalVelocity = 0;
      roleList[0].push_back(std::make_pair(Tactic::Position, param));
      
      Tactic::Param param2;
      param2.PositionP.x = -HALF_FIELD_MAXX/4;
      param2.PositionP.y = -HALF_FIELD_MAXY/2;
      param2.PositionP.finalSlope  = 0;
      param2.PositionP.finalVelocity = 0;
      roleList[1].push_back(std::make_pair(Tactic::Position, param2));
      
      Tactic::Param param3;
      param3.PositionP.x = -HALF_FIELD_MAXX/4;
      param3.PositionP.y =  HALF_FIELD_MAXY/2;
      param3.PositionP.finalSlope  = 0;
      param3.PositionP.finalVelocity = 0;
      roleList[2].push_back(std::make_pair(Tactic::Position, param3));
      
      Tactic::Param param4;
      param4.PositionP.x = -3*HALF_FIELD_MAXX/4;
      param4.PositionP.y = -HALF_FIELD_MAXY/4;
      param4.PositionP.finalSlope  = 0;
      param4.PositionP.finalVelocity = 0;
      roleList[3].push_back(std::make_pair(Tactic::Position, param4));
      
      Tactic::Param param5;
      param5.PositionP.x = -3*HALF_FIELD_MAXX/4;
      param5.PositionP.y =  HALF_FIELD_MAXY/4;
      param5.PositionP.finalSlope  = 0;
      param5.PositionP.finalVelocity = 0;
      roleList[4].push_back(std::make_pair(Tactic::Position, param5));
      
      computeMaxTacticTransits();
    }

    inline ~PDefenceSetPosition1()
    { }

    inline bool applicable(void) const
    {
      // printf("Set position is applicable\n");
      // TODO make it more sophisticated
      printf("Set position CHECKING %d\n", state.gameRunning);
      if(!Play::applicable()) return false;
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
