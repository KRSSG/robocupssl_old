#include "World.h"
#include "config.h"
#include "EntityInfo.h"

using namespace HAL;
using namespace Simulator;
using namespace Strategy;

namespace PhysxEngine
{
  World::World(PosInfo* posInfo)
  {
    ASSERT((posInfo != NULL), "posInfo must not be NULL");

    this->posInfo = posInfo;

    ASSERT(this->posInfo->checkOverlap(), "CHECK OVERLAP FAILED");
    ASSERT(this->posInfo->checkBounds(), "CHECK BOUNDS FAILED");

    b2world = new b2World(b2Vec2(0.0f, 0.0f));

    b2world->SetContactListener(this);

    createArena();

    for (int botID=0; botID<BlueTeam::SIZE; ++botID)
    {
      BotInfo *botInfo = new BotInfo(1.0f, 2.0f, 1.0f, 1.0f, 0.9f, 1.0f);
      blueActuator[botID] = new BotActuator(TeamColor::BLUE, botID, 0.0f);
      createBot(botInfo, true, botID, this->posInfo->bluePos[botID], this->posInfo->blueAngle[botID]);
    }

    for (int botID=0; botID<YellowTeam::SIZE; ++botID)
    {
      BotInfo *botInfo = new BotInfo(1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f);
      yellowActuator[botID] = new BotActuator(TeamColor::YELLOW, botID, 0.0f);
      createBot(botInfo, false, botID, this->posInfo->yellowPos[botID], this->posInfo->yellowAngle[botID]);
    }
    createBall(this->posInfo->ballPos);
    this->fixture = NULL;
  }

  void World::createArena()
  {
    // TODO: Arena has no walls so field boundaries will be sensor fixtures/fixtures with collision filtering. Goals will have solid boundaries

    b2BodyDef bd;
    bd.type = b2_staticBody;

    b2FixtureDef fd;
    fd.density = 0.0f;
    fd.friction = ARENA_FRIC;
    fd.restitution = ARENA_REST;
    fd.userData = (void*)&ARENA_USER_DATA;

    b2Body *arena;
    arena = b2world->CreateBody(&bd);

    b2PolygonShape shape;
    
    shape.SetAsBox((ARENA_W/2 - FIELD_W/2)/2, (ARENA_H/2 - GOAL_H/2)/2, b2Vec2((-ARENA_W/2 - FIELD_W/2)/2, (ARENA_H/2 + GOAL_H/2)/2), 0.0f);
    fd.shape = &shape;
    arena->CreateFixture(&fd);
    
    shape.SetAsBox((ARENA_W/2 - FIELD_W/2)/2, (ARENA_H/2 - GOAL_H/2)/2, b2Vec2((-ARENA_W/2 - FIELD_W/2)/2, (-ARENA_H/2 - GOAL_H/2)/2), 0.0f);
    fd.shape = &shape;
    arena->CreateFixture(&fd);
    
    shape.SetAsBox((ARENA_W/2 - FIELD_W/2 - GOAL_W)/2, ARENA_H/2, b2Vec2((-ARENA_W/2 - FIELD_W/2 - GOAL_W)/2, 0.0f), 0.0f);
    fd.shape = &shape;
    arena->CreateFixture(&fd);
    
    shape.SetAsBox((ARENA_W/2 - FIELD_W/2)/2, (ARENA_H/2 - GOAL_H/2)/2, b2Vec2((ARENA_W/2 + FIELD_W/2)/2, (ARENA_H/2 + GOAL_H/2)/2), 0.0f);
    fd.shape = &shape;
    arena->CreateFixture(&fd);

    shape.SetAsBox((ARENA_W/2 - FIELD_W/2)/2, (ARENA_H/2 - GOAL_H/2)/2, b2Vec2((ARENA_W/2 + FIELD_W/2)/2, (-ARENA_H/2 - GOAL_H/2)/2), 0.0f);
    fd.shape = &shape;
    arena->CreateFixture(&fd);

    shape.SetAsBox((ARENA_W/2 - FIELD_W/2 - GOAL_W)/2, ARENA_H/2, b2Vec2((ARENA_W/2 + FIELD_W/2 + GOAL_W)/2, 0.0f), 0.0f);
    fd.shape = &shape;
    arena->CreateFixture(&fd);

    shape.SetAsBox(FIELD_W/2, (ARENA_H/2 - FIELD_H/2)/2, b2Vec2(0.0f, (ARENA_H/2 + FIELD_H/2)/2), 0.0f);
    fd.shape = &shape;
    arena->CreateFixture(&fd);

    shape.SetAsBox(FIELD_W/2, (ARENA_H/2 - FIELD_H/2)/2, b2Vec2(0.0f, (-ARENA_H/2 - FIELD_H/2)/2), 0.0f);
    fd.shape = &shape;
    arena->CreateFixture(&fd);
  }

  void World::createBot(const BotInfo* botInfo,
                        bool           ourTeam,
                        int            botId,
                        const b2Vec2&  pos,
                        float          pAng)
  {
    ASSERT(botInfo != NULL, "botInfo must not be NULL");
    ASSERT(((0 <= botId && botId < BlueTeam::SIZE && ourTeam) || (0 <= botId && botId < YellowTeam::SIZE && !ourTeam)),
           "botId out of bounds");

    b2FixtureDef fd;
      
    // Creating the bot body and adding it to the world
    {
      b2BodyDef bd;

      bd.type           = b2_dynamicBody;
      bd.linearDamping  = BOT_GND_FRIC;
      bd.angularDamping = BOT_GND_FRIC;
      bd.angle          = pAng;
      bd.position       = pos;
      
      if (ourTeam)
      {
        bd.userData        = blueActuator[botId];
        blueBody[botId] = b2world->CreateBody(&bd);
        blueInfo[botId] = botInfo;
      }
      else
      {
        bd.userData               = yellowActuator[botId];
        yellowBody[botId]         = b2world->CreateBody(&bd);
        yellowInfo[botId]         = botInfo;
      }
    }
   
    b2Body* botBody = (ourTeam)? blueBody[botId] : yellowBody[botId];

    // Adding the body fixture to the bot
    {
      b2Vec2         vertices[8];
      float          ang = pAng + FACE_HALF_ANG;
      b2PolygonShape shape;
      
      fd.density     = BOT_MASS/(b2_pi*BOT_RADIUS*BOT_RADIUS);
      fd.friction    = BOT_WALL_FRIC;
      fd.restitution = BOT_REST;

      /* Assuming the bot has 8 vertices, the angle subtended by each of the non-front edge 
       * at the center of the bot
       */
      const float ANG_STEP = (2*b2_pi - 2*FACE_HALF_ANG)/7;

      vertices[0].Set(BOT_RADIUS*cosf(pAng - FACE_HALF_ANG), BOT_RADIUS*sinf(pAng - FACE_HALF_ANG));
      vertices[1].Set(BOT_RADIUS*cosf(pAng + FACE_HALF_ANG), BOT_RADIUS*sinf(pAng + FACE_HALF_ANG));
      
      for (int c=2; c<8; c++)
      {
        ang += ANG_STEP;
        vertices[c].Set(BOT_RADIUS*cosf(ang), BOT_RADIUS*sinf(ang));
      }
      shape.Set(vertices, 8);

      fd.shape = &shape;
      fd.userData = (void*)&BOT_BODY_USER_DATA;
      botBody->CreateFixture(&fd);
    }

    // Adding the dribbler bar fixture to the bot's body
    {
      b2PolygonShape dribShape;
      
      fd.friction    = DRIBB_FRIC;
      fd.restitution = (1.0f - botInfo->catchBallAcc);

      dribShape.SetAsBox(DRIBB_W/2, 
                         BOT_RADIUS*sinf(FACE_HALF_ANG)*DRIBB_L, 
                         b2Vec2((BOT_RADIUS*cosf(FACE_HALF_ANG) + DRIBB_W/2)*cosf(pAng), 
                                (BOT_RADIUS*cosf(FACE_HALF_ANG) + DRIBB_W/2)*sinf(pAng)),
                         pAng);
      fd.shape = &dribShape;
      fd.userData = (void*)&DRIBB_USER_DATA;
      botBody->CreateFixture(&fd);

      b2PolygonShape sensorShape;
      sensorShape.SetAsBox(DRIBB_INF_DIST/2, 
                         BOT_RADIUS*sinf(FACE_HALF_ANG)*DRIBB_L - BALL_RADIUS, 
                         b2Vec2((BOT_RADIUS*cosf(FACE_HALF_ANG) + (DRIBB_W + DRIBB_INF_DIST)/2)*cosf(pAng), 
                                (BOT_RADIUS*cosf(FACE_HALF_ANG) + (DRIBB_W + DRIBB_INF_DIST)/2)*sinf(pAng)),
                         pAng);

      b2FixtureDef fd2;
      fd2.density  = 0.1f;
      fd2.shape    = &sensorShape;
      fd2.isSensor = true;
      fd2.userData = (void*)&SENSOR_USER_DATA;
      botBody->CreateFixture(&fd2);

    }
  }

  void World::createBall(const b2Vec2& pos)
  {
    b2BodyDef bd;
    bd.type           = b2_dynamicBody;
    bd.linearDamping  = BALL_GND_FRIC;
    bd.bullet         = true;
    bd.position       = pos;
    
    ballBody = b2world->CreateBody(&bd);

    b2FixtureDef fd;
    fd.density        = BALL_MASS/(b2_pi*BALL_RADIUS*BALL_RADIUS);
    fd.friction       = BALL_WALL_FRIC;
    fd.restitution    = BALL_REST;

    b2CircleShape circ;
    circ.m_p.Set(0.0f, 0.0f);
    circ.m_radius     = BALL_RADIUS;
    
    fd.shape          = &circ;
    fd.userData       = (void*)&BALL_USER_DATA;
    ballBody->CreateFixture(&fd);
  }

  void World::getPIOutputs(TeamColor teamColor,
                           int       botId, 
                           float     xErr, 
                           float     yErr, 
                           float     rErr, 
                           b2Vec2&   force, 
                           float&    torque) const
  {
    static float IError[2][MAX(BlueTeam::SIZE, YellowTeam::SIZE)][3];

    const float KpLinVel = 45.0f, KpAngVel = 0.19f;
    const float KiLinVel = 9.0f, KiAngVel = 0.45f;
    
    IError[teamColor][botId][0] += xErr/FPS;
    IError[teamColor][botId][1] += yErr/FPS;
    IError[teamColor][botId][2] += rErr/FPS;

    force.x = KpLinVel*xErr + KiLinVel*IError[teamColor][botId][0];
    force.y = KpLinVel*yErr  + KiLinVel*IError[teamColor][botId][1];

    torque = KpAngVel*rErr + KiAngVel*IError[teamColor][botId][2];

    // TODO: there must be a cap on the max value of force and torque
  }

  void World::update(void)
  {
    b2world->Step(1.0f/FPS, 10, 10);

    // TODO: Process the back-spins over the ball here

    for (int botID=0; botID<BlueTeam::SIZE; ++botID)
    {
      float  angle  = blueBody[botID]->GetAngle();
      b2Vec2 pos    = blueBody[botID]->GetWorldCenter();
      b2Vec2 linVel = blueBody[botID]->GetLinearVelocity();
      float  angVel = blueBody[botID]->GetAngularVelocity();

      /* Updating the bot position in the variable visible to the simulator */
      posInfo->bluePos[botID].Set(pos.x, pos.y);
      posInfo->blueAngle[botID] = angle;

      /* Charging the kicker */
      blueActuator[botID]->chargeKicker(1.0f/FPS);

      /* Processing dribbling command */
      if (blueComm[botID].dribble)
      {
        // TODO: Implement the back spin effect on the ball in a more elegant way as it would happen in reality with all the physics
        if (blueActuator[botID]->canDribbleBall())
        {
          static const float BACK_FORCE = BALL_GND_FRIC*BALL_MASS*9.8f;
          ballBody->ApplyForce(-b2Vec2(BACK_FORCE*cos(angle), BACK_FORCE*sin(angle)), ballBody->GetWorldCenter());
        }
      }

      float kickPower = blueComm[botID].kickPower;
      if (kickPower > b2_epsilon)
      {
        blueActuator[botID]->kick(kickPower);
      }
      
      b2Vec2 force;
      float torque;

      getPIOutputs(TeamColor::BLUE, 
                   botID, 
                   blueComm[botID].v_x*sinf(angle) + blueComm[botID].v_y*cosf(angle) - linVel.x, 
                   blueComm[botID].v_y*sinf(angle) - blueComm[botID].v_x*cosf(angle) - linVel.y, 
                   blueComm[botID].v_t - angVel, 
                   force, torque);

      blueBody[botID]->ApplyForce(force, pos);
      blueBody[botID]->ApplyTorque(torque);
    }

    for (int botID=0; botID<YellowTeam::SIZE; ++botID)
    {
      float  angle  = yellowBody[botID]->GetAngle();
      b2Vec2 pos    = yellowBody[botID]->GetWorldCenter();
      b2Vec2 linVel = yellowBody[botID]->GetLinearVelocity();
      float  angVel = yellowBody[botID]->GetAngularVelocity();

      // Updating the bot position in the variable visible to the simulator
      posInfo->yellowPos[botID].Set(pos.x, pos.y);
      posInfo->yellowAngle[botID] = angle;

      // Charging the kicker
      yellowActuator[botID]->chargeKicker(1.0f/FPS);

      // Processing dribbling command
      if (yellowComm[botID].dribble)
      {
        // TODO: Implement the back spin effect on the ball in a more elegant way as it would happen in reality with all the physics
        if (yellowActuator[botID]->canDribbleBall())
        {
          static const float BACK_FORCE = BALL_GND_FRIC*BALL_MASS*9.8f;
          ballBody->ApplyForce(-b2Vec2(BACK_FORCE*cos(angle), BACK_FORCE*sin(angle)), ballBody->GetWorldCenter());
        }
      }

      float kickPower = yellowComm[botID].kickPower;
      if (kickPower > b2_epsilon)
      {
        yellowActuator[botID]->kick(kickPower);
      }
      
      b2Vec2 force;
      float torque;

      getPIOutputs(TeamColor::YELLOW, 
                   botID, 
                   yellowComm[botID].v_x*sinf(angle) + yellowComm[botID].v_y*cosf(angle) - linVel.x, 
                   yellowComm[botID].v_y*sinf(angle) - yellowComm[botID].v_x*cosf(angle) - linVel.y, 
                   yellowComm[botID].v_t - angVel, 
                   force, 
                   torque);

      yellowBody[botID]->ApplyForce(force, pos);
      yellowBody[botID]->ApplyTorque(torque);
    }
    
    // Updating the ball position in the variable visible to the simulator
    b2Vec2 pos = ballBody->GetWorldCenter();
    posInfo->ballPos.Set(pos.x, pos.y);
  } // update

  void World::BeginContact(b2Contact* contact)
  {
    b2Fixture *fixA = contact->GetFixtureA();
    b2Fixture *fixB = contact->GetFixtureB();

    const char *userDataA = (char*)fixA->GetUserData();
    const char *userDataB = (char*)fixB->GetUserData();

    if (*userDataA == BALL_USER_DATA && *userDataB == SENSOR_USER_DATA)
    {
      BotActuator *act = (BotActuator*)fixB->GetBody()->GetUserData();
      act->setBallInDribbZoneOfInf();
    }
    else if (*userDataB == BALL_USER_DATA && *userDataA == SENSOR_USER_DATA)
    {
      BotActuator *act = (BotActuator*)fixA->GetBody()->GetUserData();
      act->setBallInDribbZoneOfInf();
    }
    else if (*userDataA == BALL_USER_DATA && *userDataB == DRIBB_USER_DATA)
    {
      BotActuator *act = (BotActuator*)fixB->GetBody()->GetUserData();
      act->setBallTouchedDribb();
    }
    else if (*userDataB == BALL_USER_DATA && *userDataA == DRIBB_USER_DATA)
    {
      BotActuator *act = (BotActuator*)fixA->GetBody()->GetUserData();
      act->setBallTouchedDribb();
    }
  }

  void World::EndContact(b2Contact* contact)
  {
    b2Fixture *fixA = contact->GetFixtureA();
    b2Fixture *fixB = contact->GetFixtureB();

    const char *userDataA = (char*)fixA->GetUserData();
    const char *userDataB = (char*)fixB->GetUserData();

    if (*userDataA == BALL_USER_DATA && *userDataB == SENSOR_USER_DATA)
    {
      BotActuator *act = (BotActuator*)fixB->GetBody()->GetUserData();
      act->clearBallInDribbZoneOfInf();
      act->clearBallTouchedDribb();
    }
    else if (*userDataB == BALL_USER_DATA && *userDataA == SENSOR_USER_DATA)
    {
      BotActuator *act = (BotActuator*)fixA->GetBody()->GetUserData();
      act->clearBallInDribbZoneOfInf();
      act->clearBallTouchedDribb();
    }
  }

  void World::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
  {
    NOT_USED(oldManifold);

    b2Fixture *fixA = contact->GetFixtureA();
    b2Fixture *fixB = contact->GetFixtureB();

    const char *userDataA = (char*)fixA->GetUserData();
    const char *userDataB = (char*)fixB->GetUserData();

    if (*userDataA == BALL_USER_DATA && *userDataB == DRIBB_USER_DATA)
    {
      b2Body      *botBody = fixB->GetBody();
      BotActuator *act     = (BotActuator*)botBody->GetUserData();

      // TODO: Handle opponent case too
      float power = blueComm[act->botId].kickPower;
      if (power > b2_epsilon)
      {
        float p = MIN(power, act->getKickPowerRemaining());
        ballBody->ApplyLinearImpulse(b2Vec2(MAX_KICK_SPEED*BALL_MASS*p*cosf(botBody->GetAngle()), 
                                            MAX_KICK_SPEED*BALL_MASS*p*sinf(botBody->GetAngle())),
                                     ballBody->GetWorldCenter());
        botBody->ApplyLinearImpulse(-b2Vec2(MAX_KICK_SPEED*BALL_MASS*p*cosf(botBody->GetAngle()), 
                                            MAX_KICK_SPEED*BALL_MASS*p*sinf(botBody->GetAngle())),
                                     botBody->GetWorldCenter());
      }
    }
    else if (*userDataB == BALL_USER_DATA && *userDataA == DRIBB_USER_DATA)
    {
      b2Body      *botBody = fixA->GetBody();
      BotActuator *act     = (BotActuator*)botBody->GetUserData();

      // TODO: Handle opponent case too
      float power = blueComm[act->botId].kickPower;
      if (power > b2_epsilon)
      {
        float p = MIN(power, act->getKickPowerRemaining());
        ballBody->ApplyLinearImpulse(b2Vec2(MAX_KICK_SPEED*BALL_MASS*p*cosf(botBody->GetAngle()), 
                                            MAX_KICK_SPEED*BALL_MASS*p*sinf(botBody->GetAngle())),
                                     ballBody->GetWorldCenter());
        botBody->ApplyLinearImpulse(-b2Vec2(MAX_KICK_SPEED*BALL_MASS*p*cosf(botBody->GetAngle()), 
                                            MAX_KICK_SPEED*BALL_MASS*p*sinf(botBody->GetAngle())),
                                     botBody->GetWorldCenter());
      }
    }
  }

  float32 World::ReportFixture(b2Fixture*    fixture, 
                               const b2Vec2& point, 
                               const b2Vec2& normal,
                               float32       fraction)
  {
    NOT_USED(fixture);
    NOT_USED(point);
    NOT_USED(normal);
    NOT_USED(fraction);
    return 0.0f;
  }

  World::~World()
  {
    for (int botID=0; botID<BlueTeam::SIZE; ++botID)
    {
      delete(blueInfo[botID]);
      blueInfo[botID] = NULL;
      delete(blueActuator[botID]);
      blueActuator[botID] = NULL;
    }

    for (int botID=0; botID<YellowTeam::SIZE; ++botID)
    {
      delete(yellowInfo[botID]);
      yellowInfo[botID] = NULL;
      delete(yellowActuator[botID]);
      yellowActuator[botID] = NULL;
    }

    delete(b2world);
    b2world = NULL;
  }
} // namespace PhysxEngine