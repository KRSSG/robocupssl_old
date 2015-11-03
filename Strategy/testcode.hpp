#include "mainheaders.hpp"
#include "thread.h"
using namespace std;
using namespace Strategy;
int kbhit(void);
class Tester : public Util::Thread
{
public:
  bool &running;
  BeliefState &state;
  
  void PlayFootball(BeliefState &state)
  {
    int distfromgoal1 = Vector2D<int>::dist(state.ballPos, state.homePos[1]);
    int distfromgoal2 = Vector2D<int>::dist(state.ballPos, state.homePos[2]);
    int botToUse = (distfromgoal1 < distfromgoal2) ?1:2;
    TPosition tp(&state,botToUse);
    Tactic::Param paramposition;
    paramposition.PositionP.x=-HALF_FIELD_MAXX/2;
    paramposition.PositionP.y=0;
    paramposition.PositionP.finalSlope=normalizeAngle(Vector2D<int>::angle(state.homePos[0],state.homePos[botToUse]));
    paramposition.PositionP.finalVelocity=0;
    
    TSteal tpSteal(&state,botToUse);
    Tactic::Param paramsteal;
    
    TGoalKeepingOurSide tGoal(&state,0);
    Tactic::Param paramGoal;
    
    TKickToGoal tpKicktoGoal(&state, botToUse);
    Tactic::Param paramKick;
    
    TDefendLine tpDefendLine(&state, (botToUse==1)?2:1);
    Tactic::Param paramDefend;
    Tactic::Param paramDefend2;
    paramDefend.DefendLineP.x1=OUR_GOAL_X/2;
    paramDefend.DefendLineP.y1=1000;
    paramDefend.DefendLineP.x2=OUR_GOAL_X/2;
    paramDefend.DefendLineP.y2=-1000;
    paramDefend2.DefendLineP.x1=0;
    paramDefend2.DefendLineP.y1=1000;
    paramDefend2.DefendLineP.x2=0;
    paramDefend2.DefendLineP.y2=-1000;
    
    TMarkBot tpmark(&state,(botToUse==1)?2:1);
    Tactic::Param markparam;
    markparam.MarkBotP.awayBotID=state.oppBotNearestToBall;
    
    tGoal.execute(paramGoal); // Goal Keeper
    
    if(state.pr_ballOurSide && !state.pr_ourBall)
    {
        tpSteal.execute(paramsteal);
        tpDefendLine.execute(paramDefend);        
    }
    else if(state.pr_ballOurSide && state.pr_ourBall)
    {
        float angleWithBall = normalizeAngle(state.homeAngle[0] - Vector2D<int>::angle(state.ballPos, state.homePos[0]));
        float goaliedistfromball=Vector2D<int>::dist(state.ballPos,state.homePos[0]);
        if(state.ourBotNearestToBall==0 && fabs(angleWithBall) < DRIBBLER_BALL_ANGLE_RANGE && goaliedistfromball<DRIBBLER_BALL_THRESH)
          tp.execute(paramposition);
        tpDefendLine.execute(paramDefend2);
        tpKicktoGoal.execute(paramKick);
    }
    else if(!state.pr_ballOurSide && !state.pr_ourBall)
    {
        tpSteal.execute(paramsteal);
        tpmark.execute(markparam);
    }
    else if(!state.pr_ballOurSide && state.pr_ourBall)
    {
        tpKicktoGoal.execute(paramKick);
        tpDefendLine.execute(paramDefend2);
    }
    else 
    {
        tpSteal.execute(paramsteal);
        tpDefendLine.execute(paramDefend); 
    }
  }
  
  Tester(bool &running_, BeliefState &state_):running(running_),state(state_) {}
  void run()
  {
    Util::CS loggerCS;
    Util::Logger logger("timelog.log", Util::Logger::Write, loggerCS);


    Kalman      kFilter;
    VisionThread vThread(kFilter);
    vThread.start();

    int mycharger = 2;

    TKickToGoal tpKick(&state, 2);
    Tactic::Param paramKick;
    
    TDefendLine tpDefend(&state, 1);
    Tactic::Param paramDefend;
    paramDefend.DefendLineP.x1=OUR_GOAL_X/2;
    paramDefend.DefendLineP.y1=1000;
    paramDefend.DefendLineP.x2=OUR_GOAL_X/2;;
    paramDefend.DefendLineP.y2=-1000;
    
//    TVelocity tpD(&state,2);
//    Tactic::Param paramD;
//	paramD.VelocityP.v_y = 50;
//  paramD.VelocityP.v_x = 0;
//  paramD.VelocityP.v_t = 0;
  
    TGoalKeepingOurSide tGoal(&state,0);
    Tactic::Param paramGoal;
    
    TPass tpass(&state,0);
    Tactic::Param paramPass;
    paramPass.PassP.x=0;
    paramPass.PassP.y=0;
    paramPass.PassP.power=5;
    

    TStop tS0(&state,0);
    TStop tS1(&state,1);
    TStop tS2(&state,2);
    Tactic::Param paramStop;
    
    bool isRunning = true;
    
    while(running)
    {
      kFilter.update(state);
      if(kbhit())
      {
        getchar();
        isRunning = !isRunning;
      }
      if(isRunning)
      {
//        for(int i=0;i<3;i++)
//        {
//          printf("Home Bot ID: %d ",i);
//          printf("Bot Position: %d %d ",state.homePos[i].x,state.homePos[i].y);
//          printf("Bot Angle: %lf\n",state.homeAngle[i]);
//        }
//        for(int i=0;i<3;i++)
//        {
//          printf("Away Bot ID: %d ",i);
//          printf("Bot Position: %d %d ",state.awayPos[i].x,state.awayPos[i].y);
//          printf("Bot Angle: %lf\n",state.awayAngle[i]);
//        }  
//        printf("Ball Position: %d %d ",state.ballPos.x,state.ballPos.y);
      // printf("ballpos %d,%d\n",state.ballPos.x,state.ballPos.y);
      //tpKick.execute(paramD);
//        tGoal.execute(paramGoal);
//        tpKick.execute(paramKick);
//        tpDefend.execute(paramDefend);
      //tGoal.execute(paramGoal);
//        tpGoal.execute(paramGoal);
//        tpass.execute(paramPass);
        PlayFootball(state);
//        printf("ON!\n");
      }      
      else
      {
//        printf("OFF!\n");
        tS0.execute(paramStop);
        tS1.execute(paramStop);
        tS2.execute(paramStop);
      }
      usleep(16000);  // Adding sleep to this thread of execution to prevent CPU hogging

    }
    vThread.stop();
    Util::Logger::toStdOut("Exiting process");
    return;

  }
  
};
