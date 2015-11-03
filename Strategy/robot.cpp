#include <iostream>
#include <cstring>
#include <ctime>
#include "robot.h"
#include "beliefState.h"
#include "skillSet.h"
#include "tBlock.hpp"
#include "tCharge.hpp"
#include "tDefendLine.hpp"
#include "tDefendPoint.hpp"
#include "tGoalKeepingOppSide.hpp"
#include "tGoalKeepingOurSide.hpp"
#include "tMarkBot.hpp"
#include "tPosition.hpp"
#include "tPositionForPenalty.hpp"
#include "tPositionForStart.hpp"
#include "tShoot.hpp"
#include "tDefend.hpp"
#include "tSteal.hpp"
#include "tStop.hpp"
#include "tDragToGoal.hpp"
#include "tAttack.hpp"
#include "tVelocity.hpp"
#include "tAttack.hpp"
#include "tPass.hpp"

using namespace std;
using namespace Util;
using namespace HAL;

namespace Strategy
{
  Robot::Robot(BeliefState& stateSh,
               CS&          stateCS,
               CS*          tacticCS,
               int          botID) :
    tIDSh(Tactic::Stop),
    tStateSh(Tactic::INIT),
    botID(botID),
    tacticCS(tacticCS),
    stateSh(stateSh),
    stateCS(stateCS)
  {
    state = new BeliefState();  // Initializing with default constructor to avoid re-instantaition of referee box and vision thread
    
    // Resetting the tactic list
    for (int tID = 0; tID < Tactic::MAX_TACTICS; ++tID)
    {
      tacticList[tID] = NULL;
    }

    // List all Tactic ID -> Tactic object pairs here for each robot
    tacticList[Tactic::Block]               = new TBlock(state, botID);
    tacticList[Tactic::ChargeBall]          = new TCharge(state, botID);
    tacticList[Tactic::DefendLine]          = new TDefendLine(state, botID);
    tacticList[Tactic::DefendPoint]         = new TDefendPoint(state, botID);
    tacticList[Tactic::GoalieOur]           = new TGoalKeepingOurSide(state, botID);
    tacticList[Tactic::GoalieOpp]           = new TGoalKeepingOppSide(state, botID);
    tacticList[Tactic::MarkBot]             = new TMarkBot(state, botID);
    tacticList[Tactic::Pass]                = new TPass(state, botID);
    tacticList[Tactic::Position]            = new TPosition(state, botID);
    tacticList[Tactic::PositionForPenalty]  = new TPositionForPenalty(state, botID);
    tacticList[Tactic::PositionForStart]    = new TPositionForStart(state, botID);
    tacticList[Tactic::Defend]              = new TDefend(state,botID);
    tacticList[Tactic::Attack]              = new TAttack(state,botID);
    tacticList[Tactic::Shoot]               = new TShoot(state, botID);
    tacticList[Tactic::Steal]               = new TSteal(state, botID);
    tacticList[Tactic::Stop]                = new TStop(state, botID);
    tacticList[Tactic::Velocity]            = new TVelocity(state, botID);

    // Initialization check
    for (int tID = 0; tID < Tactic::MAX_TACTICS; ++tID)
    {
      assert(tacticList[tID] != NULL); // Tactic enum not mapped to the corresponding Tactic object
    }
    this->start();
  } // Robot

  Robot::~Robot()
  {
    delete state;
    
    for (int tID = 0; tID < Tactic::MAX_TACTICS; ++tID)
    {
      if (tacticList[tID] != NULL)
      {
        delete tacticList[tID];
      }
    }
  } // ~Robot

  void Robot::run()
  {
    Tactic::ID    tID = Tactic::Stop;
    Tactic::Param tParam;
    bool          updated;

    while (true)
    {
      updated = false;
      {
        // Updating the belief state
        stateCS.enter();
        if (state->currFrameNum != stateSh.currFrameNum)
        {
          updated = true;
          memcpy(state, &stateSh, sizeof(BeliefState));
        }
        stateCS.leave();
      }

      {
        // Updating the tactic and its parameters to be executed next
        tacticCS->enter();
        tID    = tIDSh;
        tParam = tParamSh;
        if (tStateSh == Tactic::INIT)
        {
          tStateSh = Tactic::RUNNING;
          tacticList[tID]->initialize();
        }
        tacticCS->leave();
      }

      if (updated)
      {
        tacticList[tID]->execute(tParam);
      }
      sleep(16);  // Adding sleep to this thread of execution to prevent CPU hogging
    }
  } // run
} // namespace Strategy
