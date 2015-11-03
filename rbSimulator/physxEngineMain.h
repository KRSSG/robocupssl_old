#ifndef PHYSX_ENGINE_MAIN_H
#define PHYSX_ENGINE_MAIN_H

// Forward Declarations
namespace PhysxEngine
{
  class  World;
  struct PosInfo;
}

namespace Util
{
  class SharedMemory;
}

namespace HAL
{
  struct SimPacket;
}

namespace PhysxEngine 
{
  class PhysxEngineMain sealed
  {
  private:
    World*              world;
    PosInfo*            posInfo;
    Util::SharedMemory* shmemBlue;
    Util::SharedMemory* shmemYellow;
    HAL::SimPacket*     blueTeamCommand;
    HAL::SimPacket*     yellowTeamCommand;

  public:
    PhysxEngineMain(PosInfo* posInfo);
    ~PhysxEngineMain();

    void updateWorld();
    void update(int i);
  };
}

#endif // PHYSX_ENGINE_MAIN_H