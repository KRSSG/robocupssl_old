#ifndef WORLD_H
#define WORLD_H

#include "Box2D/Box2D.h"
#include "RBCommDef.h"

// Forward Declarations
namespace PhysxEngine
{
  class  BotInfo;
  class  BotActuator;
  struct PosInfo;
}

namespace PhysxEngine
{
  class World sealed : public b2ContactListener, public b2RayCastCallback
  {
  private:
    b2World*       b2world;
    b2Body*        arenaBody;

    b2Body*        blueBody[Simulator::BlueTeam::SIZE];
    BotActuator*   blueActuator[Simulator::BlueTeam::SIZE];
    const BotInfo* blueInfo[Simulator::BlueTeam::SIZE];
    
    b2Body*        yellowBody[Simulator::YellowTeam::SIZE];
    BotActuator*   yellowActuator[Simulator::YellowTeam::SIZE];
    const BotInfo* yellowInfo[Simulator::YellowTeam::SIZE];

    b2Body*        ballBody;
    
    void createArena();
    
    void createBot(const BotInfo* botInfo, 
                   bool           ourTeam, 
                   int            botId, 
                   const b2Vec2&  pos,
                   float          pAng);
    
    void createBall(const b2Vec2& pos);
    
    void getPIOutputs(Simulator::TeamColor teamColor,
                      int                  botId, 
                      float                xErr,
                      float                yErr,
                      float                rErr,
                      b2Vec2&              force,
                      float&               torque) const;

    //----- CallBackMembers -----//
    b2Fixture* fixture;
    b2Vec2     point;
    b2Vec2     normal;
    
    float ReportFixture(b2Fixture*    fixture, 
                        const b2Vec2& point, 
                        const b2Vec2& normal, 
                        float32       fraction);
    
    void  BeginContact(b2Contact* contact);
    
    void  EndContact(b2Contact* contact);
    
    void  PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

  public:
    World(PosInfo* posInfo);
    ~World();

    void update(void);

    PosInfo*        posInfo;
    HAL::BotCommand blueComm[Simulator::BlueTeam::SIZE];
    HAL::BotCommand yellowComm[Simulator::YellowTeam::SIZE];
  };
} // namespace PhysxEngine

#endif // WORLD_H
