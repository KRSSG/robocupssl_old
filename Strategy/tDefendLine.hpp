#ifndef TDEFENDLINE_HPP
#define TDEFENDLINE_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"
namespace Strategy
{
	///Class for Tactic TDefendLine.
	class TDefendLine : public Tactic
	{
	public:
	
		/**Constructor taking state and botID as parameters.
		*@param state a belief state type variable
		*@param botID an integer which identifies the bot executing the tactic
		*@see BeliefState*/
		TDefendLine(const BeliefState* state, int botID) :
			Tactic(Tactic::Stop, state, botID)
		{ }

		/**Destructor.*/
		~TDefendLine()
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
			return minv;	/**The best bot for the tactic is the one closest to the ball. */
		}
			
		/**Executes tactic with given Tactic parameters.
		 * @param tParam tactic parameters
		 * @see Tactic::Param*/
		void execute(const Param& tParam)
		{
			float x1,x3,x2,x4,y1,y2,y3,y4;
			x1=tParam.DefendLineP.x1;
			x2=tParam.DefendLineP.x2;
			y1=tParam.DefendLineP.y1;
			y2=tParam.DefendLineP.y2;
			x3=state->ballPos.x;
			y3=state->ballPos.y;
			x4=state->ballPos.x + state->ballVel.x;
			y4=state->ballPos.y+ state->ballVel.y;
			if(state->ballVel.x==0)
			{
//        printf("here1\n");
        return;
				x4=(x1+x2)/2;
				//y4=(y1+y2)/2;
			}
			
			Vector2D<int> targetPoint;
			// intersection formula copied from http://en.wikipedia.org/wiki/Line-line_intersection
			float denominator= (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
			if(denominator==0)
			{
//        printf("here2\n");
        targetPoint.x=(x1+x2)/2;
        targetPoint.y =state->ballPos.y+ state->ballVel.y;
				
			}
			else
			{
			targetPoint.x = ((x1*y2-y1*x2)* (x3-x4) - (x1-x2) *(x3*y4-y3*x4))/denominator;
			targetPoint.y = ((x1*y2-y1*x2)* (y3-y4) - (y1-y2) *(x3*y4-y3*x4))/denominator;
			}
			if(fabs(targetPoint.x) > fabs(HALF_FIELD_MAXX))
			{
				targetPoint.x=(x1+x2)/2;
			}
			if(fabs(targetPoint.y) > fabs(HALF_FIELD_MAXY))
			{
				targetPoint.y=(y1+y2)/2;
			}
//			if(x3 < x1)
//			{
//				/**Shifts the defence line if the ball has already crossed it.*/
//				targetPoint.x = state->ballPos.x  + 4*BOT_BALL_THRESH;
//				targetPoint.y = state->ballPos.y; + state->ballVel.y*0.3;
//			}
//			else
//			{
//				/**Continue moving along the line if the ball has not crossed it.*/
//				targetPoint.x = x1;
//				targetPoint.y = state->ballPos.y; + state->ballVel.y*0.3;
//			}
//
//			/**Set DefendPoint coordinates on the defence line*/
//			int xfinal = targetPoint.x < HALF_FIELD_MAXX ? targetPoint.x : HALF_FIELD_MAXX;
//			int yfinal = targetPoint.y;
			
			sParam.DefendPointP.x=targetPoint.x;
			sParam.DefendPointP.y=targetPoint.y;
			sParam.DefendPointP.radius =tParam.DefendLineP.radius;
			sID = SkillSet::DefendPoint;
			skillSet->executeSkill(sID, sParam);
			


			/**Tactic completed if ball comes in our possession or if ball crosses the defence line.*/
			if(state->pr_ourBall && x3>x1)
			{
				tState = COMPLETED;
			}

		}
	}; // class TDefendLine
} // namespace Strategy

#endif // TDEFENDLINE_HPP