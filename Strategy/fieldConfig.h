#ifndef FIELD_CONFIG_H
#define FIELD_CONFIG_H

#include "../rbSimulator/config.h"

#if SIM_COMM || GR_SIM_COMM // Parameters for the simulator
# define SELECT(sim_param, ssl_param) (sim_param)
#elif SSL_COMM || FIRA_COMM// Parametres for the real bots
# define SELECT(sim_param, ssl_param) (ssl_param)
#else
# error Macro for Comm class not fully handled
#endif
#define SGN(x) (((x)>0)?1:(((x)<0)?(-1):0))

extern bool FIELD_IS_INVERTED;
template<class T> T ForwardX(T distance) {
  return FIELD_IS_INVERTED?(-distance):distance;
}

#define SELECTX(a, b) ForwardX(SELECT(a, b))
static const int   BOT_COUNT                  = SELECT(5,5);
static const float MOVING_BALL_VELOCITY       = SELECT(40, 30);
static const float MIN_DIST_FROM_TARGET       = SELECT(30.0, 25.0);
static const int CENTER_X                     = SELECT(0, 0);
static const int CENTER_Y                     = SELECT(0, 0);
static const int HALF_FIELD_MAXX              = SELECTX(3025, 3025); //actual 225 (rugged surface at end)
static const int HALF_FIELD_MAXY              = SELECT(2025, 2025);

#define OUR_GOAL_X                            ForwardX(-HALF_FIELD_MAXX)
#define OPP_GOAL_X                            ForwardX(HALF_FIELD_MAXX)

static const int OUR_GOAL_MAXY                = SELECT(600,600);
static const int OUR_GOAL_MINY                = SELECT(-600, -600);
static const int OPP_GOAL_MAXY                = SELECT(600, 600);
static const int OPP_GOAL_MINY                = SELECT(-600, -600);
static const int OUR_GOAL_WIDTH               = OUR_GOAL_MAXY - OUR_GOAL_MINY;
static const int OPP_GOAL_WIDTH               = OPP_GOAL_MAXY - OPP_GOAL_MINY;
static const int CENTER_CIRCLE_DIAMETER       = SELECT(1000,1000);
static const int DBOX_WIDTH                   = SELECT(600,600);       //Along X direction
static const int DBOX_HEIGHT                  = SELECT(600,600);       //Along Y direction(half height in each y direction)
static const int DBOX_DEPTH                   = SELECTX(10, 10);
static const int BALL_AT_CORNER_THRESH        = SELECT(20,20); 
/* Bot Parameteres configuration */
static const float ROTATION_FACTOR            = SELECT(0.05, 0.15);                //

static const float RFACTOR                    = SELECT(3,   0.3);
static const float RFACTOR_SMALL              = SELECT(0.6, 0.15);

static const int CLEARANCE_PATH_PLANNER       = SELECT(500, 50);               //mm
static const int MID_FIELD_THRESH             = SELECT(10, 10);                       // mm
static const float BOT_RADIUS                 = SELECT(70, 100);                       // mm
static const float BALL_RADIUS                = SELECT(40, 40);                       // mm
static const float SAFE_RADIUS 			          = (BOT_RADIUS * 5);
static const float COLLISION_DIST 			      = (BOT_RADIUS * 10);
static const int DRIBBLER_BALL_THRESH         = SELECT(110, 500);            // mm


static const int BOT_BALL_THRESH              = SELECT(105, 200);                  // mm
static const int BOT_BALL_THRESH_FOR_PR       = SELECT(105, 200);                  // mm
static const int BOT_POINT_THRESH             = SELECT(105, 147);                     // mm

static const int STRIP_WIDTH_X                = ForwardX(BOT_RADIUS*1.5);
static const int STRIP_WIDTH_Y                = BOT_RADIUS*1.5;
static const int MAX_FIELD_DIST               = SELECT(1000, 3500);                // mm
static const float MAX_WHEEL_SPEED            = SELECT(2000, 100);                 //mm/s
static const float MAX_BOT_LINEAR_ACC         = SELECT(1000, 100);                // mm/s/s
static const float MAX_BOT_SPEED              = SELECT(1800, 60.0);                 // mm
static const float MIN_BOT_SPEED              = SELECT(5, 30);                     // mm/s
static const float MAX_BOT_OMEGA              = SELECT(7, 100);                     // rad/s//2
static const float MIN_BOT_OMEGA              = SELECT(0.15, 0.15);                     // rad/s
static const float MAX_BACK_DRIBBLE_V_Y       = SELECT(500, 500);                  // mm/s
static const float MAX_FRONT_DRIBBLE_V_Y      = SELECT(1200, 1200);                // mm/s
static const float MAX_DRIBBLE_V_X            = SELECT(200, 100);                 // mm/s
static const float MAX_DRIBBLE_R              = SELECT(3, 3);                      // rad
static const float DRIBBLER_BALL_ANGLE_RANGE  = SELECT(0.2f, 0.1f);                // rad
static const float SATISFIABLE_THETA          = SELECT(0.08f, 0.1f);                // rad
static const float SATISFIABLE_THETA_SHARP    = SELECT(0.01f, 0.01f);              // rad
static const float MAX_BALL_STEAL_DIST        = SELECT(800, 800);

/* If the velocity of a bot is below this value, then the bot has effectively zero velocity */
static const float ZERO_VELOCITY_THRESHOLD    = SELECT(10, 10);                    // mm/s

// Parameters useful for camera's data transformation.
static const int OUR_GOAL_Y = 500;
static const int OPP_GOAL_Y = 0;

static const float NETWORK_DELAY = SELECT(0.05, 0.05);  // Network Delay in miliseconds
//Distance Hysteresis factor for switching of roles
static const int HYSTERESIS = SELECT(20000,300);
#endif //FIELD_CONFIG_H