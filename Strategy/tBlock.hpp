#ifndef TTBLOCK_HPP
#define TTBLOCK_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"


namespace Strategy
{
	class TBlock : public Tactic
	{
	public:
		TBlock(const BeliefState* state, int botID) :
			Tactic(Tactic::Stop, state, botID)
		{ } // TBlock

		~TBlock()
		{ } // ~TBlock

		inline bool isActiveTactic(void) const
		{
			return true;
		}
    
    int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
		{
			int minv = *(freeBots.begin());
      int mindis = Vector2D<int>::dist(state->homePos[minv],state->ballPos);
			for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
				// TODO make the bot choosing process more sophisticated, the logic below returns the 1st available bot    
        if(Vector2D<int>::dist(state->homePos[*it],state->ballPos)<mindis)
				{
					mindis = Vector2D<int>::dist(state->homePos[*it],state->ballPos);;
					minv = *it;
				}
			}
			return minv;
		} // chooseBestBot
    void execute(const Param& tParam)
		{
       sID = SkillSet::GoToPoint;
       sParam.GoToPointP.x=state->ballPos.x + tParam.BlockP.side*tParam.BlockP.dist;
       sParam.GoToPointP.y=state->ballPos.y + tParam.BlockP.side*tParam.BlockP.dist;
      // sParam.GoToPointP.finalslope=0;
      // SkillSet::_goToPoint(botID,sParam,state->ballVel,0,0);
		skillSet->executeSkill(sID, sParam);
		if(state->homePos[botID].x>/*Opp_D*/2300)   //end conditions
        {
          sID = SkillSet::Stop;
//          printf("Competed Tactic\n");
          tState = COMPLETED;
        }
        

			// Execute the selected skill
			
		}
	};// class TBlock
} // namespace Strategy

#endif // TTBLOCK_HPP