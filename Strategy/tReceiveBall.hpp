#ifndef TRECEIVEBALL_HPP
#define TRECEIVEBALL_HPP
#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"
namespace Strategy
{
  class TReceiveBall: public Tactic
  {
  public:
    TReceiveBall(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { } // TReceiveBall
    ~TReceiveBall()
    { } // ~TReceiveBall
    inline bool isActiveTactic(void) const
    {
      return false;
    }
    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
      int minv = *(freeBots.begin());
      int mindis = 10000;
      for(std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
      {
        // TODO make the bot choosing process more sophisticated, the logic below returns the 1st available bot
        float dis_from_ball = (state->homePos[*it] - state->ballPos).absSq();
        //cannot use below condition since tparam is not passed as paramater
        //float dis_from_ball = (state->homePos[*it] - tParam.DefendPointP).absSq();
        if(dis_from_ball < mindis)
        {
          dis_from_ball = mindis;
          minv = *it;
        }
      }
      return minv;
    } // chooseBestBot)
    void execute(const Param& tParam)
    {
      Vector2D<float> homePosfloat;
      homePosfloat.x = state->homePos[botID].x;
      homePosfloat.y = state->homePos[botID].y;
      float dist = Vector2D<int>::dist(state->ballPos, state->homePos[botID]);
      float angle = normalizeAngle(Vector2D<float>::angle(state->ballVel, homePosfloat));   //angle between ball's predicted path and bot position
      Vector2D<float> target = state->ballVel / ((state->ballVel).abs());
      target = target * (dist * cos(angle));

      if(state->pr_looseBall)
      {
        sID = SkillSet::GoToPoint;
        sParam.GoToPointP.x = target.x;
        sParam.GoToPointP.y = target.y;
        sParam.GoToPointP.align = true;
        skillSet->executeSkill(sID, sParam);
      }
      if(state->pr_goalscored || state->pr_ourBall || state->pr_oppBall)
        tState = COMPLETED;
      else
        tState = RUNNING;
    }
  } ;// class TReceiveBall
} // namespace Strategy
#endif // TRECEIVEBALL_HPP
