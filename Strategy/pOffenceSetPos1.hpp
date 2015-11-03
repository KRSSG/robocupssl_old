#ifndef POFFENCESETPOSITION1_HPP
#define POFFENCESETPOSITION1_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"

#define centerx 0
#define centery 0
#define gap 1000

namespace Strategy
{
  class POffenceSetPosition1 : public Play
  {
  public:
    inline POffenceSetPosition1(const BeliefState& state) 
      : Play(state)
    {
      name = "OffenceSetPositon1";

      assert(HomeTeam::SIZE == 5); // TestPlay is applicable for a team of 5 robots only

      PositionPlay = PLAYTYPE_YES;
      AttackPlay   = PLAYTYPE_NO;
      Tactic::Param param;
      param.PositionP.align = true;
      //for (int botIDx=0; botIDx<HomeTeam::SIZE; ++botIDx)     
      param.PositionP.x = -HALF_FIELD_MAXX + 2*BOT_RADIUS;
      param.PositionP.y = OUR_GOAL_MINY + 0.2*OUR_GOAL_WIDTH;
      param.PositionP.finalSlope=0;
      roleList[0].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = -4*HALF_FIELD_MAXX/5;
      param.PositionP.y = OUR_GOAL_MAXY+0.2*OUR_GOAL_WIDTH;
      param.PositionP.finalSlope  = 0;
      roleList[1].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = -HALF_FIELD_MAXX/6;
      param.PositionP.y =  0;
      param.PositionP.finalSlope  = 0;
      roleList[2].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = HALF_FIELD_MAXX/4;
      param.PositionP.y = -HALF_FIELD_MAXY/2;
      param.PositionP.finalSlope  = 0;
      roleList[3].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = HALF_FIELD_MAXX/4;
      param.PositionP.y =  HALF_FIELD_MAXY/2;
      param.PositionP.finalSlope  = 0;
      roleList[4].push_back(std::make_pair(Tactic::Position, param));
      
      computeMaxTacticTransits();
    }

    inline ~POffenceSetPosition1()
    { }

    inline bool applicable(void) const
    {
      // printf("Set position is applicable\n");
      // TODO make it more sophisticated
      return true;
    }

    inline Result done(void) const
    {
      printf("%d\n", state.ballPos.x);
      // TODO make it more sophisticated and also use the timeout info to determine if the play has terminated
      // printf("Done condition not finalised\n");
      return NOT_TERMINATED;
    }
  }; // class PTestPlay
} // namespace Strategy

#endif // PTEST_PLAY_HPP
