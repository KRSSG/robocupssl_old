#include "skillSet.h"
#include "pathPlanners.h"
#include "beliefState.h"
#include "fieldConfig.h"
#include <cstdio>
namespace Strategy
{
  void SkillSet::goToPoint(const SParam &param)
  {
    Vector2D<int> dpoint;
    dpoint.x = param.GoToPointP.x;
    dpoint.y = param.GoToPointP.y;
//    printf("point= %d,%d\n",dpoint.x,dpoint.y);
    obstacle obs[HomeTeam::SIZE + AwayTeam::SIZE];
    for(int i = 0; i < HomeTeam::SIZE; ++i)
    {
      obs[i].x = state->homePos[i].x;
      obs[i].y = state->homePos[i].y;
      obs[i].radius = 3 * BOT_RADIUS;
    }

    for(int i = HomeTeam::SIZE; i < HomeTeam::SIZE + AwayTeam::SIZE; ++i)
    {
      obs[i].x = state->awayPos[i - HomeTeam::SIZE].x;
      obs[i].y = state->awayPos[i - HomeTeam::SIZE].y;
      obs[i].radius = 3 * BOT_RADIUS;
    }
    Vector2D<int> point, nextWP, nextNWP;
    pathPlanner->plan(state->homePos[botID],
                      dpoint,
                      &nextWP,
                      &nextNWP,
                      obs,
                      HomeTeam::SIZE + AwayTeam::SIZE,
                      botID,
                      true);

    if(nextWP.valid())
    {
      comm.addCircle(nextWP.x, nextWP.y, 50);
      comm.addLine(state->homePos[botID].x, state->homePos[botID].y, nextWP.x, nextWP.y);
    }
    if(nextNWP.valid())
    {
      comm.addCircle(nextNWP.x, nextNWP.y, 50);
      comm.addLine(nextWP.x, nextWP.y, nextNWP.x, nextNWP.y);
    }

    float motionAngle = Vector2D<int>::angle(nextWP, state->homePos[botID]);

    float finalSlope;   // final slope the current bot motion should aim for!
    if(nextNWP.valid())
      finalSlope = Vector2D<int>::angle(nextNWP, nextWP);
    else
      finalSlope = param.GoToPointP.finalslope;

    float turnAngleLeft = normalizeAngle(finalSlope - state->homeAngle[botID]); // Angle left to turn
    //printf("Target x: %d, y:%d, a:%f || Left x:%d, y:%d, a:%f\n", nextWP.x, nextWP.y, finalSlope, 
           // nextWP.x - state->homePos[botID].x, nextWP.y - state->homePos[botID].y, turnAngleLeft);
    
    float omega = turnAngleLeft * MAX_BOT_OMEGA / (2 * PI); // Speedup turn
    if(omega < MIN_BOT_OMEGA && omega > -MIN_BOT_OMEGA)
    {
      if(omega < 0) omega = -MIN_BOT_OMEGA;
      else omega = MIN_BOT_OMEGA;
    }

    float dist = Vector2D<int>::dist(nextWP, state->homePos[botID]);  // Distance of next waypoint from the bot
    float theta =  motionAngle - state->homeAngle[botID];               // Angle of dest with respect to bot's frame of reference

    float profileFactor = (dist * 2 / MAX_FIELD_DIST) * MAX_BOT_SPEED;
    if(profileFactor < MIN_BOT_SPEED)
      profileFactor = MIN_BOT_SPEED;
    else if(profileFactor > MAX_BOT_SPEED)
      profileFactor = MAX_BOT_SPEED;
    profileFactor = MAX_BOT_SPEED;
    if(dist < BOT_POINT_THRESH)
    {
      if(param.GoToPointP.align == true)
      {
        if((turnAngleLeft) > -DRIBBLER_BALL_ANGLE_RANGE  && (turnAngleLeft) < DRIBBLER_BALL_ANGLE_RANGE)
        {
          comm.sendCommand(botID, 0, 0, 0, 0, true);
        }
        else
          comm.sendCommand(botID, 0, 0, omega, 0, true);
      }
      else
        comm.sendCommand(botID, 0, 0, 0, 0, true);
    }
    else
    {
      comm.sendCommand(botID, profileFactor * sin(-theta), profileFactor * cos(-theta), omega, 0, false);
    }
  } // goToPoint
}
