// DO NOT EDIT: This file is auto-generated

#include <cstdlib>
#include "playBook.h"
#include "play.hpp"
#include "pNone.hpp"
#include "pTestPlay.hpp"
#include "pOffensePlay.hpp"
#include "pSetPosition.hpp"
#include "pDefenceSetPos1.hpp"
#include "pPositionOppStrike.hpp"
#include "pOffenceSetPos1.hpp"
#include "pPositionOurStrike.hpp"
#include "pDefensiveGoToGoal.hpp"
#include "pDefensiveSteal.hpp"
#include "pOurGoalKick.hpp"
#include "pOppGoalKick.hpp"
#include "pTieBreakerOurPenalty.hpp"
#include "pTieBreakerOppPenalty.hpp"

namespace Strategy
{
  PlayBook::PlayBook(const BeliefState& state) : 
    state(state)
  {
    reload();
  } // PlayBook

  PlayBook::~PlayBook()
  { } // ~PlayBook

  void PlayBook::reload(void)
  {
    // Initializing all play objects with NULL
    for (int pID=0; pID<PlayBook::MAX_PLAYS; ++pID)
    {
      playList[pID] = NULL;
    }

    // Inserting all the name-object pairs into the  Play List
    playList[PlayBook::None]                  = new PNone(state);
    playList[PlayBook::TestPlay]              = new PTestPlay(state);
    playList[PlayBook::SetPosition]           = new PSetPosition(state);
    playList[PlayBook::OffenceSetPosition1]   = new POffenceSetPosition1(state);
    playList[PlayBook::PositionOurStrike]     = new PPositionOurStrike(state);
    playList[PlayBook::OffensePlay]           = new POffensePlay(state); 
    playList[PlayBook::DefenceSetPosition1]   = new PDefenceSetPosition1(state);
    playList[PlayBook::PositionOppStrike]     = new PPositionOppStrike(state);
    playList[PlayBook::DefensiveGoToGoal]     = new PDefensiveGoToGoal(state);
    playList[PlayBook::DefensiveSteal]        = new PDefensiveSteal(state);
    playList[PlayBook::OurGoalKick]           = new POurGoalKick(state);
    playList[PlayBook::OppGoalKick]           = new POppGoalKick(state);
    playList[PlayBook::TieBreakerOurPenalty]  = new PTieBreakerOurPenalty(state);
    playList[PlayBook::TieBreakerOppPenalty]  = new PTieBreakerOppPenalty(state);
    
    // Checking if all the play ids have been associated with their corresponding Play objects
    for (int pID=0; pID<PlayBook::MAX_PLAYS; ++pID)
    {
      assert(playList[pID] != NULL); // Play has not been assigned a Play object
    }
  }
}
