#ifndef TDEFEND_HPP
#define TDEFEND_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"
namespace Strategy
{
	///Class for Tactic TDefend.
	class TDefend : public Tactic
	{
	public:
	
		/**Constructor taking state and botID as parameters.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TDefend(const BeliefState* state, int botID) :
			Tactic(Tactic::Stop, state, botID)
		{ }
		
		/**Destructor.*/
		~TDefend()
		{ }
		
		/**Checks if the tactic is of type active.*/
		inline bool isActiveTactic(void) const
		{
			return false;
		}

		/**@return the botID of the best bot for the given tactic among the free bots.
		 * @param freeBots list of botIDs of free bots
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
		{
			int minv = *(freeBots.begin());
			int mindis = fabs(state->homePos[*(freeBots.begin())].x - tParam->DefendP.x);
			for (std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
				float dis_from_defendline = fabs(state->homePos[*it].x - tParam->DefendP.x);
				if(*it == botID)
					dis_from_defendline-=sqrt((float)HYSTERESIS);
					if(dis_from_defendline < mindis)
						{
						dis_from_defendline = mindis;
						minv = *it;
						}
			}
			return minv; /**The best bot for the tactic is the one closest to the line to be defended. */
		}
		
		/**Executes tactic with given Tactic parameters.
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		void execute(const Param& tParam)
		{
		float x;
		  {
			x=tParam.DefendP.x;
			if(state->ballPos.x < x)
			{
				/**Shifts the defence line if the ball has already crossed it.*/
				x = state->ballPos.x-2*BOT_BALL_THRESH;
			}
			sParam.GoToPointP.x = x;
			sParam.GoToPointP.y  = state->ballPos.y;
			sParam.GoToPointP.align = true;
			sParam.GoToPointP.finalslope = PI/2;
			/**Goes to the defence line with y-coordinates as that of the ball.*/
        
			sID = SkillSet::GoToPoint;
			skillSet->executeSkill(sID, sParam);
		}
      
	  /**Tactic completed if ball comes in our possession.*/
      if(state->pr_ourBall)
        tState = COMPLETED;
      else
        tState = RUNNING;
      
		}
	}; // class TDefend
} // namespace Strategy
#endif // TDEFEND_HPP