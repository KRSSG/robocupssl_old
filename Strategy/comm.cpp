#include <cassert>
#include "comm.h"
#include "cs.hpp"

using namespace Util;

namespace HAL
{
  bool Comm::initializedOnce = false;
  CS   Comm::commCS;

  Comm::Comm()
  {
    assert(initializedOnce == false);
    initializedOnce = true;
  }

  Comm::~Comm()
  { }
} // namespace HAL
