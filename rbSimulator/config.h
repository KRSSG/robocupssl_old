#ifndef INCL_CONFIG_H
#define INCL_CONFIG_H

#include "comdef.h"
#include "geometry.hpp"

namespace Simulator
{
  // THESE ARE THE RATES FOR UPDATE ETC
  static const int VIEW_REFRESH_RATE = 30;
  static const int UPDATE_RATE       = 30;
  static const int SEND_RATE         = 60;
  
  // THESE ARE THE NETWORK PROPERTIES
  static const int   VISION_PORT  = 10002;
  static const int   COMMAND_PORT = 20012;
  static const char* ADDRESS      = "224.5.23.2";
  static const char* INTER_FACE   = "";
  
  //--BALL CONFIGURATIONS
  static const int BALL_AREA    = 200;
  static const int BALL_PIXEL_X = 30;
  static const int BALL_PIXEL_Y = 30;
  static const int _BALL_RADIUS = 30;

  //--END BALL CONFIGS


  //-- BOT COONFIGS
  static const int BOT_PIXEL_X = 60;
  static const int BOT_PIXEL_Y = 60;

  //--END BOT CONFIGS

  //-- FIELD CONFIGURATIONS
  static const int XSHIFT  = 30;
  static const int YSHIFT  = 0;
  static const int BOT_MAX = BlueTeam::SIZE;    // HACK RbSimulator has BOT_MAX all over the code, but it has to be separate for each team

  //-- END FIELD CONFIGURATIONS

  //--Teams
  static const int _BOT_RADIUS = 90;
  //-- end Teams

  //these configurations hold the scale to show the field
  static const float scaleFactor   = 0.13f;
  static const int fieldShowWidth  = 550;
  static const int fieldShowLength = 825;
  //-----

  static const int line_width                        = 10;
  static const int field_length                      = 6050;
  static const int field_width                       = 4050;
  static const int boundary_width                    = 250;
  static const int referee_width                     = 425;
  static const int goal_width                        = 700;
  static const int goal_depth                        = 180;
  static const int goal_wall_width                   = 20;
  static const int center_circle_radius              = 500;
  static const int defense_radius                    = 500;
  static const int defense_stretch                   = 350;
  static const int free_kick_from_defense_dist       = 200;
  static const int penalty_spot_from_field_line_dist = 450;
  static const int penalty_line_from_spot_dist       = 400;
  static const int pXSHIFT                           = XSHIFT - line_width/2;
  static const int pYSHIFT                           = YSHIFT - line_width/2;

  //--------- otherGUI constraints------
  static const int MAX_ITEMS = 200;
  static const int MAX_TEXT  = 50;
  //------------------------------------
}

namespace PhysxEngine
{
  // Physics Engine Frames per second
  static const int FPS                 = 60;
  
  // Arena dimensions in MKS units
  static const float ARENA_W           = 7.4f;
  static const float ARENA_H           = 5.4f;
  static const float FIELD_W           = 6.05f;
  static const float FIELD_H           = 4.05f;
  static const float GOAL_W            = 0.18f;
  static const float GOAL_H            = 0.7f;

  // Arena physical properties in MKS units
  static const float ARENA_FRIC        = 1.0f;
  static const float ARENA_REST        = 0.1f;

  // Ball dimensions in MKS units
  static const float BALL_RADIUS       = 0.0215f;

  // Ball physical properties in MKS units
  static const float BALL_MASS         = 0.043f;
  static const float BALL_GND_FRIC     = 0.3f;
  static const float BALL_WALL_FRIC    = 0.1f;
  static const float BALL_REST         = 0.0f;
  
  // Bot dimensions in MKS units
  
  static const float BOT_RADIUS        = 0.09f;
  // Width of the dribbler bar
  static const float DRIBB_W           = 0.02f;                 
  // Length of the dribbler bar as a percentage of length of the flat edge of the bot
  static const float DRIBB_L           = 0.7f;                   
  // Half angle subtended by the flat edge of the bot at the center of the bot
  static const float FACE_HALF_ANG     = 49.68f*PI/180.f; 

  // Bot physical properties in MKS units
  
  static const float BOT_MASS          = 2.0f;
  static const float BOT_GND_FRIC      = 0.2f;
  static const float BOT_WALL_FRIC     = 10.0f;
  static const float BOT_REST          = 0.5f;
  static const float DRIBB_FRIC        = 10.0f;
  // Measure of the number of back-spins put on the ball by the dribbler
  static const float DRIBB_INF_DIST    = 0.05f;   

  // Time taken by the kicker to recharge from 0 to full power
  static const float KICKER_RECHARGE_TIME = 5.0f;
  static const float MAX_KICK_SPEED    = 5.0f;

  // Fixture User Data used for indentification of the fixture type
  static const char DRIBB_USER_DATA    = 'D';
  static const char BALL_USER_DATA     = 'b';
  static const char ARENA_USER_DATA    = 'A';
  static const char BOT_BODY_USER_DATA = 'B';
  static const char SENSOR_USER_DATA   = 'S';
} // PhysxEngine

#endif  // INCL_CONFIG_H
