#include <ctime>

#include "PhysxEngineMain.h"
#include "World.h"
#include "RBCommDef.h"
#include "SharedMemory.h"
#include "EntityInfo.h"

using namespace Util;
using namespace HAL;
using namespace Simulator;
using namespace Strategy;

namespace PhysxEngine
{
  PhysxEngineMain::PhysxEngineMain(PosInfo *posInfo)
  {
    ASSERT((posInfo != NULL), "posInfo must not be NULL");
    
    this->posInfo     = posInfo;
    world             = new World(this->posInfo);
    shmemBlue         = new SharedMemory(SHM_BLUE_ALIAS, sizeof(SimPacket));
    shmemYellow       = new SharedMemory(SHM_YELLOW_ALIAS, sizeof(SimPacket));
    blueTeamCommand   = new SimPacket();
    yellowTeamCommand = new SimPacket();
  }

  void PhysxEngineMain::updateWorld()
  {
      delete world;
      world = new World(this->posInfo);
  }

  void PhysxEngineMain::update(int cycleNo)
  {
    shmemBlue->read(blueTeamCommand, sizeof(SimPacket));
    shmemYellow->read(yellowTeamCommand, sizeof(SimPacket));

    for (int i=0; i<BlueTeam::SIZE; ++i)
    {
      world->blueComm[i] = blueTeamCommand->bot[i];
    }
    
    for (int i=0; i<YellowTeam::SIZE; ++i)
    {
      world->yellowComm[i] = yellowTeamCommand->bot[i];
    }
    world->update();
  }

  PhysxEngineMain::~PhysxEngineMain()
  {
    delete world;
    world = NULL;

    delete shmemBlue;
    shmemBlue = NULL;

    delete shmemYellow;
    shmemYellow = NULL;

    delete blueTeamCommand;
    blueTeamCommand = NULL;

    delete yellowTeamCommand;
    yellowTeamCommand = NULL;
  }
} // namespace PhysxEngine
