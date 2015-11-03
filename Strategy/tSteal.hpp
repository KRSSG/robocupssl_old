#ifndef TSTEAL_HPP
#define TSTEAL_HPP

#include <list>
#include "comdef.h"
#include "tactic.h"
#include "skillSet.h"
#include "beliefState.h"
#include "logger.h"
#include "fieldConfig.h"

namespace Strategy
{
	class TSteal : public Tactic
	{
		public:
			TSteal(const BeliefState* state, int botID) :Tactic(Tactic::Stop, state, botID)
			{ } // TSteal

			~TSteal()
			{ } // ~TSteal

			inline bool isActiveTactic(void) const
			{
				//return true;
				return false;
			}

			int chooseBestBot(std::list<int>& freeBots, const Tactic::Param* tParam) const
			{
				int minv = *(freeBots.begin());
				int mindis = 1000000000;
				for(std::list<int>::iterator it = freeBots.begin(); it != freeBots.end(); ++it)
				{
					float dis_from_opp = (state->homePos[*it] - state->awayPos[state->oppBotNearestToBall]).absSq();
					if(*it == botID)
						dis_from_opp-=HYSTERESIS;
					if(dis_from_opp < mindis)
					{
						mindis = dis_from_opp;
						minv = *it;
					}
				}
				printf("%d assigned Steal\n", minv);
				return minv;
			} // chooseBestBot

			void execute(const Param& tParam)
			{
				if(state->pr_looseBall == true)
				{
//					printf("LOOSE BALL\n");
					sID = SkillSet::GoToBall;
					skillSet->executeSkill(sID, sParam);
					tState = RUNNING;
					if(Vector2D<int>::dist(state->ballPos,state->homePos[botID])<DRIBBLER_BALL_THRESH)   //
					{
//						printf("BALL CAPTURED\n");
						sID = SkillSet::Dribble;
						skillSet->executeSkill(sID, sParam);
						tState = COMPLETED;
					}
					//Util::Logger::toStdOut("Going to  : %f,%f\n",sParam.GoToPointP.x,sParam.GoToPointP.y);
				}
				if(state->pr_oppBall == true)
				{
//					printf("OPP BALL\n");
					sID = SkillSet::GoToBall;
					skillSet->executeSkill(sID, sParam);
					tState = RUNNING;
					if(Vector2D<int>::dist(state->ballPos,state->homePos[botID])<DRIBBLER_BALL_THRESH)
					{
//						printf("BALL CAPTURED , NOW TURNING WITH BALL\n");
						sID=SkillSet::TurnToAngle;
						float finalincline=state->homeAngle[botID]+PI/2;
						while((finalincline-state->homeAngle[botID])>0.5)     // to turn the bot once taken away from oppenent
						{
							sParam.TurnToAngleP.finalslope=finalincline;
							skillSet->executeSkill(sID, sParam);
						}
						tState = COMPLETED;
					}
				}
				if(state->pr_ourBall == true)  //our team takes possession
				{
//					printf("OUR BALL\n");
					tState = COMPLETED;
					sID = SkillSet::Stop;
					skillSet->executeSkill(sID, sParam);
				}
			}
	}; // class TSteal
} // namespace Strategy

#endif // TSTEAL_HPP
