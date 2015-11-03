// It is through the skill layer that the Strategy layer talks to the Simulator/Actual robots

#ifndef SKILLS_H
#define SKILLS_H

#if GR_SIM_COMM
# include "grSimComm.h"
#elif SIM_COMM
# include "simComm.h"
#elif SSL_COMM
# include "sslComm.h"
#else
# error Macro for Comm class not defined
#endif

// Forward Declarations
namespace Strategy
{
  class ERRT;
  class MergeSCurve;
  class BeliefState;
}

template <class T> class Vector2D;

namespace Strategy
{
  /* Procedure for adding a skill successfully to the SkillSet is:
   * 1. Enumarate it in enum SkillSet::SkillID just before MAX_SKILLS
   * 2. Identify its input parameters and define a struct for it in union SkillSet::SParam
   * 3. Declare the function prototype for the skill. Its parameter must only be SParam& param
   * 4. Map the Skill ID to the corresponding function in the constructor of SkillSet
   * 5. Define the function that implements the skill declared in step 3.
   * NOTE: Variable names of enums and corresponding skill function names must be the same,
   *       except that the enum name starts with a capital letter. Name of the corresponding
   *       struct should be the same as that of enum with a trailing 'P' character
   */

  class SkillSet
  {
  public:
    enum SkillID
    {
      Spin,
      Kick,
      Stop,
      Dribble,
      Velocity,
      GoToBall,
      GoToPoint,
      DefendPoint,
      DribbleToPoint,
      KickToPoint,
      ReceiveBall,
      TurnToPoint,
      TurnToAngle,
      MAX_SKILLS
    };

    // Union of parameters for each skill enumerated in SkillID
    union SParam
    {
      // Parameters for the skill Spin
      struct
      {
        float radPerSec;
      } SpinP;

      // Parameters for the skill Stop
      struct
      {} StopP;

      struct
      {
        bool intercept;
      } GoToBallP;

      // Parameters for the skill Kick
      struct
      {
        float power;
      } KickP;
      //Parameters for the skill KickToPoint
      struct
      {
        float power;
        float x;
        float y;
      } KickToPointP;
      // Parameters for the skill Velocity
      struct
      {
        float v_x;
        float v_y;
        float v_t;
      } VelocityP;

      //Parameters for skill goToPoint and dribble to point
      struct
      {
        float x;
        float y;
        float finalslope;
        float radius;
      }  DefendPointP, DribbleToPointP, GoalKeepingP, TurnToAngleP;
      struct
      {
        float x;
        float y;
        float max_omega;
      } TurnToPointP;
      struct
      {
        float x;
        float y;
        float finalslope;
        bool align;
        float finalVelocity;
      } GoToPointP;
    };



  private:
#if GR_SIM_COMM
    static HAL::GrSimComm comm;
#elif SIM_COMM
    static HAL::SimComm   comm;
#elif SSL_COMM
    static HAL::SSLComm   comm;
#else
#   error Macro for Comm class not defined
#endif

  protected:
    typedef void (SkillSet::*skillFncPtr)(const SParam&);
    const BeliefState* state;
    const int          botID;
    skillFncPtr        skillList[MAX_SKILLS];
    MergeSCurve*       pathPlanner;
    ERRT*              errt;

  private:
    /* trajectory2D() and trajectory1D() functions implement the path following
     * algorithm based on bang-bang motion. The pseudo code was obtained from
     * Skuba 2011 ETDP which can be found at
     * http://small-size.informatik.uni-bremen.de/tdp/etdp2011/SKUBA_ETDP_2011.pdf
     */
    void trajectory2D(const Vector2D<int>&   startPos,
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
                      float&                 angVel);

    /* Given the distance to cover, start velocity, final velocity,
     * frame rate, maximum acceleration and maximum velocity, this function
     * computes the required initial acceleration and the time required
     * to complete the path and returns it. In case, a path is not feasible
     * with the given values, a very high value of time for completing the
     * path is returned
     */
    void trajectory1D(const float dist,
                      const float startVel,
                      const float finalVel,
                      const float frameRate,
                      const float maxAcc,
                      const float maxVel,
                      float&      trajAcc,
                      float&      tracTime);

  public:
    //------- List of robot skills -------//
    void spin(const SParam& param);
    void stop(const SParam& param);
    void kick(const SParam& param);
    void dribble(const SParam& param);
    void velocity(const SParam& param);
    void goToBall(const SParam& param);
    void goToPoint(const SParam& param);
    void defendPoint(const SParam& param);
    void dribbleToPoint(const SParam& param);
    void receiveBall(const SParam& param);
    void goalKeeping(SParam& param);
    void kickToPoint(const SParam& param);
    void turnToPoint(const SParam& param);
    void turnToAngle(const SParam& param);

    SkillSet(const BeliefState* state, int botID);

    ~SkillSet();

    // Executing the skill function corresponding to the given ID and param function parameters
    inline void executeSkill(SkillID ID, const SParam& param)
    {
      (*this.*skillList[ID])(param);
    } // executeSkill
  }; // class SkillSet
} // namespace Strategy

#endif // SKILLS_H
