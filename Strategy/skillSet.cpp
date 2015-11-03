// This file contains all the skillSet functons
#include <cassert>
#include "skillSet.h"
#include "pathPlanners.h"
#include "beliefState.h"
#include "geometry.hpp"

using namespace HAL;
using namespace std;

namespace Strategy
{
#if GR_SIM_COMM
  GrSimComm SkillSet::comm;
#elif SIM_COMM
  SimComm   SkillSet::comm;
#elif SSL_COMM
  SSLComm   SkillSet::comm;
#else
# error Macro for Comm class not defined
#endif

  SkillSet::SkillSet(const BeliefState* state, const int botID) :
    state(state),
    botID(botID)
  {
    // Resetting the skill list
    for (int sID = 0; sID < MAX_SKILLS; ++sID)
    {
      skillList[sID] = NULL;
    }

    // Mapping the skill IDs to their corresponding function pointers
    skillList[Kick] = &SkillSet::kick;
    skillList[Spin] = &SkillSet::spin;
    skillList[Stop] = &SkillSet::stop;
    skillList[Dribble] = &SkillSet::dribble;
    skillList[DefendPoint] = &SkillSet::defendPoint;
    skillList[Velocity] = &SkillSet::velocity;
    skillList[GoToBall] = &SkillSet::goToBall;
    skillList[GoToPoint] = &SkillSet::goToPoint;
    skillList[DribbleToPoint] = &SkillSet::dribbleToPoint;
    skillList[KickToPoint] = &SkillSet::kickToPoint;
    skillList[ReceiveBall] = &SkillSet::receiveBall;
    skillList[TurnToAngle] = &SkillSet::turnToAngle;
    skillList[TurnToPoint] = &SkillSet::turnToPoint;

    // Initialization check
    for (int sID = 0; sID < MAX_SKILLS; ++sID)
    {
      assert(skillList[sID] != NULL); // Skill enum not mapped to the corresponding skill function
    }

    errt = new ERRT(0.2f, 0.6f);
    pathPlanner = new MergeSCurve();
  } // SkillSet

  SkillSet::~SkillSet()
  {
    delete errt;
    delete pathPlanner;
  } // ~SkillSet

  void SkillSet::trajectory2D(const Vector2D<int>&   startPos,
                              const Vector2D<int>&   finalPos,
                              const Vector2D<float>& startVel,
                              const Vector2D<float>& finalVel,
                              const float            startAng,
                              const float            finalAng,
                              const float            startAngVel,
                              const float            finalAngVel,
                              const float            frameRate,
                              const float            maxAcc,
                              const float            maxVel,
                              const float            maxAngAcc,
                              const float            maxAngVel,
                              Vector2D<float>&       trajVel,
                              float&                 angVel)
  {
    Vector2D<float> acc;
    float timeX, timeY;
    Vector2D<int> delta = finalPos - startPos;

    float u = PI / 2;
    float du = -PI / 2;
    // Performing binary search for the optimum value of alpha which will result in
    for (int i = 0; i < 10; ++i)
    {
      float alpha = u + (du /= 2);
      Vector2D<float> aTransMax, vTransMax;
      aTransMax.fromPolar(maxAcc, alpha);
      vTransMax.fromPolar(maxVel, alpha);

      trajectory1D(delta.x, startVel.x, finalVel.x, frameRate, aTransMax.x, vTransMax.x, acc.x, timeX);
      trajectory1D(delta.y, startVel.y, finalVel.y, frameRate, aTransMax.y, vTransMax.y, acc.y, timeY);

      if (timeX <= timeY)
        u = alpha;
    }

    float trajTime = MAXIMUM(timeX, timeY);
    float deltaAng = MINIMUM(finalAng - startAng, 0); // forcing deltaAng to lie in (-pi, pi]

    float angAcc = 0 , timeAng = INFINITY;
    for (float factor = 0.1f; factor <= 1.05f; factor += 0.1f)   // using 1.05f instead of 1.0f to account for errors due to floating point precision
    {
      trajectory1D(deltaAng, startAngVel, finalAngVel, frameRate, maxAngAcc * factor, maxAngVel, angAcc, timeAng);
      if (timeAng < trajTime)
        break;
    }

    trajVel.x = startVel.x + acc.x / frameRate;
    trajVel.y = startVel.y + acc.y / frameRate;
    angVel = startAngVel + angAcc / frameRate;
  } // trajectory2D

  void SkillSet::trajectory1D(const float dist,
                              const float startVel,
                              const float finalVel,
                              const float frameRate,
                              const float maxAcc,
                              const float maxVel,
                              float&      trajAcc,
                              float&      trajTime)
  {
    if (dist < 0.5 * (startVel + finalVel)*ABSOLUTE(finalVel - startVel) / maxAcc)
    {
      // Path not feasible given the constraints
      trajTime = INFINITY;
      return;
    }

    // Computation when bot can reach max velocity
    float accTime = (maxVel - startVel) / maxAcc;
    float decTime = (maxVel - finalVel) / maxAcc;
    float velTime = (dist / maxVel) - (accTime / 2) * (1 + startVel / maxVel) - (decTime / 2) * (1 + finalVel / maxVel);

    // Computation when bot cannot reach max velocity
    if (velTime < 0)
    {
      velTime = 0;

      float discr = 2 * (startVel * startVel + finalVel * finalVel) + 4 * maxAcc * dist;
      assert(discr >= 0);
      float sqrtDiscr = sqrt(discr);
      accTime = (-2 * startVel + sqrtDiscr) / (2 * maxAcc);
      decTime = (-2 * finalVel + sqrtDiscr) / (2 * maxAcc);

      assert(accTime >= 0 || decTime >= 0); // Both acceleration and deceleration times cannot be negative

      if (accTime < 0)
      {
        accTime = 0;
        decTime = 2 * dist / (startVel + finalVel);
      }
      if (decTime < 0)
      {
        decTime = 0;
        accTime = 2 * dist / (startVel + finalVel);
      }
    }

  } // trajectory1D
} // namespace Strategy
