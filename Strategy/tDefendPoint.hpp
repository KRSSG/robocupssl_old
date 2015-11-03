#ifndef TDEFENDPOINT_HPP
#define TDEFENDPOINT_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	///Class for Tactic TDefendPoint.
	class TDefendPoint : public Tactic
	{
	public:
	
		/**Constructor taking state and botID as param.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TDefendPoint(const BeliefState* state, int botID) :
			Tactic(Tactic::Stop, state, botID)
		{ }
			
		/**Destructor.*/
		~TDefendPoint()
		{ }
		
		/**Checks if the tactic is of type active.
		 *@return boolean type variable*/
		inline bool isActiveTactic(void) const
		{
			return false;
		}
	
		/**@return the botID of the best bot (int type) for the given tactic among the free bots.
		 * @param freeBots list of botIDs of free bots
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
		{
			int minv = *(freeBots.begin());
			int mindis = 10000;
			for(std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
			{
				float dis_from_ball = (state->homePos[*it] - state->ballPos).absSq();
				if(dis_from_ball < mindis)
				{
					dis_from_ball = mindis;
					minv = *it;
				}
			}
			return minv;				/**The best bot for the tactic is the one closest to the ball. */
		}

		/**Executes tactic with given Tactic parameters.
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		void execute(const Param& tParam)
		{
			{
				sID = SkillSet::DefendPoint;
				sParam.DefendPointP.x=tParam.DefendPointP.x;
				sParam.DefendPointP.y=tParam.DefendPointP.y;
				sParam.DefendPointP.radius =tParam.DefendPointP.radius;
				skillSet->executeSkill(sID, sParam);
			}
			
			/**Tactic completed if goal score / free kick or penalty awarded.*/
//			if (state->pr_ourGoal||state->pr_oppGoal||state->pr_ourFreeKick||state->pr_ourPenalty)
//			{
//			  tState = COMPLETED;
//			}
		}
	}; // class TDefendPoint
} // namespace Strategy

#endif // TDEFENDPOINT_HPP
