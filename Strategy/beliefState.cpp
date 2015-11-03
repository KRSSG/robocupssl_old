#include <ctime>
#include "beliefState.h"
#include "visionThread.h"
#include "fieldConfig.h"
#include "thread.h"
#include "rbCommDef.h"
#include "cs.hpp"
#include "fieldConfig.h"
#include "logger.h"
#include "skillSet.h"

using namespace std;
using namespace Util;
using namespace HAL;
using namespace Simulator;

namespace Strategy
{

	BeliefState::BeliefState() :
		prevFrameNum(-1),
		currFrameNum(-1)
	{
		for(int botID = 0; botID < HomeTeam::SIZE; botID++)
		{
			homeAngle[botID] = 0;
		}

		for(int botID = 0; botID < AwayTeam::SIZE; botID++)
		{
			awayAngle[botID] = 0;
		}
		ourGoalCount    = 0;
		oppGoalCount    = 0;
		timeRemaining   = 0;
// If Refree Box is not going to run do not wait for signal from refree box to start the game
#ifdef RUN_REFBOX
		gameRunning     = false;
#else
		gameRunning     = true;
#endif
		pr_gameHalted      = false;
		pr_ourFreeKick     = false;
		pr_oppFreeKick     = false;
		pr_ourGoalKick     = false;
		pr_oppGoalKick     = false;
	}

	BeliefState::~BeliefState()
	{

	}

	bool BeliefState::update()
	{
    return false;
	} // update
	/* Function definitions for all the predicates...
	   * */

	void BeliefState::computeBallLocation()
	{
		int homeNearbotID = -1, awayNearbotID = -1;
		float minDist,distSq,closestBot ;
		minDist = 1000000000.0;
		for(int i = 0; i < HomeTeam::SIZE ; i++)
		{
			float th = Vector2D<int>::angle(ballPos, homePos[i]);
			float theta = normalizeAngle(th - homeAngle[i]);
			distSq =  Vector2D<int>::distSq(ballPos , homePos[i]);

			if(distSq < minDist)
			{
				minDist = distSq;
				closestBot = i;
			}
			this->ourBotNearestToBall = closestBot;
			if(distSq < (BOT_BALL_THRESH_FOR_PR * BOT_BALL_THRESH_FOR_PR) && fabs(theta) < DRIBBLER_BALL_ANGLE_RANGE)
			{
				homeNearbotID = i;
				break ;
			}
		}
		minDist = 1000000000.0;
		for(int i = 0; i < AwayTeam::SIZE ; i++)
		{
			float theta = normalizeAngle(Vector2D<int>::angle(ballPos, homePos[i]) - awayAngle[i]);
			distSq = Vector2D<int>::distSq(ballPos , awayPos[i]);
			if(distSq < minDist)
			{
				minDist = distSq;
				closestBot = i;
			}
			this->oppBotNearestToBall = closestBot;
			if(distSq < (BOT_BALL_THRESH_FOR_PR * BOT_BALL_THRESH_FOR_PR) && fabs(theta) < DRIBBLER_BALL_ANGLE_RANGE)
			{
				awayNearbotID = i;
				break ;
			}
		}
		//printf("OurBotnearest, OppBotNearest : %d %d\n",ourBotNearestToBall,oppBotNearestToBall);
		if(awayNearbotID == -1 && homeNearbotID == -1)
		{
			pr_looseBall = true;
			pr_oppBall = false;
			pr_ourBall = false;

		}
		else if(awayNearbotID == -1 && homeNearbotID != -1)
		{
			pr_looseBall  =  false;
			pr_oppBall    =  false;
			pr_ourBall    =  true;
		}
		else if(awayNearbotID != -1 && homeNearbotID == -1)
		{
			pr_looseBall  =  false;
			pr_oppBall    =  true;
			pr_ourBall    =  false;
		}
		else if(awayNearbotID != -1 && homeNearbotID != -1)
		{
			pr_looseBall  =  false;
			pr_oppBall    =  true;
			pr_ourBall    =  false;

		}

	}

	void BeliefState::computeBallInDBox()
	{
		pr_ball_in_opp_dbox = false;
		pr_ball_in_our_dbox = false;

		if(ballPos.x < (-HALF_FIELD_MAXX+DBOX_WIDTH)&&
		        ballPos.y <OUR_GOAL_MAXY &&
		        ballPos.y >OUR_GOAL_MINY)
			pr_ball_in_our_dbox = true;
		else if(ballPos.x > (HALF_FIELD_MAXX-DBOX_WIDTH)&&
		        ballPos.y <OUR_GOAL_MAXY &&
		        ballPos.y >OUR_GOAL_MINY)
			pr_ball_in_opp_dbox = true;
//		if(pr_ball_in_our_dbox)
//			Util::Logger::toStdOut("\nBALL_IN_OUR_DBOX\n");
//		if(pr_ball_in_opp_dbox)
//			Util::Logger::toStdOut("\nBALL_IN_OPP_DBOX\n");
	}

	//The following three assume that 0,0 is at center of frame (for checking ball parameters)

	void BeliefState::computeBallSide()
	{
		//	printf("DF our %d\topp %d\n",pr_ballOurSide,pr_ballOppSide);
			if(ForwardX(ballPos.x) >ForwardX(- MID_FIELD_THRESH)) 
			{//MID_FIELD_THRESH is the distance from midfield line into which when ball goes ball's side changes
				pr_ballOurSide = true ;
				pr_ballOppSide=false;
			}
			else if(ForwardX(ballPos.x) < ForwardX(MID_FIELD_THRESH)) 
			{
				pr_ballOppSide = true ;
				pr_ballOurSide = false ;
			}
			else if(fabs(ballPos.x)<fabs(MID_FIELD_THRESH) && pr_ballOurSide==true)
				{pr_ballOppSide=false;
				pr_ballOurSide=true;}
			else   
				
				{pr_ballOurSide=false;
				pr_ballOppSide=true;}
			
		
	}



	bool BeliefState::pr_nOpponentsOurSide(int n)
	{
		int ctr = 0;
		for(int i = 0; i < AwayTeam::SIZE ; i++)
		{
			if(awayPos[i].x < 0)
				ctr ++ ;
		}
		if(ctr == n)
			return true ;
		else
			return false ;
	}

	bool BeliefState::pr_ballXGt(int x)
	{
		if(ballPos.x > x)
			return true ;
		else
			return false ;
	}

	bool BeliefState::pr_ballXLt(int x)
	{
		if(ballPos.x  < x)
			return true ;
		else
			return false ;
	}

	bool BeliefState::pr_ballAbsYGt(int y)
	{
		int absy = ballPos.y > 0 ? ballPos.y : (-(ballPos.y)) ;
		if(absy > y)
			return true ;
		else
			return false ;
	}

	bool BeliefState::pr_ballAbsYLt(int y)
	{
		int absy = ballPos.y > 0 ? ballPos.y : (-(ballPos.y)) ;
		if(absy < y)
			return true ;
		else
			return false ;
	}

	void BeliefState::computeBallInStrips()
	{
		pr_ballInFrontStrip = (ballPos.x > HALF_FIELD_MAXX - STRIP_WIDTH_X || ballPos.x < -HALF_FIELD_MAXX+STRIP_WIDTH_X);
		pr_ballInSideStrip  = (ballPos.y > HALF_FIELD_MAXY - STRIP_WIDTH_Y || ballPos.y < -HALF_FIELD_MAXY+STRIP_WIDTH_Y);
	}

	void BeliefState::updateStateFromRefree(HAL::RefBoxCmd &refBoxCmdSh)
	{
		if(Strategy::HomeTeam::COLOR==Simulator::BLUE_TEAM)
		{
		ourGoalCount   = refBoxCmdSh.goalsBlue;
		oppGoalCount   = refBoxCmdSh.goalsYellow;
		}
		// update state based on the value of the cmd. Need to define the conventions.
		else
		{
		oppGoalCount   = refBoxCmdSh.goalsYellow;
		ourGoalCount   = refBoxCmdSh.goalsBlue;
		}
		pr_ourGoal =false;
		pr_oppGoal =false;
		pr_goalscored=false;
		timeRemaining  = refBoxCmdSh.timeRemaining;
		Util::Logger::toStdOut("Updating state from REFEREE BOX");
		switch(refBoxCmdSh.cmd)
		{
			case 'S':
				gameRunning = false;
				break;
			case 'H':
				gameRunning = false;
				pr_gameHalted = true;
				break;
			case 's':
				gameRunning = true;
				break;
			case 'K':
				pr_ourGoalKick = true;
				break;
			case 'k':
				pr_oppGoalKick = true;
				break;
			case 'p':
			case 'f':
			case 'i':
				pr_oppFreeKick = true;
				break;
			case 'P':
			case 'F':
			case 'I':
				pr_ourFreeKick = true;
				break;
			case 'n':
				pr_ourFreeKick = false;
				pr_oppFreeKick = false;
				pr_ourGoalKick = false;
				pr_oppGoalKick = false;
				gameRunning = true;
				break;
			case 'G':
				pr_ourGoal =true;
				pr_oppGoal =false;
				pr_goalscored=true;
			case 'g':
				pr_ourGoal =false;
				pr_oppGoal =true;
				pr_goalscored=true;
		}
		refreeUpdated = true;
	}
	void BeliefState::computeBallInCorner()
	{
		if(ballPos.x<-HALF_FIELD_MAXX+BALL_AT_CORNER_THRESH && (ballPos.y>HALF_FIELD_MAXY-BALL_AT_CORNER_THRESH||ballPos.y<-HALF_FIELD_MAXY+BALL_AT_CORNER_THRESH))
		{
			pr_ballInOurCorner=true;
			pr_ballInOppCorner=false;
		}
		if(ballPos.x>HALF_FIELD_MAXX-BALL_AT_CORNER_THRESH && (ballPos.y>HALF_FIELD_MAXY-BALL_AT_CORNER_THRESH||ballPos.y<-HALF_FIELD_MAXY+BALL_AT_CORNER_THRESH))
		{
			pr_ballInOurCorner=false;
			pr_ballInOppCorner=true;
		}
	}
} // namespace Strategy