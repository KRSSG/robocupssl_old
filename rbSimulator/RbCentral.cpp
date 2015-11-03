#include "RbCentral.h"

using namespace Simulator;
using namespace PhysxEngine;

RbCentral::RbCentral(PosInfo         *posInfo, 
                     PhysxEngineMain *engine) : posInfo(posInfo),
                                                engine(engine),
                                                ready(true)
{ 
}

//This is the function called at 60fps. No need to call setBot and setBall as earlier.
void RbCentral::run()
{
  static int counter=0;

  if(ready)
      engine->update(counter++);
}