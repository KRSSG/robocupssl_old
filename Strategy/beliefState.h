#ifndef BELIEF_STATE_H
#define BELIEF_STATE_H

#include "comdef.h"
#include "geometry.hpp"
#include "../sslrefbox/client/game_state.h"

/**Forward Declarations.*/
namespace HAL
{
  class VisionInfo;
  class RefBoxCmd;
}

namespace Strategy
{
  class VisionThread;
}

namespace Util
{
  class CS;
}

namespace Strategy
{
  ///@class BeliefState This class defines the state parameter during game play.
	class BeliefState
  {
  private:
    int              prevFrameNum; ///<private int type variable to hold last Frame number.
    


    // stateSh is the shared belief state. It will be shared by the home robots.
	public:
  ///BeliefState  constructor.
    BeliefState();
  ///BeliefState Destructor.
    ~BeliefState();

    /** It tries to update the belief state. 
	 * @return  If it does not changes the function  returns false else true*/
    bool      update();
	
    bool      refreeUpdated; ///<Boolean type variable.Is true afer the refree is updated
    int       currFrameNum;   ///<Integer type variable.Holds current Frame number
    GameState gameState;  ///<GameState object variable. Holds state as reported by the Referee Box

    Point2D<int>    homePos[HomeTeam::SIZE]; /**<Array of Vector2D type objets of length team size .
	                                         *stores team members positions
											 * Has basic fuctionalities associated with vector operations*/

    Vector2D<float> homeVel[HomeTeam::SIZE]; ///<Vector2D type array to hold our bot's velocity components.
    Vector2D<float> homeAcc[HomeTeam::SIZE]; ///<Vector2D type array to hold our bot's acceleration components.
    float           homeAngle[HomeTeam::SIZE]; /**<Team size array of float type.
	                                           *Holds angle of each bot with respect to positive x axis.*/ 
    float           homeOmega[HomeTeam::SIZE];///<Float type our team size array to hold our team member's angular velocity.
    float           homeAngAcc[HomeTeam::SIZE];///<Float type our team size array to hold our team member's angular acceleration.
    
    Point2D<int>    awayPos[HomeTeam::SIZE];/**<Array of Vector2D type objets of length team size .
	                                         *stores opponent team member's positions
											 * Has basic fuctionalities associated with vector operations*/
											 
    Vector2D<float> awayVel[HomeTeam::SIZE];///<Vector2D type array to hold opponent bot's velocity components.
    Vector2D<float> awayAcc[HomeTeam::SIZE];///<Vector2D type array to hold opponent bot's acceleration components.
    float           awayAngle[HomeTeam::SIZE];///<Team size array of float type.Holds angle of each opponent bot with respect to positive x axis
    float           awayOmega[HomeTeam::SIZE];///<Float type our team size array to hold opponents team member's angular veolcity.
    float           awayAngAcc[HomeTeam::SIZE];///<Float type our team size array to hold opponents team member's angular acceleration.
    
    Point2D<int>    ballPos;  ///<Vector2D object to hold position of ball at that time.
    Vector2D<float> ballVel;  ///<Vector2D object to hold velocity of ball at that time.
    Vector2D<float> ballAcc; ///<Vector2D object to hold accleration of ball at that time.

    // Rarely changing elements from refree box
    int ourGoalCount;  ///< Integer type variable to hold our goal count.
    int oppGoalCount;  ///< Integer type variable to hold opponent goal count.
    int timeRemaining; ///< Integer type variable to hold tme remaining for the half to end.
    bool pr_gameHalted; ///<Boolean type variable.his state is necessary to select the play to halt the robots in their position

    bool gameRunning;  ///<Boolean type, true when game running.
    bool pr_ourGoalKick;  ///<Boolean type , true when our goal kick.
    bool pr_oppGoalKick;  ///<Boolean type , true when opponent's goal kick.
    bool pr_ourPenaltyKick;  ///<Boolean type , true when our penalty kick.
    bool pr_oppPenaltyKick;  ///<Boolean type , true when opponent's penalty kick.

    //------- Set of high-level predicates -------//
    
    /* This predicates are calculated by computeBallLocation */
    int ourBotNearestToBall; ///<Integer type High-level predicates. Holds botid of our bot nearest to ball 
    int oppBotNearestToBall;  ///<Integer type High-level predicates. Holds botid of opponent bot nearest to ball 
    
    /* The two predicates below are computed in computeBallInDBox() */
    bool pr_ball_in_our_dbox; ///<True when ball in our D box.Computed in computeBallInDBox()
    bool pr_ball_in_opp_dbox;  ///<True when ball in opponent D box.Computed in computeBallInDBox()
    
    bool pr_goalscored; ///<Predicate for goal scored.
	
	bool pr_ourGoal;      ///<Boolean type , true when our Goal. 
	
    bool pr_oppGoal;      ///<Boolean type , true when opp Goal. 


    bool pr_oppBall;  ///<True when ball is with opponent.

    bool pr_ourBall;  ///<True when ball is with us.

    bool pr_looseBall;  ///<True when no one posses the ball.

    bool pr_ballOppSide;  ///<True when ball is in opponent half.

    bool pr_ballOurSide; ///<True when ball in our half.

    bool pr_ballInOurCorner;  ///<True when ball in our corner .

    bool pr_ballInOppCorner;  ///<Predicate true when ball in opponent corner.
	
    bool pr_ourKickOff;  ///<True when we are to kick off.

    /// @predicate oppKickOff
    bool pr_oppKickOff; ///<Predicate true when its opponent kick off.

    /// @predicate ourFreeKick
    bool pr_ourFreeKick; ///<Predicate true when its our free kick.

    /// @predicate oppFreeKick
    bool pr_oppFreeKick;  ///<Predicate true when its opponent free kick.

    ///@predicate ourPenalty
    bool pr_ourPenalty;  ///<Predicate true when its our penalty kick.

    /// @predicate oppPenalty
    bool pr_oppPenalty; ///<Predicate true when its opponent penalty kick.

    // Predicates that take an input parameter
    ///@predicate nOpponentsOurSide < n >
    bool pr_nOpponentsOurSide(int n);

    /// @predicate ballXGt < x >
    bool pr_ballXGt(int x);

    /// @predicate ballXLt < x >
    bool pr_ballXLt(int x);

    /// @predicate ballAbsYGt < y >
    bool pr_ballAbsYGt(int y);

    /// @predicate ballAbsYLt < y >
    bool pr_ballAbsYLt(int y);


    /// @predicate ballInSideStrip
    bool pr_ballInSideStrip;
    
    /// @predicate ballInFrontStrip
    bool pr_ballInFrontStrip;
    
    // Prototypes for functions that compute the values of the predicates
	
	/**Sets Predicates corrosponding to conditions.
	 * @see pr_ball_in_our_dbox
	 * @see pr_ball_in_opp_dbox*/
    void computeBallInDBox(); 
	
	/**Function for computing our / opponents bot nearest to ball.
	 * @see ourBotNearestToBall
	 * @see oppBotNearestToBall*/
    void computeBallLocation();
	

	
	/**Function for predicates evaluation.
	 * @see pr_ballOppSide
	 * @see pr_ballOurSide*/
    void computeBallSide();
	

 

    /**Function for predicates evaluation.
	 * @see pr_ballInOurCorner*/
    void computeBallInCorner(); 
	
    void computeBallInStrips();
	
	/**Constantly updates the states frfom refree.*/
    void updateStateFromRefree(HAL::RefBoxCmd &refBoxCmdSh);
	
  }; // class BeliefState
} // namespace Strategy

#endif // BELIEF_STATE_H