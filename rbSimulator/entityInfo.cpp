#include "EntityInfo.h"

using namespace Simulator;

namespace PhysxEngine
{
  PosInfo::PosInfo()
  {
    if (BlueTeam::SIZE > 0)
    {
      bluePos[0].Set(-FIELD_W/2 + BOT_RADIUS*2, 0.0f);
      blueAngle[0] = 0.0f;
    }
    
    if (BlueTeam::SIZE > 1)
    {
      bluePos[1].Set(-FIELD_W/6, FIELD_H/4);
      blueAngle[1] = 0.0f;
    }

    if (BlueTeam::SIZE > 2)
    {
      bluePos[2].Set(-FIELD_W/6, -FIELD_H/4);
      blueAngle[2] = 0.0f;
    }

    if (BlueTeam::SIZE > 3)
    {
      bluePos[3].Set(-FIELD_W/3, FIELD_H/6);
      blueAngle[3] = 0.0f;
    }

    if (BlueTeam::SIZE > 4)
    {
      bluePos[4].Set(-FIELD_W/3, -FIELD_H/6);
      blueAngle[4] = 0.0f;
    }
    
    if (YellowTeam::SIZE > 0)
    {
      yellowPos[0].Set(FIELD_W/2 - BOT_RADIUS*2, 0.0f);
      yellowAngle[0] = b2_pi;
    }

    if (YellowTeam::SIZE > 1)
    {
      yellowPos[1].Set(FIELD_W/6, FIELD_H/4);
      yellowAngle[1] = b2_pi;
    }
    
    if (YellowTeam::SIZE > 2)
    {
      yellowPos[2].Set(FIELD_W/6, -FIELD_H/4);
      yellowAngle[2] = b2_pi;
    }
    
    if (YellowTeam::SIZE > 3)
    {
      yellowPos[3].Set(FIELD_W/3, FIELD_H/6);
      yellowAngle[3] = b2_pi;
    }
    
    if (YellowTeam::SIZE > 4)
    {
      yellowPos[4].Set(FIELD_W/3, -FIELD_H/6);
      yellowAngle[4] = b2_pi;
    }

    ballPos.Set(0.0f, 0.0f);
  }

  bool PosInfo::checkOverlap() const
  {
    b2Vec2 distVect;
    float  dist2;

    for (int i=0; i<BlueTeam::SIZE; ++i)
    {
      distVect = bluePos[i] - ballPos;
      dist2 = distVect.LengthSquared();
      if((dist2 > (BOT_RADIUS + BALL_RADIUS)*(BOT_RADIUS + BALL_RADIUS))){}
      else{return false;}
    }

    for (int i=0; i<YellowTeam::SIZE; ++i)
    {
      distVect = yellowPos[i] - ballPos;
      dist2 = distVect.LengthSquared();
      if((dist2 > (BOT_RADIUS + BALL_RADIUS)*(BOT_RADIUS + BALL_RADIUS))){}
      else{return false;}
    }

    for (int i=0; i<BlueTeam::SIZE; ++i)
    {
      for (int j=0; j<YellowTeam::SIZE; j++)
      {
        distVect = bluePos[i] - yellowPos[j];
        dist2 = distVect.LengthSquared();
        if((dist2 > (2*BOT_RADIUS)*(2*BOT_RADIUS))){}
        else{return false;}
      }
    }
    return true;
  }

  bool PosInfo::checkBounds() const
  {
    if(((ballPos.x > -FIELD_W/2 + BALL_RADIUS && ballPos.x < FIELD_W/2 - BALL_RADIUS &&
         ballPos.y >= -FIELD_H/2 + BALL_RADIUS && ballPos.y < FIELD_H/2 - BALL_RADIUS) ||
        (ballPos.x > -FIELD_W/2 - GOAL_W + BALL_RADIUS && ballPos.x < FIELD_W/2 + GOAL_W - BALL_RADIUS &&
         ballPos.y >= -GOAL_H/2 + BALL_RADIUS && ballPos.y < GOAL_H/2 - BALL_RADIUS)))
    {
    }
    else
    {
        return false;
    }

    for (int i=0; i<BlueTeam::SIZE; ++i)
    {
      if(((bluePos[i].x > -FIELD_W/2 + BOT_RADIUS && bluePos[i].x < FIELD_W/2 - BOT_RADIUS &&
           bluePos[i].y >= -FIELD_H/2 + BOT_RADIUS && bluePos[i].y < FIELD_H/2 - BOT_RADIUS) ||
          (bluePos[i].x > -FIELD_W/2 - GOAL_W + BOT_RADIUS && bluePos[i].x < FIELD_W/2 + GOAL_W - BOT_RADIUS &&
           bluePos[i].y >= -GOAL_H/2 + BOT_RADIUS && bluePos[i].y < GOAL_H/2 - BOT_RADIUS)))
      {
      }
      else
      {
        return false;
      }
    }

    for (int i=0; i<YellowTeam::SIZE; ++i)
    {
      if(((yellowPos[i].x > -FIELD_W/2 + BOT_RADIUS && yellowPos[i].x < FIELD_W/2 - BOT_RADIUS &&
           yellowPos[i].y >= -FIELD_H/2 + BOT_RADIUS && yellowPos[i].y < FIELD_H/2 - BOT_RADIUS) ||
          (yellowPos[i].x > -FIELD_W/2 - GOAL_W + BOT_RADIUS && yellowPos[i].x < FIELD_W/2 + GOAL_W - BOT_RADIUS &&
           yellowPos[i].y >= -GOAL_H/2 + BOT_RADIUS && yellowPos[i].y < GOAL_H/2 - BOT_RADIUS)))
      {
      }
      else
      {
        return false;
      }
    }
    return true;
  }

  BotInfo::BotInfo() :
    maxLinAcceleration(1.0f),
    maxAngAcceleration(5.0f),
    linVelAcc(1.0f),
    angVelAcc(1.0f),
    catchBallAcc(1.0f),
    dribbleBallAcc(1.0f)
  {}

  BotInfo::BotInfo(float maxLinAcceleration_ = 1.0f, 
                   float maxAngAcceleration_ = 5.0f,
                   float linVelAcc_          = 1.0f,
                   float angVelAcc_          = 1.0f,
                   float catchBallAcc_       = 1.0f,
                   float dribbleBallAcc_     = 1.0f) :
    maxLinAcceleration(maxLinAcceleration_),
    maxAngAcceleration(maxAngAcceleration_),
    linVelAcc(linVelAcc_),
    angVelAcc(angVelAcc_),
    catchBallAcc(catchBallAcc_),
    dribbleBallAcc(dribbleBallAcc_)
  {
    ASSERT((maxLinAcceleration >= 0.0f && maxLinAcceleration <= 2.0f), "Max Linear Acceleration out of bounds");
    ASSERT((maxAngAcceleration >= 0.0f && maxLinAcceleration <= 10.0f), "Max Angular Accelaration out of bounds");
    ASSERT((linVelAcc >= 0.0f && linVelAcc <= 1.0f), "Illegal value for linear velocity accuracy");
    ASSERT((angVelAcc >= 0.0f && angVelAcc <= 1.0f), "Illegal value for angular velocity accuracy");
    ASSERT((catchBallAcc >= 0.0f && catchBallAcc <= 1.0f), "Illegal value for catch ball accuracy");
    ASSERT((dribbleBallAcc >= 0.0f && dribbleBallAcc <= 1.0f), "Illegal value for dribble ball accuracy");
  }

  BotActuator::BotActuator(TeamColor teamColor, 
                           int       botId, 
                           float     kickPowerRemaining) : 
    teamColor(teamColor),
    botId(botId),
    kickPowerRemaining(kickPowerRemaining)
  {
    ASSERT((teamColor == TeamColor::BLUE || teamColor == TeamColor::YELLOW), "Wrong Team Color");
    ASSERT(((teamColor == TeamColor::BLUE && botId >= 0 && botId < BlueTeam::SIZE) || 
           (teamColor == TeamColor::YELLOW && botId >= 0 && botId < YellowTeam::SIZE)), "Wrong bot ID");
    ASSERT((kickPowerRemaining >= 0.0f && kickPowerRemaining <= 1.0f), "kickPowerRemaining must lie in [0..1]");

    state = 0;
  }
} // namespace PhysxEngine
