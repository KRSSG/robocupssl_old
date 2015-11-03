#ifndef TTDRAGTOGOALOPP_HPP
#define TTDRAGTOGOALOPP_HPP


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
  class TDragToGoalOpp : public Tactic
  {
  public:
    TDragToGoalOpp(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { } // TCharge

    ~TDragToGoalOpp()
    { } // ~TCharge

    inline bool isActiveTactic(void) const
    {
      return true;
    }

    int chooseBestBot(std::list<int>& freeBots) const
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
      // Select the skill to be executed next
      #undef HALF_FIELD_MAXX
      #define HALF_FIELD_MAXX -SELECT(3025, 225)

      Vector2D<int> fastBallPos  = Vector2D<int>((int)state->ballPos.x + 0.3*state->ballVel.x, (int)state->ballPos.y + 0.3*state->ballVel.y);
      Vector2D<int> goalPoint(HALF_FIELD_MAXX, 0);
      float theta               = normalizeAngle(Vector2D<int>::angle(goalPoint, fastBallPos));
      float angleWithBall       = normalizeAngle(Vector2D<int>::angle(fastBallPos, state->homePos[botID]));
      Vector2D<int> finalPoint  = state->homePos[botID] + Vector2D<int>(2*BOT_BALL_THRESH*cos(theta), 2*BOT_BALL_THRESH*sin(theta));
      
      Vector2D<int> targetPoint = fastBallPos - Vector2D<int>(2*BOT_BALL_THRESH*cos(theta), 2*BOT_BALL_THRESH*sin(theta));
      float dist = Vector2D<int>::dist(targetPoint, state->homePos[botID]);
      printf("Drag to Goal: %f, %d, %f, \n", dist, 2*BOT_BALL_THRESH, fabs(firaNormalizeAngle(theta)));
      float sign = (state->homePos[botID].x - fastBallPos.x)*(state->homePos[botID].x - HALF_FIELD_MAXX);
      static int stt = 1;
      printf("State: %d\n", stt);
      if(stt == 0 && dist < 2*BOT_BALL_THRESH && fabs(firaNormalizeAngle(theta - angleWithBall)) < 0.05 && sign > 0) {
        stt = 1;
      }
      if(stt == 1 && dist > 3*BOT_BALL_THRESH || sign < 0) {
        stt = 0;
      }
      if(stt == 1)
      {
        Util::Logger::toStdOut("Dribbling to goal %d %d", goalPoint.x, goalPoint.y);
        sID = SkillSet::GoToPoint;
        sParam.GoToPointP.finalslope = normalizeAngle(Vector2D<int>::angle( goalPoint, fastBallPos ));
        sParam.GoToPointP.x = goalPoint.x;
        sParam.GoToPointP.y = goalPoint.y;
        
        sParam.GoToPointP.finalVelocity = 0.1;
        sParam.GoToPointP.align = true;
        skillSet->executeSkill(sID, sParam);
      }
      else{
        Util::Logger::toStdOut("Going to ball");
        sID = SkillSet::GoToPoint;
        sParam.GoToPointP.align = true;
        sParam.GoToPointP.x = targetPoint.x;
        sParam.GoToPointP.y = targetPoint.y;
        sParam.GoToPointP.finalslope = Vector2D<int>::angle(goalPoint, state->homePos[botID]);
        skillSet->executeSkill(sID,sParam);
      }
      if (state->pr_oppBall || state->pr_looseBall/*||state->pr_goalscored*/)
      {
//      tState = COMPLETED;
      }
      #undef HALF_FIELD_MAXX
      #define HALF_FIELD_MAXX SELECT(3025, 225)
    }
  }; // class TCharge
} // namespace Strategy

#endif // TTCharge_HPP
