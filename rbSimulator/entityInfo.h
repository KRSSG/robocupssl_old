#ifndef ENTITY_INFO_H
#define ENTITY_INFO_H

#include "config.h"
#include "Box2D/Box2D.h"

namespace PhysxEngine
{
  typedef struct PosInfo
  {
  public:
    PosInfo();

    b2Vec2 bluePos[Simulator::BlueTeam::SIZE];
    float  blueAngle[Simulator::BlueTeam::SIZE];

    b2Vec2 yellowPos[Simulator::YellowTeam::SIZE];
    float  yellowAngle[Simulator::YellowTeam::SIZE];
    
    b2Vec2 ballPos;

    // Checks if the position of any pair of entities (bot or ball) overlap
    bool checkOverlap() const;

    // Checks if all the entities are within the bounds of the field
    bool checkBounds() const;
  } PosInfo;

  class BotInfo
  {
  public:
    BotInfo();

    BotInfo(float maxLinAcceleration, 
            float maxAngAcceleration, 
            float linVelAcc,
            float angVelAcc,
            float catchBallAcc,
            float dribbleBallAcc);

    // Bot physical parameters
    float maxLinAcceleration;
    float maxAngAcceleration;

    // Omni drive parameters
    float linVelAcc;                  // must lie in [0..1]
    float angVelAcc;                  // must lie in [0..1]

    // Dribbler parameters
    float catchBallAcc;               // must lie in [0..1]
    float dribbleBallAcc;             // must lie in [0..1]
  };

  class BotActuator
  {
  private:
    static const uint8_t BALL_TOUCHED_DRIBB        = (1<<1);
    static const uint8_t BALL_IN_DRIBB_ZONE_OF_INF = (1<<2);
        
    static const uint8_t KICK_COMM_ISSUED          = (1<<4);
    static const uint8_t KICK_COMM_EXECUTED        = (1<<5);

    // Bit vector of the bit masks defined above
    uint8_t state;

    float kickPowerRemaining;
    float kickPowerRequested;         // Lies in [0..1]

  public:
    BotActuator(Simulator::TeamColor teamColor, 
                int                  botId, 
                float                kickPowerRemaining = 0.0f);

    Simulator::TeamColor teamColor;
    int                  botId;
    
    inline void setBallInDribbZoneOfInf()
    {
      state |= BALL_IN_DRIBB_ZONE_OF_INF;
    }

    inline void clearBallInDribbZoneOfInf()
    {
      state &= ~BALL_IN_DRIBB_ZONE_OF_INF;
    }

    inline void setBallTouchedDribb()
    {
      state |= BALL_TOUCHED_DRIBB;
    }

    inline void clearBallTouchedDribb()
    {
      state &= ~BALL_TOUCHED_DRIBB;
    }

    inline bool canDribbleBall() const
    {
      return ((state & (BALL_TOUCHED_DRIBB | BALL_IN_DRIBB_ZONE_OF_INF)) != 0);
    }

    inline void chargeKicker(float time)
    {
      kickPowerRemaining = MIN(1.0f, kickPowerRemaining + time/KICKER_RECHARGE_TIME);
    }

    inline float getKickPowerRemaining() const
    {
      return kickPowerRemaining;
    }

    inline void kick(float power)
    {
      float p = MIN(power, kickPowerRemaining);
      kickPowerRemaining -= p;
    }
  }; // class BotActuator
} // namespace PhysxEngine

#endif // ENTITY_INFO_H
