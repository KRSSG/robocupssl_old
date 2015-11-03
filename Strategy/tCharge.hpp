#ifndef TTCHARGE_HPP
#define TTCHARGE_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

//TODO: Make a tactic such as tStealAndShoot which steals the ball, then shoots it, and 
//      continues the stealing a few times if a goal isn't scored.

namespace Strategy
{
  class TCharge : public Tactic
  {
  public:
    TCharge(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { } // TCharge

    ~TCharge()
    { } // ~TCharge

    inline bool isActiveTactic(void) const
    {
      return true;
    }

    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
      int minv = *(freeBots.begin());
      int mindis = 10000;
      for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
      {
        // TODO make the bot choosing process more sophisticated, the logic below returns the 1st available bot
        float dis_from_ball = (state->homePos[*it] - state->ballPos).absSq();
        if(dis_from_ball < mindis)
        {
          dis_from_ball = mindis;
          minv = *it;
        }
      }
      Util::Logger::toStdOut("Selected bot %d\n", minv);
      return minv;
      
    } // chooseBestBot


    void execute(const Param& tParam)
    {
		if(state->pr_ourBall)
		{	
			sID = SkillSet::DribbleToPoint;
			sParam.DribbleToPointP.x=HALF_FIELD_MAXX;
			sParam.DribbleToPointP.y=(OPP_GOAL_MAXY+OPP_GOAL_MINY)/2;
			skillSet->executeSkill(sID, sParam);
		}
		else if(state->pr_oppBall || state->pr_looseBall)
		{
			sID=SkillSet::GoToBall;
			sParam.GoToBallP.intercept=false;
			skillSet->executeSkill(sID,sParam);
		}
	
		if (state->pr_goalscored)
			tState = COMPLETED;
		else
			tState = RUNNING;
	}
      
      
      
    };
// class TCharge
} // namespace Strategy

#endif // TTCharge_HPP
