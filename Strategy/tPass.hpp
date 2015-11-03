#ifndef TTPASS_HPP
#define TTPASS_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"


namespace Strategy
{
	class TPass : public Tactic
	{
	public:
		TPass(const BeliefState* state, int botID) :
			Tactic(Tactic::Stop, state, botID)
		{ } // TPass

		~TPass()
		{ } // ~TPass

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
		sID = SkillSet::KickToPoint;
		sParam.KickToPointP.x = tParam.PassP.x;
		sParam.KickToPointP.y = tParam.PassP.y;
		sParam.KickToPointP.power = tParam.PassP.power;
		
		skillSet->executeSkill(sID, sParam);              // Execute the selected skill
		
		if (state->homePos[botID].absSq() < BOT_BALL_THRESH * BOT_BALL_THRESH)      //end conditions
		{
			tState = COMPLETED;
		}			
			
		}
	};// class TPass
} // namespace Strategy

#endif // TTPass_HPP
