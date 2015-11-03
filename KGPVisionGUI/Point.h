#ifndef POINT_H
#define POINT_H

#include <cmath>

namespace KGPVisionGUI{

class Point2D
{
public:
  int x;
  int y;
  
  Point2D();
  Point2D(int x,int y);
  float getDistance(Point2D pt1,Point2D pt2);
  void assign(Point2D pt);
};

}
#endif //POINT