#ifndef TKICKTOGOAL_HPP
#define TKICKTOGOAL_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
  class TKickToGoal : public Tactic
  {
  public:
    TKickToGoal(const BeliefState* state, int botID) :
      Tactic(Tactic::Stop, state, botID)
    { 
      iState = GOTOBALL;
      goal = Vector2D<int>(OPP_GOAL_X, 0);
      dribblePoint = Vector2D<int>(0,0);
    } // TTStop
    enum InternalState
    {
      GOTOBALL,
      FINDPOINT,
      DRIBBLING,
      TURNING,
      KICKING
    } iState;
    ~TKickToGoal()
    { } // ~TTStop
    
    inline bool isActiveTactic(void) const
    {
      return true;
    }

    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param *tParam) const
    {
      int minv = *(freeBots.begin());
      int mindis = 10000;
      for (std::list<int>::const_iterator it = freeBots.begin(); it != freeBots.end(); ++it)
      {
        // TODO make the bot choosing process more sophisticated, the logic below returns the 1st available bot
        float dis_from_ball = (state->homePos[*it] - state->ballPos).absSq();
        if(dis_from_ball < mindis)
        {
          dis_from_ball = mindis;
          minv = *it;
        }
      }
      return minv;
    } // chooseBestBot

    void execute(const Param& tParam)
    {
      float dist=0, finalSlope=0, turnAngleLeft=0, angleWithBall=0;
      dist = Vector2D<int>::dist(state->ballPos, state->homePos[botID]);
      finalSlope = Vector2D<int>::angle(goal, state->homePos[botID]);
      turnAngleLeft = normalizeAngle(finalSlope - state->homeAngle[botID]); // Angle left to turn
      angleWithBall = normalizeAngle(state->homeAngle[botID] - Vector2D<int>::angle(state->ballPos, state->homePos[botID]));
//      switch(iState)
//      {
//        case GOTOBALL:
//            if(!(dist > BOT_BALL_THRESH || fabs(angleWithBall) > DRIBBLER_BALL_ANGLE_RANGE))
//            {
//              iState=TURNING;///////////////////////////
//              printf("state changed gotoball to turning\n");
//              break;
//            }  
//            sID = SkillSet::GoToBall;
//            printf("going to ball %d, %f, %f\n", BOT_BALL_THRESH, dist, angleWithBall);
//            skillSet->executeSkill(sID, sParam);
//            break;
//        case FINDPOINT:
////            int destRadius = (int)Vector2D<int>::dist(state->homePos[botID], goal)/2;
//            dribblePoint.x = (10*state->homePos[botID].x+goal.x)/11;
//            dribblePoint.y = (10*state->homePos[botID].y+goal.y)/11;
//            iState = DRIBBLING;
//            break;
//        case DRIBBLING:
//            if(dist > BOT_BALL_THRESH*2 /*|| fabs(angleWithBall) > DRIBBLER_BALL_ANGLE_RANGE*/)
//            {
//              iState = GOTOBALL;
//              break;
//            }
//            if(Vector2D<int>::dist(dribblePoint, state->homePos[botID])< BOT_POINT_THRESH)
//            {
//              iState = TURNING;
//              break;
//            }
//            printf("dribbling..\n");
//            sID = SkillSet::DribbleToPoint;
//            sParam.DribbleToPointP.x = dribblePoint.x;
//            sParam.DribbleToPointP.y = dribblePoint.y;
//            sParam.DribbleToPointP.finalslope = Vector2D<int>::angle(goal, dribblePoint);
//            skillSet->executeSkill(sID, sParam);
//            break;
//        case TURNING:
//            if(!(fabs(turnAngleLeft) > SATISFIABLE_THETA/2))
//            {
//              iState = KICKING;
//              printf("state changed turning to kicking\n");
//              break;
//            }
//            printf("turning to balll %f %f\n", turnAngleLeft, angleWithBall);
//            sID = SkillSet::TurnToPoint;
//            sParam.TurnToPointP.x = goal.x;
//            sParam.TurnToPointP.y = goal.y;
//#ifdef SSL_COMM
//        sParam.TurnToPointP.max_omega = MAX_BOT_OMEGA / 5;
//#else
//        sParam.TurnToPointP.max_omega = MAX_BOT_OMEGA*3;
//#endif
//            skillSet->executeSkill(sID, sParam);
//            break;
//        case KICKING:
//            printf("should kick now %f %f %f\n", turnAngleLeft, finalSlope, angleWithBall);
//            sID = SkillSet::Kick;
//            sParam.KickP.power = 7;
//            skillSet->executeSkill(sID, sParam);
//            if(dist > BOT_BALL_THRESH || fabs(angleWithBall) > DRIBBLER_BALL_ANGLE_RANGE)
//            {
//              iState = GOTOBALL;
//              printf("state changed kicking to gotoball\n");
//              break;
//            }
//            break;
//      } 
      if((dist > BOT_BALL_THRESH*1.5 || fabs(angleWithBall) > DRIBBLER_BALL_ANGLE_RANGE))
      {
        
        sID = SkillSet::GoToBall;
//        printf("going to ball %d, %f, %f\n", BOT_BALL_THRESH, dist, angleWithBall);
        skillSet->executeSkill(sID, sParam);
        return;
      }
      if((fabs(turnAngleLeft) > SATISFIABLE_THETA/2))
      {
//        printf("turning to balll %f %f\n", turnAngleLeft, angleWithBall);
        sID = SkillSet::TurnToPoint;
        sParam.TurnToPointP.x = goal.x;
        sParam.TurnToPointP.y = goal.y;
  #ifdef SSL_COMM
    sParam.TurnToPointP.max_omega = MAX_BOT_OMEGA / 5;
  #else
    sParam.TurnToPointP.max_omega = MAX_BOT_OMEGA*5;
  #endif
        skillSet->executeSkill(sID, sParam);
        return;
      }
      if((dist > BOT_BALL_THRESH || fabs(angleWithBall) > DRIBBLER_BALL_ANGLE_RANGE))
      {
        
        sID = SkillSet::GoToBall;
//        printf("going to ball %d, %f, %f\n", BOT_BALL_THRESH, dist, angleWithBall);
        skillSet->executeSkill(sID, sParam);
        return;
      }
//      printf("should kick now %f %f %f\n", turnAngleLeft, finalSlope, angleWithBall);
      sID = SkillSet::Kick;
      sParam.KickP.power = 7;
      skillSet->executeSkill(sID, sParam);
      
//      if(fabs(turnAngleLeft) > SATISFIABLE_THETA/2)
//      {

//        return;
//      }
      
      if (state->homePos[botID].absSq() < BOT_BALL_THRESH * BOT_BALL_THRESH)
      {
        tState = COMPLETED;
      }
    }
  private:
    Vector2D<int> goal;
    Vector2D<int> dribblePoint;
    
  }; // class TTStop
} // namespace Strategy

#endif // TTSTOP_HPP
