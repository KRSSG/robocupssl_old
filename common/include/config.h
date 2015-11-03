#ifndef INCL_CONFIG_H
#define INCL_CONFIG_H

namespace Simulator
{
  static const int PORT = 10002;
  static const char *ADDRESS = "224.5.23.2";
  static const char *INTER_FACE = "";

  //--BALL CONFIGURATIONS
  static const int BALL_AREA = 200;
  static const int BALL_PIXEL_X = 30;
  static const int BALL_PIXEL_Y = 30;
  static const int BALL_RADIUS = 30;

  //--END BALL CONFIGS


  //-- BOT COONFIGS
  static const int BOT_PIXEL_X = 60;
  static const int BOT_PIXEL_Y = 60;

  //--END BOT CONFIGS

  //-- FIELD CONFIGURATIONS
  static const int XSHIFT = 30;
  static const int YSHIFT = 0;
  
  //-- END FIELD CONFIGURATIONS

  //--Teams
  static const int YELLOW  = 0;
  static const int BLUE = 1;
  static const int _BOT_RADIUS = 90;
  //-- end Teams

  //these configurations hold the scale to show the field
  static const float scaleFactor = 0.13f;
  static const int fieldShowWidth = 550;
  static const int fieldShowLength = 825;
  //-----

  static const int line_width = 10;
  static const int field_length = 6050;
  static const int field_width = 4050;
  static const int boundary_width = 250;
  static const int referee_width = 425;
  static const int goal_width = 700;
  static const int goal_depth = 180;
  static const int goal_wall_width = 20;
  static const int center_circle_radius = 500;
  static const int defense_radius = 500;
  static const int defense_stretch = 350;
  static const int free_kick_from_defense_dist = 200;
  static const int penalty_spot_from_field_line_dist = 450;
  static const int penalty_line_from_spot_dist = 400;
  static const int pXSHIFT = XSHIFT - line_width/2;
  static const int pYSHIFT = YSHIFT - line_width/2;

  //--------- otherGUI constraints------
  static const int MAX_ITEMS = 200;
  static const int MAX_TEXT = 50;
  //------------------------------------

  //-Wrapping Names----
}

#endif  // INCL_CONFIG_H
