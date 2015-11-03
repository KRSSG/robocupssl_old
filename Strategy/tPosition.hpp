#ifndef TPOSITION_HPP
#define TPOSITION_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"
#include <sys/time.h>
#include <unistd.h>
namespace Strategy
{
  class TPosition: public Tactic
  {
  public:

    TPosition(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    {

    } // TPosition

    ~TPosition()
    { } // ~TPosition
    inline bool isActiveTactic(void) const
    {
      return false;
    }
//CHOOSEbEST bOT AND the giving of parameters for going to the required point needs to be entered
//Choose best bot also needs to get the params that the tactic has in order to choose the best bot....

    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
      assert(tParam != 0);
      int minv   = *(freeBots.begin());
      int mindis = 1000000000;
      Vector2D<int> tGoToPoint(tParam->PositionP.x, tParam->PositionP.y);
      for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
      {
        // TODO make the bot choosing process more sophisticated, the logic below returns the 1st available bot
        float dis_from_point = (state->homePos[*it] - tGoToPoint).absSq();
        if(*it == botID)
          dis_from_point -= HYSTERESIS;
        if(dis_from_point < mindis)
        {
          mindis = dis_from_point;
          minv = *it;
        }
      }
      printf("%d assigned Position\n", minv);
      return minv;
    } // chooseBestBot

    void execute(const Param& tParam)
    {
      // Select the skill to the executed next
//      printf("botpos x:%d\ty:%d\n", state->homePos[botID].x, state->homePos[botID].y);

      sID = SkillSet::GoToPoint;
      sParam.GoToPointP.x             = tParam.PositionP.x ;
      sParam.GoToPointP.y             = tParam.PositionP.y ;
      sParam.GoToPointP.align         = tParam.PositionP.align;
      sParam.GoToPointP.finalslope    = tParam.PositionP.finalSlope ;
      sParam.GoToPointP.finalVelocity = tParam.PositionP.finalVelocity;

      // Execute the selected skill
      skillSet->executeSkill(sID, sParam);

      if((state->homePos[botID] - Vector2D<int>(tParam.PositionP.x, tParam.PositionP.y)).absSq() < BOT_POINT_THRESH * BOT_POINT_THRESH)
      {
        tState = COMPLETED;
      }
    }
  }; // class TPosition
} // namespace Strategy

#endif // TPOSITION_HPP
