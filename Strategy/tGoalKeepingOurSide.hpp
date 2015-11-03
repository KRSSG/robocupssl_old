#ifndef TGOALKEEPINGOUR_HPP
#define TGOALKEEPINGOUR_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"
#include "geometry.hpp"
#define GOAL_Y 0
#define AWAYGOAL_X HALF_FIELD_MAXX
namespace Strategy
{
  class TGoalKeepingOurSide : public Tactic
  {
  public:
    int state1;
    TGoalKeepingOurSide(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    {
      state1 = 0;
    } // TGoalKeeping

    ~TGoalKeepingOurSide()
    { } // ~TGoalKeeping
    inline bool isActiveTactic(void) const
    {
      return false;
    }

    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
    {
      int minv = *(freeBots.begin());
      int mindis = 1000000000;
      Point2D<int> goalPos(-(HALF_FIELD_MAXX), 0);
      for(std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
      {
        float dis_from_ball = (state->homePos[*it] - goalPos).absSq();//state->home_goalpoints[2] is center of our goal
        if(dis_from_ball < mindis)
        {
          mindis = dis_from_ball;
          minv = *it;
        }
      }
      printf("%d assigned Goalie\n", minv);
      return minv;
    } // chooseBestBot

    void execute(const Param& tParam)
    {
      /*
            if (state->homePos[botID].x < -HALF_FIELD_MAXX || state->homePos[botID].x > -HALF_FIELD_MAXX + 5 * BOT_RADIUS)
      			{
      				sID = SkillSet::GoToPoint;
              sParam.GoToPointP.finalslope  = PI/2;
              sParam.GoToPointP.x           = -(HALF_FIELD_MAXX)  + 2.5 * BOT_RADIUS;
              sParam.GoToPointP.y           = (OUR_GOAL_MAXY      + OUR_GOAL_MINY)/2;
      */
//				if(!isGoalKeeperInPosition())
//				{
//					//Bot elsewhere in field. Bring the bot to the Goalkeeper position.
//					//Util::Logger::toStdOut("Bot going to goalkeeper positon.");
//					sID = SkillSet::GoToPoint;
//					sParam.GoToPointP.align = false;
//					sParam.GoToPointP.finalslope = PI/2;
//					sParam.GoToPointP.x=-(HALF_FIELD_MAXX)+DBOX_WIDTH/4;
//					sParam.GoToPointP.y=(OUR_GOAL_MAXY+OUR_GOAL_MINY)/2;
//					skillSet->executeSkill(sID, sParam);
//				}
//				else
      float dist = Vector2D<int>::dist(state->ballPos, state->homePos[botID]);
      float angleWithBall = normalizeAngle(state->homeAngle[botID] - Vector2D<int>::angle(state->ballPos, state->homePos[botID]));
      if(dist < BOT_BALL_THRESH+10 && fabs(angleWithBall) < DRIBBLER_BALL_ANGLE_RANGE)
      {
        //  printf(">>>>>>>>>>>>>>>>>>>>>>>here<<<<<<<<<<<<<<<<<\n");
        int distfromgoal1 = Vector2D<int>::dist(state->homePos[(botID + 1) % 3], state->homePos[botID]);
        int distfromgoal2 = Vector2D<int>::dist(state->homePos[(botID + 2) % 3], state->homePos[botID]);
        int botfromgoal = (distfromgoal1 < distfromgoal2) ? ((botID + 1) % 3) : ((botID + 2) % 3);
//        printf(">>>>>>>>>>>>>>>>>>>>>>>here  %d\n",botfromgoal);
        sID = SkillSet::KickToPoint;
        sParam.KickToPointP.x = state->homePos[botfromgoal].x;
        sParam.KickToPointP.y = state->homePos[botfromgoal].y;
        sParam.KickToPointP.power = 7;
        skillSet->executeSkill(sID, sParam);
      }
      else
      {
//        printf("Ball:(%d, %d)\n", state->ballPos.x, state->ballPos.y);
        //Bot in Goalkeeper position. Show goalkeeping skills.
        state1 = 1 ;
        //Util::Logger::toStdOut("Bot showing goalkeeping skills.");
        //printf("Ball x:%d y:%d v_x:%f v_y:%f\n", state->ballPos.x, state->ballPos.y, state->ballVel.x, state->ballVel.y);
        sID = SkillSet::GoToPoint;
        sParam.GoToPointP.x = (OUR_GOAL_X) + ForwardX(DBOX_WIDTH) ;
//        sParam.GoToPointP.x = OUR_GOAL_X + ForwardX(DBOX_WIDTH) ;
        sParam.GoToPointP.y = getBotDestPointY();
        sParam.GoToPointP.finalslope = atan2(-state->homePos[botID].y + state->ballPos.y, -state->homePos[botID].x + state->ballPos.x);
        //printf("finalslope = %f\n", atan2(-state->homePos[botID].y + state->ballPos.y, -state->homePos[botID].x + state->ballPos.x));
        sParam.GoToPointP.align = true;
        //sParam.GoalKeepingP.finalslope = PI/2;
        skillSet->executeSkill(sID, sParam);
      }
      tState = COMPLETED;

    }

    bool isGoalKeeperInPosition()
    {
      //Util::Logger::toStdOut("Half_field_max : %d, Dbox_width : %d\n",HALF_FIELD_MAXX,DBOX_WIDTH);
      if((state->homePos[botID].x > -HALF_FIELD_MAXX) &&
          (state->homePos[botID].x <= -HALF_FIELD_MAXX + DBOX_WIDTH) &&
          (state->homePos[botID].y >= OUR_GOAL_MINY) &&
          (state->homePos[botID].y <= OUR_GOAL_MAXY))
        return true;
      else
        return false;

    }

    int getBotDestPointY()
    {
      Vector2D<int> ballFinalpos, botDestination, point;
//      ballFinalpos.x = state->ballPos.x + state->ballVel.x;
//      ballFinalpos.y = state->ballPos.y + state->ballVel.y;
//      botDestination.x = -(HALF_FIELD_MAXX) + DBOX_WIDTH ;
//      /* Workaround for ball velocity 0*/
//      if(fabs(ballFinalpos.y - state->ballPos.y) < 5 || fabs(ballFinalpos.x - state->ballPos.x) < 5)
//      {
//        point.y = state->ballPos.y;
//      }
//      else
//      {
//        botDestination.y = (ballFinalpos.y - state->ballPos.y) / (ballFinalpos.x - state->ballPos.x) * (botDestination.x - ballFinalpos.x) + ballFinalpos.y;
//        point.y = botDestination.y;
//
//      }
      point.y = state->ballPos.y + 0.6 * state->ballVel.y;
      /* Set Limits on y to not exceed DBOX Y Limits*/
      if(point.y < OUR_GOAL_MINY)
        point.y = OUR_GOAL_MINY + BOT_RADIUS;
      else if(point.y > OUR_GOAL_MAXY)
        point.y = OUR_GOAL_MAXY - BOT_RADIUS;

      return point.y;
    }
  } ;// class TGoalKeepingOurside
} // namespace Strategy

#endif // TGOALKEEPINGOUR_HPP
