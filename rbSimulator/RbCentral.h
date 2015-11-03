#ifndef RBCENTRAL_H
#define RBCENTRAL_H

#include "physxEngineMain.h"
#include "server.h"

namespace Simulator
{
  class RbCentral
  {
    public:
      PhysxEngine::PosInfo *posInfo;
      PhysxEngine::PhysxEngineMain* engine;
      bool ready;
      RbCentral(PhysxEngine::PosInfo* posInfo, PhysxEngine::PhysxEngineMain* engine);
      void run();
  };
}/* end RbCentral*/

#endif