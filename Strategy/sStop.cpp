#include "skillSet.h"

namespace Strategy
{
  void SkillSet::stop(const SParam& param)
  {
    comm.sendCommand(botID, 0, 0, 0, 0, false);
  } // stop
}
